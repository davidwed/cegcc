/* { dg-do compile { target mips16_attribute } } */
/* { dg-mips-options "-mcode-readable=yes -mgp32" } */
/* { dg-add-options mips16_attribute } */

MIPS16 int
foo (int i)
{
  switch (i)
    {
    case 1: return 40;
    case 2: return 11;
    case 3: return 29;
    case 4: return 10;
    case 5: return 12;
    case 6: return 35;
    case 7: return 23;
    default: return 0;
    }
}

extern int k[];

MIPS16 int *
bar (void)
{
  return k;
}

/* { dg-final { scan-assembler "\tla\t" } } */
/* { dg-final { scan-assembler "\t\.half\t" } } */
/* { dg-final { scan-assembler-not "%hi\\(\[^)\]*L" } } */
/* { dg-final { scan-assembler-not "%lo\\(\[^)\]*L" } } */

/* { dg-final { scan-assembler "\t\.word\tk\n" } } */
/* { dg-final { scan-assembler-not "%hi\\(k\\)" } } */
/* { dg-final { scan-assembler-not "%lo\\(k\\)" } } */
