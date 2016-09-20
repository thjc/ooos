#include "idle.h"
#include "videodriver.h"
#include "global.h"

Idle::Idle(void * Start, void * End) : Process(Start, End)
{
}

Idle::~Idle(void)
{
}

void Idle::ProcessEntry(void ** args)
{
	while(1);
}
