/* rshd for Windows CE.

   Copyright (C) 2007, Pedro M. P. Alves

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.


   Originally based on rlogind from GNUWINCE by Voxware Inc.,
   rewritten as native Windows CE application using PipeLib
   and mingw32ce.  */

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <stdarg.h>
#include <malloc.h>

#include <windows.h>
#include <winsock2.h>

#include <PipeLib.h>

#ifndef COUNTOF
#define COUNTOF(STR) (sizeof (STR) / sizeof ((STR)[0]))
#endif

static BOOL debug = FALSE;



static void
logprintf (const char *fmt, ...)
{
  if (0)
    {
      FILE *logfile = fopen("/rshd.log", "a+");

      if (logfile)
	{
	  va_list ap;
	  va_start (ap, fmt);
	  vfprintf (logfile, fmt, ap);
	  va_end (ap);
	  fclose (logfile);
	}
    }
  else if (debug)
    {
      va_list ap;
      va_start (ap, fmt);
      vfprintf (stderr, fmt, ap);
      fflush (stderr);
      va_end (ap);
    }
}

/* Map the Windows error number in ERROR to a locale-dependent error
   message string and return a pointer to it.  Typically, the values
   for ERROR come from GetLastError.

   The string pointed to shall not be modified by the application,
   but may be overwritten by a subsequent call to strwinerror

   The strwinerror function does not change the current setting
   of GetLastError.  */

char *
strwinerror (DWORD error)
{
  static char buf[1024];
  TCHAR *msgbuf;
  DWORD lasterr = GetLastError ();
  DWORD chars = FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM
			       | FORMAT_MESSAGE_ALLOCATE_BUFFER,
			       NULL,
			       error,
			       0, /* Default language */
			       (LPVOID)&msgbuf,
			       0,
			       NULL);
  if (chars != 0)
    {
      /* If there is an \r\n appended, zap it.  */
      if (chars >= 2
	  && msgbuf[chars - 2] == '\r'
	  && msgbuf[chars - 1] == '\n')
	{
	  chars -= 2;
	  msgbuf[chars] = 0;
	}

      if (chars > ((COUNTOF (buf)) - 1))
	{
	  chars = COUNTOF (buf) - 1;
	  msgbuf [chars] = 0;
	}

      wcstombs (buf, msgbuf, chars + 1);
      LocalFree (msgbuf);
    }
  else
    sprintf (buf, "unknown win32 error (%ld)", error);

  SetLastError (lasterr);
  return buf;
}

void
perror (const char *s)
{
  if (s && *s)
    fprintf (stderr, "%s: %s\n", s, strwinerror (GetLastError ()));
  else
    fprintf (stderr, "%s\n", strwinerror (GetLastError ()));
}



struct client_data_t
{
  int clientid;
  /* stdin/stdout */
  int sockfd;

  /* stderr */
  int stderrsockfd;

  /* remote */
  struct sockaddr_in sin;

  /* pipe handles for stdin/stdout/stderr.  */
  HANDLE readh[3];
  HANDLE writeh[3];

  /* stop request */
  volatile BOOL stop;

  long refcount;
};

static void
addref_data (struct client_data_t * data)
{
  InterlockedIncrement (&data->refcount);
}

static void
release_data (struct client_data_t * data)
{
  if (InterlockedDecrement (&data->refcount) == 0)
    {
      logprintf ("Connection from %s:%d terminated\n",
		 inet_ntoa (data->sin.sin_addr),
		 ntohs (data->sin.sin_port));
      free (data);
    }
}

static void
init_client_data (struct client_data_t *data)
{
  static int clientid = 0;
  int i;

  data->refcount = 0;

  memset (&data->sin, 0, sizeof (data->sin));

  data->clientid = ++clientid;
  data->sockfd = data->stderrsockfd = -1;

  for (i = 0; i < 3; i++)
    {
      data->readh[0] = INVALID_HANDLE_VALUE;
      data->writeh[0] = INVALID_HANDLE_VALUE;
    }

  data->stop = FALSE;
}

#if 0
/* check if hostname is in users .rhost file */
static int
rsh_userok (const char *hostname, const char *user)
{
#if 0
  struct passwd *pw;
  char s[256] = "";
  FILE *f;
  if ((pw = getpwnam (user)) == NULL)
    return 0;
  strcpy (s, pw->pw_dir);
  strcat (s, "/.rhosts");
  if ((f = fopen (s, "r")) == NULL)
    return 0;
  while (fgets (s, sizeof (s), f))
    {
      char *p;
      p = strchr (s, '\n');
      if (p)
	*p = 0;
      p = strchr (s, '\r');
      if (p)
	*p = 0;
      if (strcmp (hostname, s) == 0)
	{
	  fclose (f);
	  return 1;
	}
    }
  fclose (f);
  return 0;
#endif
  (void)hostname;
  (void)user;
  return 1;
}
#endif

