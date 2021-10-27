#include <stdint.h>

// define portu
extern char PBLAZEPORT[];

#define PORT_WR(_ADDR_,_DATA_) PBLAZEPORT[_ADDR_] = _DATA_
#define PORT_RD(_ADDR_)        PBLAZEPORT[_ADDR_]

#define LED       0x20
#define IT        0xff
#define SWITCH    0x00
#define TEST      0xe0
#define TEST_KO   PORT_WR(TEST,0xED)
#define TEST_OK   PORT_WR(TEST,0xFA)

uint32_t umul32(uint32_t i0, uint32_t i1)
{
  return i0*i1;
}

void main()
{
  uint32_t x          = 0xdeadbeef;
  uint32_t y          = 0xcafedeca;
  uint32_t z;
//uint64_t z_expected = 0xB092CAD667CDEA96;
  uint32_t z_expected = 0x67CDEA96;

  z = umul32(x,y);

  if (z == z_expected)
    TEST_OK;

  TEST_KO;
}
