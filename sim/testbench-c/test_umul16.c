#include <stdint.h>
#include "testbench.h"

uint32_t umul16(uint16_t i0, uint16_t i1)
{
  uint32_t res = (uint32_t)i0*(uint32_t)i1;

  return res;
}

void main()
{
  uint16_t x,y;
  uint32_t z,z_expected;

  if (1)
    {
      x          = 0x0000bebe;
      y          = 0x0000babe;
      z_expected = 0x8b239d04;

      watch32b(x);
      watch32b(y);

      z          = umul16(x,y);

      watch32b(z);
    
      if (z != z_expected)
	TEST_KO;
    }

  if (1)
    {
      x          = 0x0000beef;
      y          = 0x0000deca;
      z_expected = 0xa629ea96;

      watch32b(x);
      watch32b(y);

      z          = umul16(x,y);

      watch32b(z);

      if (z != z_expected)
	TEST_KO;
    }


  if (1)
    {
      x          = 0xdeadbeef;
      y          = 0x00000000;
      z_expected = 0x00000000;

      watch32b(x);
      watch32b(y);

      z          = umul16(x,y);

      watch32b(z);

      if (z != z_expected)
	TEST_KO;
    }
  
  TEST_OK;
}
