/* Software floating-point emulation.
   Convert a 128bit signed integer to IEEE quad
   Copyright (C) 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Uros Bizjak (ubizjak@gmail.com).

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   In addition to the permissions in the GNU Lesser General Public
   License, the Free Software Foundation gives you unlimited
   permission to link the compiled version of this file into
   combinations with other programs, and to distribute those
   combinations without any restriction coming from the use of this
   file.  (The Lesser General Public License restrictions do apply in
   other respects; for example, they cover modification of the file,
   and distribution when not linked into a combine executable.)

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "soft-fp.h"
#include "quad.h"

TFtype __floattitf(TItype i)
{
  FP_DECL_EX;
  FP_DECL_Q(A);
  TFtype a;

  FP_FROM_INT_Q(A, i, TI_BITS, UTItype);
  FP_PACK_RAW_Q(a, A);
  FP_HANDLE_EXCEPTIONS;

  return a;
}
