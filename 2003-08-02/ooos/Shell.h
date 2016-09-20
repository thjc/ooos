#pragma once
#include "process.h"

class Shell : public Process
{
public:
	Shell(void * Start, void * End) : Process(Start, End) {};
	~Shell(void);
	void ProcessEntry(void** args);
};
