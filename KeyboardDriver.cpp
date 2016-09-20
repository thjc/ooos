#include "keyboarddriver.h"

volatile BYTE KeyboardDriver::Count = 0;

KeyboardDriver::KeyboardDriver(void)
{
}

KeyboardDriver::~KeyboardDriver(void)
{
}


// interrupt handler
/*
void KeyboardDriver::KeyboardISR()  
{
	Count++;

	// clear PIC flag and then return from interrupt
	__asm
	{	
		MOV al, 0x20
		OUT IO_PIC1, al
		
	//	IRET
	}
	//while(1);
}*/




