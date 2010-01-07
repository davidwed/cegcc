/* Copyright (c) 2007, Pedro Alves

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  */

#ifndef __PIPE_LIB_H__
#define __PIPE_LIB_H__

#ifdef __cplusplus
# define PIPELIB_API extern "C"
#else
# define PIPELIB_API
#endif

PIPELIB_API BOOL CreatePipe (PHANDLE,PHANDLE,LPSECURITY_ATTRIBUTES,DWORD);
PIPELIB_API BOOL PeekNamedPipe (HANDLE,LPVOID,DWORD,LPDWORD,LPDWORD,LPDWORD);

PIPELIB_API BOOL GetPipeName (HANDLE, WCHAR*);

/* Internal, for pipedev.dll debugging purposes.  */
PIPELIB_API BOOL SetPipeTag (HANDLE, const WCHAR*);

#endif
