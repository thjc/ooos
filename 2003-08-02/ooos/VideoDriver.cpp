#include "videodriver.h"
#include "pcat.h"

VideoDriver::VideoDriver(void)
{
	this->CurrentPage = 0;
	this->Cursor.Colour = 15;
	this->VideoPages = reinterpret_cast<VideoPage *> (0xb8000);
}

VideoDriver::~VideoDriver(void)
{
}

void VideoDriver::ClearScreen()
{
	for (BYTE x = 0; x < DisplayWidth; ++x)
	{
		for (BYTE y = 0; y < DisplayHeight ; ++y)
		{
			this->VideoPages[this->CurrentPage].Characters[y][x].Character = ' ';
		}
	}
}

void VideoDriver::SetColour(BYTE NewColour)
{
	this->Cursor.Colour = NewColour;

}

void VideoDriver::SetPosition(BYTE x, BYTE y)
{
	this->Cursor.X = x;
	this->Cursor.Y = y;
}

void VideoDriver::SetPosition(Point pt)
{
	this->Cursor.X = pt.X;
	this->Cursor.Y = pt.Y;
}

Point VideoDriver::GetPosition()
{
	return Point(this->Cursor.X, this->Cursor.Y);
}

void VideoDriver::WriteChar(DisplayCharacter Char)
{
	if (Char.Character == '\n')
	{
		this->Cursor.X = 0;
			if ( ++(this->Cursor.Y) == DisplayHeight)
			{
				// scroll
				--Cursor.Y;

				for (int Y = 0; Y < DisplayHeight -1;++Y)
				{
                    for (int X = 0; X < DisplayWidth; ++X)
					{
						VideoPages[this->CurrentPage].Characters[Y][X] = VideoPages[this->CurrentPage].Characters[Y+1][X];
					}
				}
                for (int X = 0; X < DisplayWidth; ++X)
				{
					VideoPages[this->CurrentPage].Characters[DisplayHeight-1][X] = DisplayCharacter(0,0);
				}

				//this->Cursor.Y = 0;
			}
	}
	else if (Char.Character == '\b')
	{
		//Cursor.X = 3;
		if ((this->Cursor.X) == 0)
		{
			Cursor.X = DisplayWidth;
			if ((this->Cursor.Y) == 0)
			{
				Cursor.Y = 1;//DisplayHeight;
			}
			Cursor.Y--;
		}
		Cursor.X--;
		DisplayCharacter Temp;
		Temp.Character = ' ';
		Temp.Colour = 15;
		this->VideoPages[this->CurrentPage].Characters[this->Cursor.Y][this->Cursor.X] = Temp;

	}
	else
	{
		this->VideoPages[this->CurrentPage].Characters[this->Cursor.Y][this->Cursor.X] = Char;
		if (++(this->Cursor.X) == DisplayWidth)
		{
			this->Cursor.X = 0;
			if ( ++(this->Cursor.Y) == DisplayHeight)
			{
				// scroll
				--Cursor.Y;

				for (int Y = 0; Y < DisplayHeight -1;++Y)
				{
                    for (int X = 0; X < DisplayWidth; ++X)
					{
						VideoPages[this->CurrentPage].Characters[Y][X] = VideoPages[this->CurrentPage].Characters[Y+1][X];
					}
				}
                for (int X = 0; X < DisplayWidth; ++X)
				{
					VideoPages[this->CurrentPage].Characters[DisplayHeight-1][X] = DisplayCharacter(0,0);
				}

				//this->Cursor.Y = 0;
			}
		}
	}
	// Set cursor location
	WORD CurAd = 40;//Cursor.GetCursorAddress();
	__asm
	{
		PUSH AX;
		PUSH DX;

		/*MOV AL, 0xA
		MOV DX, CRT_6845_REG_SEL;
		OUT DX, AL;
		MOV AL, 0x9;
		MOV DX, CRT_6845_REG_DATA;
		OUT DX, AL
		MOV AL, 0xB
		MOV DX, CRT_6845_REG_SEL;
		OUT DX, AL;
		MOV AL, 0x9;
		MOV DX, CRT_6845_REG_DATA;
		OUT DX, AL*/


		
		MOV AL, 0xF
		MOV DX, CRT_6845_REG_SEL;
		OUT DX, AL;
		MOV AX, CurAd;
		MOV DX, CRT_6845_REG_DATA;
		OUT DX, AL

		MOV AL, 0xE
		MOV DX, CRT_6845_REG_SEL;
		OUT DX, AL;
		MOV AL, AH;
		MOV DX, CRT_6845_REG_DATA;
		OUT DX, AL

		POP DX
		POP AX
	}

	
}

void VideoDriver::WriteString(wchar_t * String)
{
	DisplayCharacter TempChar;
	TempChar.Colour = this->Cursor.Colour;
	for (unsigned long i = 0; String[i] != '\0' && i != -1; ++i)
	{
		TempChar.Character = static_cast <BYTE> (String[i]);
		this->WriteChar(TempChar);
	}
}


void VideoDriver::WriteHexByte(BYTE b)
{
	DisplayCharacter TempChar;
	TempChar.Colour = this->Cursor.Colour;
	TempChar.Character = (b >> 4) < 10 ? (b >> 4) + '0' : (b >> 4) + 'A' - 10;
	this->WriteChar(TempChar);
	TempChar.Character = (b & 0xF) < 10 ? (b & 0xF) + '0' : (b & 0xF) + 'A' - 10;
	this->WriteChar(TempChar);
}


void VideoDriver::DebugPrint(void * ptr)
{
	WriteString(L"Ptr: ");
	DebugPrint(reinterpret_cast<unsigned long> (ptr));
}

void VideoDriver::DebugPrint(unsigned long num)
{
	WriteString(L"0x");	
	WriteHexByte(num >> 24);
	WriteHexByte(num >> 16);
	WriteHexByte(num >> 8);
	WriteHexByte(num);
	WriteString(L" ");
}


