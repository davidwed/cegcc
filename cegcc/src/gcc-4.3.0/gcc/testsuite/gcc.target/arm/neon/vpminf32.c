/* Test the `vpminf32' ARM Neon intrinsic.  */
/* This file was autogenerated by neon-testgen.  */

/* { dg-do assemble } */
/* { dg-require-effective-target arm_neon_ok } */
/* { dg-options "-save-temps -O0 -mfpu=neon -mfloat-abi=softfp" } */

#include "arm_neon.h"

void test_vpminf32 (void)
{
  float32x2_t out_float32x2_t;
  float32x2_t arg0_float32x2_t;
  float32x2_t arg1_float32x2_t;

  out_float32x2_t = vpmin_f32 (arg0_float32x2_t, arg1_float32x2_t);
}

/* { dg-final { scan-assembler "vpmin\.f32\[ 	\]+\[dD\]\[0-9\]+, \[dD\]\[0-9\]+, \[dD\]\[0-9\]+!?\(\[ 	\]+@\[a-zA-Z0-9 \]+\)?\n" } } */
/* { dg-final { cleanup-saved-temps } } */
