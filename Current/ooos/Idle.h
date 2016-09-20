#pragma once
#include "process.h"
#include "videodriver.h"

class Idle :
	public Process
{
public:
	Idle(void * Start, void * End);
	~Idle(void);

	void ProcessEntry(void** args);// {printf("I");};};
};
