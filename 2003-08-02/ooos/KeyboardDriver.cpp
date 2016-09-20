#include "keyboarddriver.h"

//volatile BYTE KeyboardDriver::Count = 0;
volatile BYTE KeyboardDriver::Head = 0;
volatile BYTE KeyboardDriver::Tail = 0;
volatile bool KeyboardDriver::Full = false;
volatile wchar_t KeyboardDriver::Buffer[BufferSize];

wchar_t KeyboardDriver::CharMap[256] = {
		0, // 0
		0, // 1 
		'1', // 2  
		'2', // 3
		'3', // 4
		'4', // 5
		'5', // 6
		'6', // 7
		'7', // 8
		'8', // 9
		'9', // 10
		'0', // 11
		'-', // 12
		'=', // 13
		'\b', // 14
		'\t', // 15
		'q', // 16
		'w', // 17
		'e', // 18
		'r', // 19
		't', // 20
		'y', // 21
		'u', // 22
		'i', // 23
		'o', // 24
		'p', // 25
		'[', // 26
		']', // 27
		'\n', // 28
		0, // 29 - Ctrl Key
		'a', // 30
		's', // 31
		'd', // 32
		'f', // 33
		'g', // 34
		'h', // 35
		'j', // 36
		'k', // 37
		'l', // 38
		';', // 39
		'\'', // 40
		'`', // 41
		0, // 42 Shift Left
		'\\', // 43
		'z', // 44
		'x', // 45
		'c', // 46
		'v', // 47
		'b', // 48
		'n', // 49
		'm', // 50
		',', // 51
		'.', // 52
		'/', // 53
		0, // 54 Shift Right
		0, // 55 Print Screen
		0, // 56 Left Alt
		' ' // 57

};
		

KeyboardDriver::KeyboardDriver(void)
{
}


void KeyboardDriver::KeyboardISR()
{
	BYTE KeyCode, Status;
	__asm
	{
		// Read status byte from keyboard controller
		//MOV al, 0xD0
		//OUT 0x64, al
		
		IN al, 0x64
		MOV Status, al
	}
	if ((Status & 1) == 1)
	{

		__asm 
		{
			

			// Read KeyStroke from Keyboard Controller (Clears Interrupt flag on controller)
			IN al, 0x60
			MOV KeyCode, al
		}
		// Check if it is a make or break code
		// For the moment discard the break codes
		if (KeyCode < 128)
		{
			wchar_t CharCode = CharMap[KeyCode];
			// add new charater
			if (!Full)
			{
				Buffer[Tail] = CharCode;

				if (++Tail == BufferSize)
					Tail = 0;
				if (Tail == Head)
					Full = true;
			}
		}
	}
}


// Mask Keyboard Interrupt in PIC
void KeyboardDriver::SetIntMask()
{
	__asm 
	{
		IN al, IO_PIC1 + 1
		OR al, PIC_KEY_MSK
		OUT IO_PIC1 + 1, al
	}
}

// Enable Keyboard Interrupt in PIC
void KeyboardDriver::ClearIntMask()
{
	__asm 
	{
		IN al, IO_PIC1 + 1
		AND al, ~PIC_KEY_MSK
		OUT IO_PIC1 + 1, al
	}
}

// True if buffer is full
bool KeyboardDriver::BufferFull()
{
	bool Temp;
	KeyboardDriver::SetIntMask();
	//Temp = (Head == Tail-1) || (Head == 0 && Tail == BufferSize);
	Temp = Full;
	KeyboardDriver::ClearIntMask();
	return Temp;
	
}

// true if buffer is empty
bool KeyboardDriver::BufferEmpty()
{
	bool Temp;
	KeyboardDriver::SetIntMask();
	Temp = (Head == Tail);
	KeyboardDriver::ClearIntMask();
	return Temp;
}

int KeyboardDriver::KeysBuffered()
{
	int Temp;
	KeyboardDriver::SetIntMask();
	if (Full)
		Temp = BufferSize;
	else if (Head > Tail)
		Temp = BufferSize - (Head - Tail) + 1;
	else
		Temp = Tail - Head;
	
	KeyboardDriver::ClearIntMask();
	return Temp;
}

wchar_t KeyboardDriver::GetKey()
{
	wchar_t Temp;
	KeyboardDriver::SetIntMask();
	// if empty return null
	if (BufferEmpty())
		Temp = NULL;
	else
	// other wise return first chracter and increment head, adjust ofr end of buffer
	{
		Temp = Buffer[Head];
		if (++Head == BufferSize)
			Head = 0;
		Full = false;
	}

	KeyboardDriver::ClearIntMask();
	return Temp;
}