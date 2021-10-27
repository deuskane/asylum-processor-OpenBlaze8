/*
 * lcd.h - LCD peripheral functions header file for FITKit
 *
 * adopted for SDCC and picoBlaze port by Zbynek Krivka, 2010 <krivka @ fit.vutbr.cz>
 *
*/

#ifndef __LCD_H__
#define __LCD_H__

#include "delay.h"
#include "port.h"

#define port_lcd_high 41
#define port_lcd_low 40
#define LCD_CLEAR_DISPLAY  01
#define LCD_wr(arg)   __port_write(0x40, (arg)); __port_write(0x41, 01) 
#define MIN_PAUSE 10

void LCD_clear(void);
void LCD_init(void);
void LCD_set_cursor(void);
void LCD_write(unsigned char ch);

void LCD_clear(void)
{
  __asm
       ; LCD clear
       LOAD s6, LCD_CLEAR_DISPLAY
       OUTPUT s6, port_lcd_low
       LOAD s6, 00
       OUTPUT s6, port_lcd_high
  __endasm;
  delay(MIN_PAUSE);
}

void LCD_set_cursor()
{
  __asm;   
      ; LCD - set cursor at the line beginning
       LOAD s6, 80
       OUTPUT s6, port_lcd_low
       LOAD s6, 00
       OUTPUT s6, port_lcd_high
  __endasm;
  delay(MIN_PAUSE); 
}

void LCD_init()
{
  __asm
       ; LCD clear
       LOAD s6, LCD_CLEAR_DISPLAY
       OUTPUT s6, port_lcd_low
       LOAD s6, 00
       OUTPUT s6, port_lcd_high
  __endasm;
  delay(MIN_PAUSE);    
  __asm
       ; LCD function set - 8-bit carry, display consists of 2 parts, font 5x8
       LOAD s6, 38
       OUTPUT s6, port_lcd_low
       LOAD s6, 00
       OUTPUT s6, port_lcd_high
  __endasm;
  delay(MIN_PAUSE);    
  __asm
       ; LCD display - show the cursor, turn the display ON
       LOAD s6, 0E
       OUTPUT s6, port_lcd_low
       LOAD s6, 00
       OUTPUT s6, port_lcd_high
  __endasm;
  delay(MIN_PAUSE);           
  __asm
       ; LCD entry mode - increment cursor address automatically
       LOAD s6, 06
       OUTPUT s6, port_lcd_low
       LOAD s6, 00
       OUTPUT s6, port_lcd_high
  __endasm;
      
  LCD_set_cursor();

  delay(MIN_PAUSE);
}

void LCD_write(unsigned char ch)
{
   __port_write(0x40, ch); 
   __port_write(0x41, 01);
}

#endif


