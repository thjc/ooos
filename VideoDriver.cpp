#include "videodriver.h"

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

void VideoDriver::WriteChar(DisplayCharacter Char)
{
	if (Char.Character == '\n')
	{
		this->Cursor.X = 0;
		if ( ++(this->Cursor.Y) > DisplayHeight)
			this->Cursor.Y = 0;
	}
	else
	{
		this->VideoPages[this->CurrentPage].Characters[this->Cursor.Y][this->Cursor.X] = Char;
		if (++(this->Cursor.X) > DisplayWidth)
		{
			this->Cursor.X = 0;
			if ( ++(this->Cursor.Y) > DisplayHeight)
				this->Cursor.Y = 0;
		}
	}
}

void VideoDriver::WriteString(char * String)
{
	DisplayCharacter TempChar;
	TempChar.Colour = this->Cursor.Colour;
	for (unsigned long i = 0; String[i] != '\0' && i != -1; ++i)
	{
		TempChar.Character = String[i];
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



