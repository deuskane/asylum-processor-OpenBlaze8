#include <stdint.h>
#include "testbench.h"

uint16_t udiv16(uint16_t i0, uint16_t i1)
{
  return i0/i1;
}

void main()
{
  uint16_t x,y;
  uint16_t z,z_expected;

  if (1)
    {
      x          = 0x0000bebe;
      y          = 0x00000911;
      z_expected = 0x00000015;

      watch32b(x);
      watch32b(y);

      z          = udiv16(x,y);

      watch32b(z);
    
      if (z != z_expected)
	TEST_KO;
    }

  if (1)
    {
      x          = 0x00000911;
      y          = 0x00001234;
      z_expected = 0x00000000;

      watch32b(x);
      watch32b(y);

      z          = udiv16(x,y);

      watch32b(z);
    
      if (z != z_expected)
	TEST_KO;
    }

  if (1)
    {
      x          = 0x0000cafe;
      y          = 0x00000021;
      z_expected = 0x00000626;

      watch32b(x);
      watch32b(y);

      z          = udiv16(x,y);

      watch32b(z);
    
      if (z != z_expected)
	TEST_KO;
    }

  TEST_OK;
}
