#pragma once

#include "types.h"

const int DisplayWidth = 80;
const int DisplayHeight = 25;

void printf(const char *arg, ...);

class Point
{
public:
	int X;
	int Y;
	Point(int StartX, int StartY) {X = StartX; Y= StartY;};
	Point() {X = 0; Y= 0;};
};

typedef struct DisplayCharacter
{
	DisplayCharacter(BYTE Char, BYTE Col) {Character = Char; Colour = Col;};
	DisplayCharacter() {};
	BYTE Character;
	BYTE Colour;
} DisplayCharacter;

typedef struct VideoPage
{
	DisplayCharacter Characters[DisplayHeight][DisplayWidth];
} VideoPage;

class CursorInfo
{
public:
	BYTE X;
	BYTE Y;
	BYTE Colour;
	WORD GetCursorAddress() {return (Y * 80) + X;};

};

class VideoDriver
{
public:
	VideoDriver(void);
	~VideoDriver(void);

	void SetPosition(BYTE X, BYTE Y);
	void SetPosition(Point pt);
	Point GetPosition();

	void SetColour(BYTE Colour);
	void WriteString(wchar_t * String);
	void ClearScreen(void);
	void WriteHexByte(BYTE b);

	void DebugPrint(void * ptr);
	void DebugPrint(unsigned long num);

private:
	void WriteChar(DisplayCharacter Char);

	VideoPage* VideoPages;
	CursorInfo Cursor;
	BYTE CurrentPage;
};
