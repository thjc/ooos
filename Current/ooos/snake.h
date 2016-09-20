#pragma once
#include "process.h"

class Snake :
	public Process
{
public:
	Snake(void * Start, void * End);
	~Snake(void);

	void ProcessEntry(void** args);
};
