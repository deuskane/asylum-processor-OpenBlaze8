/*
 * intr.h - Interrupts functions header file for FITKit
 *
 * adopted for SDCC and picoBlaze port by Zbynek Krivka, 2010 <krivka @ fit.vutbr.cz>
 *
*/

#ifndef __INTR_H__
#define __INTR_H__

#define KCPSM

#ifdef KCPSM
#define EINT  ENABLE INTERRUPT
#define DINT  DISABLE INTERRUPT
#else
#define EINT  EINT
#define DINT  DINT
#endif

#define BOOL unsigned char

void pbcc_enable_interrupt(void);
void pbcc_disable_interrupt(void);
//inline bool pbcc_enabled_interrupt();
//void pbcc_set_interrupt_handler(void *(void))
//void pbcc_set_interrupt(BOOL enable);


void pbcc_enable_interrupt(void)
{
   __asm
       EINT
   __endasm;
}

void pbcc_disable_interrupt(void)
{
  __asm;   
      DINT
  __endasm;
}
/*
void pbcc_set_interrupt(BOOL enable)
{
  if (enable)
  {
     pbcc_enable_interrupt();
  }
  else
  {
     pbcc_disable_interrupt();
  }

}
*/
#endif


