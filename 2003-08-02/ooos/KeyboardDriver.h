#pragma once

#include "pcat.h"
#include "types.h"

#define BufferSize 64

class KeyboardDriver
{
public:
	KeyboardDriver(void);
	~KeyboardDriver(void);

	static void KeyboardISR();
	static void RawISR();
	static wchar_t GetKey();
	static bool BufferFull();
	static bool BufferEmpty();
	static int KeysBuffered();


private:
	
	//static volatile BYTE Count;
	static volatile BYTE Head;
	static volatile BYTE Tail;
	static volatile bool Full;
	static volatile wchar_t Buffer[BufferSize];
	static wchar_t CharMap[256];

	static void SetIntMask();
	static void ClearIntMask();

};
