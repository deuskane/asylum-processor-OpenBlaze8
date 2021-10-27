// test of inserted asm code into C code
int i;

/*
asm
ENABLE_INTERRUPT;
endasm
*/

int main(void)
{
__asm
INPUT s0
__endasm;
i = 10;
return i;
}