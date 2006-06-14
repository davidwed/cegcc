#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifndef	DebugBreak
/* Stolen from sys/oldsys/wcebase.h */
#define DebugBreak() asm( ".word 0xE6000010" )
#endif

_VOID
_DEFUN_VOID (abort)
{
#ifdef ABORT_MESSAGE
  write (2, "Abort called\n", sizeof ("Abort called\n")-1);
#endif

  wchar_t buf[256];
  GetModuleFileNameW(NULL, buf, sizeof(buf));
  MessageBoxW(0, buf, L"Abort!", 0);
  DebugBreak();
  TerminateProcess(0,0);
  _exit (1);

  while (1)
    {
      raise (SIGABRT);
	  DebugBreak();
      _exit (1);
    }
}
