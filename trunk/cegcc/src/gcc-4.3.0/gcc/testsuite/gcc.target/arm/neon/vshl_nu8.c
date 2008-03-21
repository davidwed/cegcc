/* Test the `vshl_nu8' ARM Neon intrinsic.  */
/* This file was autogenerated by neon-testgen.  */

/* { dg-do assemble } */
/* { dg-require-effective-target arm_neon_ok } */
/* { dg-options "-save-temps -O0 -mfpu=neon -mfloat-abi=softfp" } */

#include "arm_neon.h"

void test_vshl_nu8 (void)
{
  uint8x8_t out_uint8x8_t;
  uint8x8_t arg0_uint8x8_t;

  out_uint8x8_t = vshl_n_u8 (arg0_uint8x8_t, 1);
}

/* { dg-final { scan-assembler "vshl\.i8\[ 	\]+\[dD\]\[0-9\]+, \[dD\]\[0-9\]+, #\[0-9\]+!?\(\[ 	\]+@\[a-zA-Z0-9 \]+\)?\n" } } */
/* { dg-final { cleanup-saved-temps } } */
