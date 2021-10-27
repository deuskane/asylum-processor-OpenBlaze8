/*-------------------------------------------------------------------------

  Json

  device.c - Accomodates subtle variations in JSON devices

   Written By -  Scott Dattalo scott@dattalo.com

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 2, or (at your option) any
   later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
-------------------------------------------------------------------------*/

/*
  PIC device abstraction

  There are dozens of variations of PIC microcontrollers. This include
  file attempts to abstract those differences so that SDCC can easily
  deal with them.
*/

#ifndef  __JSON_DEVICE_H__
#define  __JSON_DEVICE_H__


#define PROCESSOR_NAMES    4
/* Processor unique attributes */

typedef struct JSON_device {
  char *name[PROCESSOR_NAMES];  /* aliases for the processor name */
  /* RAMsize *must* be the first item to copy for 'using' */
  int RAMsize;			/* size of Data RAM - VR 031120 */
  int acsSplitOfs;		/* access bank split offset */
//  configWordsInfo_t cwInfo;	/* configuration words info */
//  idBytesInfo_t idInfo;		/* ID Locations info */
  /* next *must* be the first field NOT being copied via 'using' */
  struct JSON_device *next;    /* linked list */
} JSON_device;

extern JSON_device *picoBlaze;

typedef struct {
  int json_flag;		// JSON flag if to do the dump of iCodes in JSON format
  char *json_dumpfile;  // name of the JSON dump file
} json_options_t;

extern json_options_t json_options;


#endif  /* __JSON_DEVICE_H__ */

