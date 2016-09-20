#pragma once

#include "types.h"

const int DisplayWidth = 80;
const int DisplayHeight = 25;

typedef struct DisplayCharacter
{
	char Character;
	BYTE Colour;
} DisplayCharacter;

typedef struct VideoPage
{
	DisplayCharacter Characters[DisplayHeight][DisplayWidth];
} VideoPage;

typedef struct CursorInfo
{
	BYTE X;
	BYTE Y;
	BYTE Colour;
} CursorInfo;

class VideoDriver
{
public:
	VideoDriver(void);
	~VideoDriver(void);

	void SetPosition(BYTE X, BYTE Y);
	void SetColour(BYTE Colour);
	void WriteString(char * String);
	void ClearScreen(void);
	void WriteHexByte(BYTE b);
private:
	void WriteChar(DisplayCharacter Char);

	VideoPage* VideoPages;
	CursorInfo Cursor;
	BYTE CurrentPage;
};
