#include <stdint.h>
#include "testbench.h"

uint32_t umul32(uint32_t i0, uint32_t i1)
{
  return i0*i1;
}

void main()
{
  uint32_t x,y,z,z_expected;

  if (0)
    {
      x          = 0x0000bebe;
      y          = 0x0000babe;
      z_expected = 0x8b239d04;
      z          = umul32(x,y);

      watch32b(x);
      watch32b(y);
      watch32b(z);
    
      if (z != z_expected)
	TEST_KO;
    }

  if (0)
    {
      x          = 0xdeadbeef;
      y          = 0x00000000;
      z_expected = 0xdeadbeef;
      z          = umul32(x,y);

      watch32b(x);
      watch32b(y);
      watch32b(z);

      if (z != z_expected)
	TEST_KO;
    }
  
  if (1)
    {
      x          = 0xdeadbeef;
      y          = 0xcafedeca;
      z_expected = 0x67cdea96;
      z          = umul32(x,y);

      watch32b(x);
      watch32b(y);
      watch32b(z);

      if (z != z_expected)
	TEST_KO;
    }

  
  TEST_OK;
}