static DWORD WINAPI
stdin_thread (void *arg)
{
  struct client_data_t *data = arg;
  const char *thread_name = "stdin_thread";

  addref_data (data);

  /* We don't need the reading side.  */
  CloseHandle (data->readh[0]);
  data->readh[0] = INVALID_HANDLE_VALUE;

  while (!data->stop)
    {
      int read = 0;
      char buf[1];

      read = recv (data->sockfd, buf, sizeof(buf), 0);
      if (read < 0)
	{
	  DWORD err = WSAGetLastError ();
	  switch (err)
	    {
	    case WSAECONNRESET:
	    case WSAEINTR:
	      if (!data->stop)
		/* only be verbose if we were not expecting it.  */
		logprintf ("%s: connection reset.\n", thread_name);
	      break;
	    default:
	      logprintf ("%s: recv ERROR, winerr %d\n", thread_name, err);
	      break;
	    }
	  break;
	}
      else if (read == 0)
	{
	  logprintf ("%s: connection closed\n", thread_name);
	  break;
	}

      if (read)
	{
	  int written;
	  DWORD dwwritten;

#if 1
	  /* echo data back ...  */
	  written = send (data->sockfd, buf, read, 0);
	  if (written < 0)
	    logprintf ("%s: write ERROR, winerr %d\n",
		       thread_name,
		       GetLastError ());
	  else if (written < read)
	    logprintf ("%s: ERROR only wrote %d of %d bytes\n",
		       thread_name, written, read);
#endif

	  /* ... and stuff it into the child's stdin.  */
	  if (!WriteFile (data->writeh[0], buf, read, &dwwritten, NULL))
	    {
	      logprintf ("%s: broken pipe (2)\n", thread_name);
	      break;
	    }
	}
    }

  release_data (data);
  logprintf ("%s gone\n", thread_name);
  return 0;
}

static DWORD WINAPI
stdout_thread (void *arg)
{
  struct client_data_t *data = arg;
  const char *thread_name = "stdout_thread";

  addref_data (data);

  while (!data->stop)
    {
      DWORD read = 0;
      char buf[256];
      if (!ReadFile (data->readh[1], buf, sizeof (buf), &read, FALSE))
	{
	  logprintf ("%s: broken pipe\n", thread_name);
	  break;
	}
      else if (data->writeh[1] != INVALID_HANDLE_VALUE)
	{
	  /* We can't close the write side of the pipe until the
	     child opens its version.  Since it will only be open on the
	     first stdout access, we have to wait until the read side returns
	     something - which means the child opened stdout.  */
	  CloseHandle (data->writeh[1]);
	  data->writeh[1] = INVALID_HANDLE_VALUE;
	}
      if (read)
	{
	  int written = send (data->sockfd, buf, read, 0);
	  if (written < 0)
	    logprintf ("%s: write ERROR, winerr %d\n",
		       thread_name,
		       GetLastError ());
	  else if ((DWORD) written < read)
	    logprintf ("%s: ERROR only wrote %d of %d bytes\n",
		       thread_name, written, read);
	}
    }

  release_data (data);
  logprintf ("%s gone\n", thread_name);
  return 0;
}

static DWORD WINAPI
stderr_thread (void *arg)
{
  struct client_data_t *data = arg;
  const char *thread_name = "stderr_thread";
  int sockfd;

  addref_data (data);

  sockfd = data->stderrsockfd;
  if (sockfd == -1)
    /* If we don't have a separate stderr channel, send the data
       as if it came through stdout. */
    sockfd = data->sockfd;

  while (!data->stop)
    {
      DWORD read = 0;
      char buf[256];

      if (!ReadFile (data->readh[2], buf, sizeof (buf), &read, FALSE))
	{
	  logprintf ("%s: broken pipe\n", thread_name);
	  break;
	}
      else if (data->writeh[2] != INVALID_HANDLE_VALUE)
	{
	  /* We can't close the write side of the pipe until the
	     child opens its version.  Since it will only be open on the
	     first stderr access, we have to wait until the read side returns
	     something - which means the child opened stderr.  */
	  CloseHandle (data->writeh[2]);
	  data->writeh[2] = INVALID_HANDLE_VALUE;
	}
      if (read)
	{
	  int written = send (sockfd, buf, read, 0);
	  if (written < 0)
	    logprintf ("%s: write ERROR, winerr %d\n",
		       thread_name,
		       GetLastError ());
	  else if ((DWORD) written < read)
	    logprintf ("%s: ERROR only wrote %d of %d bytes\n",
		       thread_name, written, read);
	}
    }

  release_data (data);
  logprintf ("%s gone\n", thread_name);
  return 0;
}

