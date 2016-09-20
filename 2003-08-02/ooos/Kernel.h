#pragma once
#include "process.h"

class Kernel :
	public Process
{
public:
	Kernel(void * Start, void * End);
	~Kernel(void);
};
