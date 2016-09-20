#include "init.h"
#include "videodriver.h"
#include "global.h"
#include "heapallocation.h"
#include "videodriver.h"
#include "timerdriver.h"
#include "shell.h"

Init::Init(void * Start, void * End) : Process(Start, End)
{
}

Init::~Init(void)
{
}

Process * ShellProcess;//(reinterpret_cast<void *> (0xA13000), reinterpret_cast<void *> (0xA14000));

void Init::ProcessEntry(void** args)
{
	// Create the shell process
	pDisp->WriteString(L"Creating Shell Process...");
	ShellProcess = new Shell(reinterpret_cast<void *> (0xA13000), reinterpret_cast<void *> (0xA14000));
	CreateProcess(ShellProcess);
	pDisp->WriteString(L"Done\n");


	/*int * Test;

	for (int i = 1; i < 7; i++)
	{
		Test = new int;
		if (Test != NULL)
		{
			*Test = i;
			pDisp->WriteHexByte(*Test);
			delete Test;
		}
		else
			pDisp->WriteHexByte(-1);
		pDisp->WriteString(L"\n");


	}*/
	/*int Temp = 0;
	while(1) 
	{
		__asm CLI;
		Point OldPoint = pDisp->GetPosition();
		pDisp->SetPosition(70,20);
		printf("%d", Temp++);
		pDisp->SetPosition(OldPoint);
		__asm STI;
		//break;
	}*/
}
