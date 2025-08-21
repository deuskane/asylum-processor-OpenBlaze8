#ifndef _testbench_h
#define _testbench_h

// define portu
extern char PBLAZEPORT[];

#define PORT_WR(_ADDR_,_DATA_) PBLAZEPORT[(_ADDR_)] = (_DATA_)
#define PORT_RD(_ADDR_)        PBLAZEPORT[(_ADDR_)]

#define LED           0x20
#define IT            0xff
#define SWITCH        0x00
#define TEST          0xe0
#define WATCH0        0xc0
#define WATCH1        0xc1
#define WATCH2        0xc2
#define WATCH3        0xc3
#define TEST_KO       do {PORT_WR(TEST,0xED);} while (0)
#define TEST_OK       do {PORT_WR(TEST,0xFA);} while (0)

#define watch32b(_DATA_) do {PORT_WR(WATCH0,(_DATA_)&0xFF); PORT_WR(WATCH1,((_DATA_)>>8)&0xFF);PORT_WR(WATCH2,((_DATA_)>>16)&0xFF);PORT_WR(WATCH3,((_DATA_)>>24)&0xFF);} while (0)


#endif
