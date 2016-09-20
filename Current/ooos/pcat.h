#ifndef _PCAT_H
#define _PCAT_H


#include "types.h"

#define IO_PIC1 0x20
#define IO_PIC2 0xA0
#define IO_KybdData 0x60
#define IO_KybdCmd 0x64
#define IO_TMR 0x40


#define PIC_KEY_MSK 0x02 
#define PIC_TMR_MSK 0x01

#define CRT_6845_REG_SEL 0x3d4
#define CRT_6845_REG_DATA 0x3d5


#endif