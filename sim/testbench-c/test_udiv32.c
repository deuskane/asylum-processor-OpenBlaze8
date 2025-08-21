#include <stdint.h>
#include "testbench.h"

uint32_t udiv32(uint32_t i0, uint32_t i1)
{
  return i0/i1;
}

void main()
{
  uint32_t x          = 0xdeadbeef;
  uint32_t y          = 0x0000cafe;
  uint32_t z;
  uint32_t z_expected = 0x000118D3;

  z = udiv32(x,y);

  watch32b(x);
  watch32b(y);
  watch32b(z);
  
  if (z != z_expected)
    TEST_KO;

  TEST_OK;
}
