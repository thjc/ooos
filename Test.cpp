/*#include "BinaryStore.h"


void main()
{
	BYTE * Buffer;
	BinaryStore * MyStore = new BinaryStore(10);
	MyStore->Write(4, reinterpret_cast<BYTE *> ("Boo"));
	Buffer = MyStore->Read(4);
}*/

unsigned long * IDTAddress = reinterpret_cast<unsigned long *> (0x0); // interrupt table address base
unsigned long * GDTAddress = reinterpret_cast<unsigned long *> (0x800); // global segment table address base

#include "VideoDriver.h"
#include "KeyboardDriver.h"
#include "pcat.h"

void KernelEntry(void)
{
	// Display start up messages
	VideoDriver i_VideoDriver;
	i_VideoDriver.ClearScreen();
	i_VideoDriver.WriteString("Display Initialised\nWelcome to ");
	i_VideoDriver.SetColour(9);
	i_VideoDriver.WriteString("Caboose v0.0\n");
	i_VideoDriver.SetColour(15);

	i_VideoDriver.WriteString("Setting up IDT ... ");
	// set up IRQ1 (Keyboard) Interrupt Gate
	IDTAddress[0x21 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (KeyboardDriver::KeyboardISR) & 0xFFFF0000); 
	IDTAddress[0x21 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (KeyboardDriver::KeyboardISR) & 0x0000FFFF); 
	i_VideoDriver.WriteString("Done\n");

	i_VideoDriver.WriteString("Enable PIC's and interrupts ... ");
    __asm
	{
		// ICW1
		MOV al, 0x11
		OUT IO_PIC1, al
		OUT IO_PIC2, al

		// ICW2
		MOV al, 0x20
		OUT IO_PIC1+1, al

		MOV al, 0x28
		OUT IO_PIC2+1, al

		// ICW3
		MOV al, 0x04
		OUT IO_PIC1+1, al

		MOV al, 0x02
		OUT IO_PIC2+1, al

		// ICW4
		MOV al, 0x01
		OUT IO_PIC1+1, al
		OUT IO_PIC2+1, al

		// PIC's are set up
		// now unmask keybd interrupt
		MOV al, 0xFD
		OUT IO_PIC1 + 1, al
		MOV al, 0xFF
		OUT IO_PIC2 + 1, al

		// Enable Interupts
		STI
	}

	i_VideoDriver.WriteString("Done\n");

	
	
	for (int i = 0, 1, ++i)
	{
		i_VideoDriver.WriteHexByte(i);
		i_VideoDriver.WriteString(" ");
	}

	// interrupt test
	while(1)
	{
		i_VideoDriver.WriteHexByte(KeyboardDriver::Count);
		i_VideoDriver.WriteString(" ");

		BYTE Return, Command;

		Command = 0x0A;
		__asm
		{
			MOV al, Command
			OUT IO_PIC1, al
			IN al, IO_PIC1
			MOV Return, al
		}
		i_VideoDriver.WriteHexByte(Return);
		i_VideoDriver.WriteString("\n");


	}



	// Keyboard test routines
	
	
	BYTE Return, Command;

	Command = 0xF6;
	Return = 0x08;
    __asm
	{
		MOV al, Command
		OUT IO_KybdCmd, al
		OUT IO_KybdData, al
	}

	while (1)
	{
		for (Return = 0; (Return & 0x04) == 0; )
		{
		
			__asm
			{
				IN al, IO_KybdCmd
				MOV Return, al
			}
		}

		__asm
		{
			IN al, IO_KybdData
			MOV Command, al
		}
		i_VideoDriver.WriteHexByte(Return);
		i_VideoDriver.WriteString(" ");
		i_VideoDriver.WriteHexByte(Command);
		i_VideoDriver.WriteString("\n");

	}
	

	// Well its gettign there slowly
	i_VideoDriver.WriteString("\nThats all Folks\n");

	while(1);
}