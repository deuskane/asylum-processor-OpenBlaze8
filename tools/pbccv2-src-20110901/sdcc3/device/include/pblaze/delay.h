
/*
 * delay.h - delay functions header file
 *
 * adopted for SDCC and picoBlaze port by Zbynek Krivka, 2010 <krivka @ fit.vutbr.cz>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __DELAY_H__
#define __DELAY_H__


//#pragma library c

/*
 * the delayNNtcy family of functions performs a
 * delay of NN cycles. Possible values for NN are:
 *   10  10*n cycles delay
 *  100  100*n cycles delay
 *   1k  1000*n cycles delay
 *  10k  10000*n cycles delay
 * 100k  100000*n cycles delay
 *   1m  1000000*n cycles delay
 */
 
/* 
void delay10tcy(unsigned char) __wparam;
void delay100tcy(unsigned char) __wparam;
void delay1ktcy(unsigned char) __wparam;
void delay10ktcy(unsigned char) __wparam;
void delay100ktcy(unsigned char) __wparam;
void delay1mtcy(unsigned char) __wparam;
*/

void delay(unsigned char time);
//TODO: void delay(unsigned int time);

void delay(unsigned char time)
{
  volatile unsigned char i = time;
  for(; i > 0; i--)
  {
    __asm
       LOAD s2, 00
       ADD s2, 01

       LOAD s1, 00
rpt22: 
       ADD s1, 01

       LOAD s0, 00
rpt11: 
       ADD s0, 01
       JUMP NZ, rpt11

       COMPARE s1, 00
       JUMP NZ, rpt22   
      
    __endasm;             
  }       
}
#endif