static void
to_back_slashes (char *path)
{
  for (; *path; ++path)
    if ('/' == *path)
      *path = '\\';
}

/* Start a new process.
   Returns the new process' handle on success, NULL on failure.  */
static HANDLE
create_child (char *program, HANDLE *readh, HANDLE *writeh)
{
  BOOL ret;
  char *args;
  int argslen;
  PROCESS_INFORMATION pi;
  wchar_t *wargs, *wprogram;
  wchar_t prev_path[3][MAX_PATH];
  size_t i;

  if (program == NULL || program[0] == '\0')
    {
      fprintf (stderr,
	       "No executable specified, specify executable to control.\n");
      return NULL;
    }

  argslen = 0;
  args = program;
  /* TODO: program paths with embedded spaces?  */
  args = strchr (args, ' ');
  if (args != NULL)
    *args++ = '\0';
  else
    args = "";
  argslen = strlen (args);
  wargs = alloca ((argslen + 1) * sizeof (wchar_t));
  mbstowcs (wargs, args, argslen + 1);

  /* PROGRAM is now free from args.  */
  to_back_slashes (program);
  wprogram = alloca ((strlen (program) + 1) * sizeof (wchar_t));
  mbstowcs (wprogram, program, strlen (program) + 1);
  /* Do the PipeLib/WinCE dup dance.  */

  for (i = 0; i < 3; i++)
    {
      wchar_t devname[MAX_PATH];
      if (!CreatePipe (&readh[i], &writeh[i], NULL, 0))
	return NULL;

      GetPipeName (readh[i], devname);
      DWORD dwLen = MAX_PATH;
      GetStdioPathW (i, prev_path[i], &dwLen);
      SetStdioPathW (i, devname);
    }

  ret = CreateProcessW (wprogram, /* image name */
			wargs,    /* command line */
			NULL,     /* security, not supported */
			NULL,     /* thread, not supported */
			FALSE,    /* inherit handles, not supported */
			0,        /* start flags */
			NULL,     /* environment, not supported */
			NULL,     /* current directory, not supported */
			NULL,     /* start info, not supported */
			&pi);     /* proc info */

  for (i = 0; i < 3; i++)
    SetStdioPathW (i, prev_path[i]);

  if (!ret)
    {
      DWORD err = GetLastError ();
      fprintf (stderr, "Error creating process \"%s %s\", (error %d): %s\n",
	       program, args, (int) err, strwinerror (err));

      for (i = 0; i < 3; i++)
	{
	  CloseHandle (readh[i]);
	  CloseHandle (writeh[i]);
	}
      return NULL;
    }
  else
    logprintf ("Process created: %s\n", program);

  CloseHandle (pi.hThread);
  pi.hThread = NULL;

  return pi.hProcess;
}

static int
rresvport (int *alport)
{
  struct sockaddr_in sin;
  int s;
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  s = socket (AF_INET, SOCK_STREAM, 0);
  if (s == -1)
    return -1;

  for (;;)
    {
      sin.sin_port = htons ((USHORT) *alport);
      if (bind (s, (struct sockaddr *) &sin, sizeof(sin)) == 0)
	return s;

      if (WSAGetLastError () != WSAEADDRINUSE)
	{
	  closesocket (s);
	  return -1;
	}
      (*alport)--;
      if (*alport == IPPORT_RESERVED / 2)
	{
	  closesocket (s);
	  return -1;
	}
    }
}

int
connect_stderr (int in, unsigned short stderr_port)
{
  int s;
  int lport = IPPORT_RESERVED - 1;
  struct sockaddr_in sin;
  int len = sizeof (sin);

  logprintf ("Connecting stderr to remote port %d\n", stderr_port);
  if (getpeername (in, (struct sockaddr *) &sin, &len) == -1)
    {
      perror ("getpeername");
      return -1;
    }

  for (;;)
    {
      if ((s = rresvport (&lport)) == -1)
	{
	  perror ("rresvport");
	  return -1;
	}

      sin.sin_port = htons (stderr_port);
      if (connect (s, (struct sockaddr *) &sin, sizeof(sin)) == -1)
	{
	  closesocket (s);
	  if (WSAGetLastError () == WSAEADDRINUSE)
	    {
	      lport--;
	      continue;
	    }

	  logprintf ("connect: %s\n", strwinerror (WSAGetLastError ()));;
	  closesocket (s);
	  return -1;
	}

      logprintf ("Using resvport %d\n", lport);
      break;
    }

  return s;
}

