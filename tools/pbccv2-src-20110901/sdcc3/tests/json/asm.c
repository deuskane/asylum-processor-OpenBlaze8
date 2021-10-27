// test of inserted asm code into C code
int i;

/*
asm
ENABLE_INTERRUPT;
endasm
*/

int main()
{
_asm
INPUT s0
_endasm;
i = 10;
return i;
}