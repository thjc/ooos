#pragma once

#include "pcat.h"
#include "types.h"

class KeyboardDriver
{
public:
	KeyboardDriver(void);
	~KeyboardDriver(void);


	static void KeyboardISR();

	static volatile BYTE Count;

};
