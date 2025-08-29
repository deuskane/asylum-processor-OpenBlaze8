#include <stdint.h>
#include "testbench.h"

uint32_t uadd16(uint16_t i0, uint16_t i1)
{
  uint32_t res = (uint32_t)i0+(uint32_t)i1;
  return res;
}

void main()
{
  uint16_t x          = 0x0000beef;
  uint16_t y          = 0x0000deca;
  uint32_t z;
  uint32_t z_expected = 0x00019DB9;
 
  z = uadd16(x,y);

  watch32b(x);
  watch32b(y);
  watch32b(z);
  
  if (z != z_expected)
    TEST_KO;

  TEST_OK;
}
