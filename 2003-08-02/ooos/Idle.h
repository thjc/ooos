#pragma once
#include "process.h"

class Idle :
	public Process
{
public:
	Idle(void * Start, void * End);
	~Idle(void);

	void ProcessEntry(void** args) {while(1);};
};
