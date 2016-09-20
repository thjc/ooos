#pragma once
#include "process.h"

class Init :
	public Process
{
public:
	Init(void * Start, void * End);
	~Init(void);
	void ProcessEntry(void **);
};