static WINAPI DWORD
handle_connection (void *arg)
{
  int s2 = (int) arg; /* sizeof (void*) == sizeof (int) */
  int stderrsockfd = -1;
  unsigned short stderr_port = 0;
  int cc;
  char c, *p;
  char stderrport[100] = "";
  char locuser[0x101] = "";
  char remuser[0x101] = "";
  char command[8193];
  int len = sizeof (struct sockaddr_in);
  struct hostent *hp;
  const char *peername;
  struct linger linger;

  struct client_data_t* client_data;

  HANDLE waith[4];
  HANDLE hndproc;
  DWORD tid[3];
  size_t i;
  int enabled = 1;
  /*  int disabled = 0; */

  logprintf ("handle_conn: STARTED\n");

  client_data = malloc (sizeof (*client_data));
  init_client_data (client_data);
  addref_data (client_data);

  /* Allow rapid reuse of this port. */
  if (setsockopt (s2, SOL_SOCKET, SO_REUSEADDR,
		  (char *) &enabled, sizeof (enabled)) < 0)
    {
      perror ("setsockopt (SO_KEEPALIVE)");
      goto shutdown;
    }

  /* Enable TCP keep alive process. */
  if (setsockopt (s2, SOL_SOCKET, SO_KEEPALIVE,
		  (char *) &enabled, sizeof (enabled)) < 0)
    {
      perror ("setsockopt (SO_KEEPALIVE)");
      goto shutdown;
    }

  linger.l_onoff = 1;
  linger.l_linger = 60;
#if 0
  if (setsockopt (s2, SOL_SOCKET, SO_LINGER, (char *)&linger,
		  sizeof (linger)) < 0)
    {
      perror ("setsockopt (SO_LINGER)");
      goto shutdown;
    }
#endif

  /* Tell TCP not to delay small packets.  This greatly speeds up
     interactive response. */
  if (setsockopt (s2, IPPROTO_TCP, TCP_NODELAY,
		  (char *) &enabled, sizeof (enabled)) < 0)
    {
      perror ("setsockopt (TCP_NODELAY)");
      goto shutdown;
    }

  if (getpeername (s2, (struct sockaddr *) &client_data->sin, &len) == -1)
    {
      perror ("getpeername");
      goto shutdown;
    }

  /* Verify that the client's address is an Internet adress. */
  if (client_data->sin.sin_family != AF_INET)
    {
      fprintf (stderr, "malformed \"from\" address (af %d)\n",
	       client_data->sin.sin_family);
      goto shutdown;
    }

  hp = gethostbyaddr ((char *) &client_data->sin.sin_addr,
		      sizeof(client_data->sin.sin_addr), PF_INET);

  peername = (hp != NULL)
    ? hp->h_name
    : "unknown";

  logprintf ("Connection from (%s) %s:%d...\n",
	     peername,
	     inet_ntoa (client_data->sin.sin_addr),
	     ntohs (client_data->sin.sin_port));

  /* get stderr port. */
  p = stderrport;
  while ((cc = recv (s2, &c, 1, 0)) > 0 && c != 0)
    *p++ = c;
  *p = 0;


  if ((stderr_port = atoi (stderrport)) > 0)
    {
      stderrsockfd = connect_stderr (s2, stderr_port);
      if (stderrsockfd == -1)
	{
	  logprintf ("cannot connect stderr\n");
	  goto shutdown;
	}
    }

  if (cc == -1)
    {
      logprintf ("error reading stderr port: %s\n",
		 strwinerror (GetLastError ()));
      goto shutdown;
    }

  p = locuser;
  while ((cc = recv (s2, &c, 1, 0)) > 0 && c != 0)
    *p++ = c;
  *p = 0;
  if (cc == -1)
    {
      logprintf ("error reading user name: %s\n",
		 strwinerror (GetLastError ()));
      goto shutdown;
    }

  p = remuser;
  while ((cc = recv (s2, &c, 1, 0)) > 0 && c != 0)
    *p++ = c;
  *p = 0;

  if (cc == -1)
    {
      logprintf ("error reading rem user/password: %s\n",
		 strwinerror (GetLastError ()));
      goto shutdown;
    }

  p = command;
  while ((cc = recv (s2, &c, 1, 0)) > 0 && c != 0)
    *p++ = c;
  *p = 0;
  if (cc == -1)
    {
      logprintf ("error reading command: %s\n", strwinerror (GetLastError ()));
      goto shutdown;
    }
  logprintf ("Local user: %s\nRemote user: %s\nCommand: %s\n",
	     locuser, remuser, command);
#if 0
  if (!hp || !rsh_userok (hp->h_name, remuser))
    {      /* check .rhosts */
      char *s = "Permission denied\n";
      send (s2, s, strlen (s) + 1, 0);
      goto shutdown;
    }
#endif

  /* send OK */
  send (s2, "", 1, 0);

  logprintf ("handle_connection: starting command... \n");
  hndproc = create_child (command, client_data->readh, client_data->writeh);
  if (!hndproc)
    {
      logprintf ("handle_connection: ERROR can't create child process, "
		 "winerr %d\n", GetLastError ());
      goto shutdown;
    }

  client_data->sockfd = s2;
  client_data->stderrsockfd = stderrsockfd;

  waith[0] = CreateThread (NULL, 0, stdin_thread, client_data, 0, &tid[0]);
  waith[1] = CreateThread (NULL, 0, stdout_thread, client_data, 0, &tid[1]);
  waith[2] = CreateThread (NULL, 0, stderr_thread, client_data, 0, &tid[2]);
  waith[3] = hndproc;

  switch (WaitForMultipleObjects (COUNTOF (waith), waith, FALSE, INFINITE))
    {
    case WAIT_OBJECT_0:
    case WAIT_OBJECT_0 + 1:
    case WAIT_OBJECT_0 + 2:
      TerminateProcess (hndproc, 0);
      break;
    case WAIT_OBJECT_0 + 3:
      break;
    default:
      logprintf ("WaitForMultipleObjects' default reached\n");
      break;
    }

  client_data->stop = TRUE;

  for (i = 0; i < 4; i++)
    CloseHandle (waith[i]);

  for (i = 0; i < 3; i++)
    {
      CloseHandle (client_data->writeh[i]);
      CloseHandle (client_data->readh[i]);
    }

 shutdown:
  logprintf ("Shutting down connection from %s:%d...\n",
	     inet_ntoa (client_data->sin.sin_addr),
	     ntohs (client_data->sin.sin_port));

  /* close sockets */
  shutdown (s2, 2);
  closesocket (s2);
  if (stderrsockfd != -1)
    {
      shutdown (stderrsockfd, 2);
      closesocket (stderrsockfd);
    }

  release_data (client_data);

  /* maybe we should wait for all the still alive threads again?  */

  return 0;
}

