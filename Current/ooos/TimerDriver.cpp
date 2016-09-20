#include "timerdriver.h"
#include "global.h"
#include "process.h"
#include "videodriver.h"

volatile unsigned long TimerDriver::Ticks = 0;

TimerDriver::TimerDriver(void)
{
}

TimerDriver::~TimerDriver(void)
{
}


void TimerDriver::TimerISR(void)
{
	//__asm CLI;
	/*DWORD Temp;
	__asm STR Temp
	printf("Current task Seg: %d\n", Temp);

	__asm PUSH EAX;
	__asm PUSHF;
	__asm POP EAX;
	__asm MOV Temp, EAX;
	__asm POP EAX;
	printf("Current Flags: %d\n", Temp);*/


	while(1) printf("T");
	//printf("Tick");
    TimerDriver::Ticks++;
	
	//printf("TaskLink: %d\n", DispatchTSS.TaskLink);


	//return;
	

	if ((Ticks & 0xFF)== 0)
	{
	//printf("T");
	int pnum = CurrentProcess->Proc->ControlBlock.pnum;
	printf("Switch to %d\n",pnum);
	ProcessNode * NewProcess = ReadyProcesses->Pop_Front();
	//printf("%d",reinterpret_cast<unsigned long> (NewProcess));
	if (NewProcess != NULL)
	{
		//printf("Switching Tasks\n");
		// Modify the return link for the interrupt
		DispatchTSS.TaskLink = (pnum + (ProcessGDTOffset/2)) << 3;
		ReadyProcesses->Push_Back(CurrentProcess);
		CurrentProcess = NewProcess;
	}
	}

}
