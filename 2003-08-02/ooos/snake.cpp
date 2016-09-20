#include "snake.h"
#include "videodriver.h"
#include "global.h"

Snake::Snake(void * Start, void * End) : Process(Start, End)
{
}

Snake::~Snake(void)
{
}


void Snake::ProcessEntry(void** args)
{
	int Temp = 0;
	while(1) 
	{
		__asm CLI;
		Point OldPoint = pDisp->GetPosition();
		pDisp->SetPosition(70,20);
		printf("%d", Temp++);
		pDisp->SetPosition(OldPoint);
		__asm STI;
		//break;
	}
}

