/* Test the `vqshlQs8' ARM Neon intrinsic.  */
/* This file was autogenerated by neon-testgen.  */

/* { dg-do assemble } */
/* { dg-require-effective-target arm_neon_ok } */
/* { dg-options "-save-temps -O0 -mfpu=neon -mfloat-abi=softfp" } */

#include "arm_neon.h"

void test_vqshlQs8 (void)
{
  int8x16_t out_int8x16_t;
  int8x16_t arg0_int8x16_t;
  int8x16_t arg1_int8x16_t;

  out_int8x16_t = vqshlq_s8 (arg0_int8x16_t, arg1_int8x16_t);
}

/* { dg-final { scan-assembler "vqshl\.s8\[ 	\]+\[qQ\]\[0-9\]+, \[qQ\]\[0-9\]+, \[qQ\]\[0-9\]+!?\(\[ 	\]+@\[a-zA-Z0-9 \]+\)?\n" } } */
/* { dg-final { cleanup-saved-temps } } */
