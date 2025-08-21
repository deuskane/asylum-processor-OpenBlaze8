#include <stdint.h>
#include "testbench.h"

uint32_t uadd32(uint32_t i0, uint32_t i1)
{
  return i0+i1;
}

void main()
{
  uint32_t x          = 0xdeadbeef;
  uint32_t y          = 0xcafedeca;
  uint32_t z;
  uint32_t z_expected = 0xA9AC9DB9;
 
  z = uadd32(x,y);

  watch32b(x);
  watch32b(y);
  watch32b(z);
  
  if (z != z_expected)
    TEST_KO;

  TEST_OK;
}
