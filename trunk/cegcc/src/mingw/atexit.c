/*
 * dllcrt1.c
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is a part of the mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within the package.
 *
 * Initialization code for DLLs.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <process.h>
#include <windows.h>

typedef void (* p_atexit_fn )(void);
static p_atexit_fn* first_atexit;
static p_atexit_fn* next_atexit;

/* This  is based on the function in the Wine project's exit.c */
static p_atexit_fn __dllonexit (p_atexit_fn, p_atexit_fn**, p_atexit_fn**);

int
atexit (p_atexit_fn pfn)
{
#ifdef DEBUG
  printf ("%s: registering exit function  0x%x at 0x%x\n",
	  __FUNCTION__, (unsigned)pfn, (unsigned)next_atexit);
#endif
  return (__dllonexit (pfn,  &first_atexit, &next_atexit)
	  == NULL ? -1  : 0 );
}

_onexit_t
_onexit (_onexit_t pfn)
{
#ifdef DEBUG
  printf ("%s: registering exit function  0x%x at 0x%x\n",
	  __FUNCTION__, (unsigned)pfn, (unsigned)next_atexit);
#endif
  return ((_onexit_t) __dllonexit ((p_atexit_fn)pfn,  &first_atexit, &next_atexit));
}

void
_cexit (void)
{
    size_t len = next_atexit - first_atexit;
    p_atexit_fn* pfn = next_atexit;
    int i;

    if (len != 0)
    {
        --pfn;
        do 
        {
            (*pfn)(); 
        } 
        while (pfn != first_atexit);
    }

    _fcloseall ();
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
}

#include "__dllonexit.c"