static void
accept_connections (void)
{
  int s;
  struct sockaddr_in sin;
  USHORT port = 0;
  struct hostent *phe;
  int i;
  char ac[80];

  port = 514;

  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;

  if ((s = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("socket");
      exit (1);
    }

  sin.sin_port = htons(port);
  if (bind (s, (struct sockaddr *) &sin, sizeof (sin)) != 0)
    {
      perror ("bind");
      closesocket (s);
      exit (1);
    }

  /* 10 is the maximum backlog allowed */
  if (listen (s, 10) != 0)
    {
      perror ("listen");
      closesocket (s);
      exit (1);
    }

  if (gethostname (ac, sizeof(ac)) == SOCKET_ERROR)
    {
      fprintf (stderr, "Error %d when getting local host name.\n",
	       WSAGetLastError());
      exit (1);
    }
  printf ("Host name is %s.\n", ac);

  phe = gethostbyname (ac);
  if (phe == NULL)
    {
      fprintf (stderr, "Yow! Bad host lookup.\n");
      exit (1);
    }

  for (i = 0; phe->h_addr_list[i] != 0; ++i)
    {
      struct in_addr addr;
      memcpy (&addr, phe->h_addr_list[i], sizeof (struct in_addr));
      printf ("Address %d: %s\n", i, inet_ntoa (addr));
    }

  logprintf ("rshd ready\n\n");
  for (;;)
    {
      HANDLE connThread;
      int s2;

      logprintf ("Listening on port %d...\n", port);
      if ((s2 = accept (s, NULL, NULL)) == -1)
	{
	  perror ("accept");
	  closesocket (s);
	  exit (1);
	}

      logprintf ("handle_conn: accepted\n");
      connThread = CreateThread (NULL, 0,
				 handle_connection,
				 (LPVOID)s2, 0, NULL);
      CloseHandle (connThread);
      logprintf ("CreateThread (connThread) returns\n");
    }
}

int
main (int argc, char **argv)
{
  WSADATA wsad;
  WSAStartup (MAKEWORD (2, 0), &wsad);

  if (argc > 1 && strcmp(argv[1], "-d") == 0)
    debug = 1;

  accept_connections ();
  return 0;
}
