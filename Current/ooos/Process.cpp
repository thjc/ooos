#include "process.h"
#include "global.h"
#include "VideoDriver.h"

#include "HeapAllocation.h"

unsigned int LastProcessID = 0;

Process::Process(void * Start, void * End)
{
	HeapStart = Start;
	HeapEnd = End;
	if (reinterpret_cast<unsigned long> (HeapEnd) - reinterpret_cast<unsigned long> (HeapStart) >= sizeof(HeapAllocation))
	{
		HeapHead = reinterpret_cast<HeapAllocation *> (HeapStart);
		HeapHead->AllocSize = 0;
		HeapHead->Next = NULL;
		HeapHead->Prev = NULL;
		HeapHead->SpaceSize = reinterpret_cast<unsigned long> (HeapEnd) - reinterpret_cast<unsigned long> (HeapStart) - sizeof(HeapAllocation);
	}
	else
	{
		HeapHead = NULL;
	}
	ControlBlock.ProcTSS.TaskLink = 0;
}

Process::~Process(void)
{
}

void* Process::Alloc(size_t Size) //throw(std::bad_alloc)
{
	if (HeapHead == NULL)
	{
		return NULL;
	}
	// Find a spot that will fit the request
	for (HeapAllocation * cur = HeapHead; cur != NULL; cur = cur->Next)
	{
		// if we have found it then
		if (cur->SpaceSize >= sizeof(HeapAllocation) + Size)
		{
			// Create Allocation Object
			reinterpret_cast<HeapAllocation *> (reinterpret_cast<int> (cur) + sizeof(HeapAllocation) + cur->AllocSize)->Alloc(Size, cur);
			// Return Pointer
			return reinterpret_cast<void *> (reinterpret_cast<int> (cur) + sizeof(HeapAllocation) + cur->AllocSize + sizeof(HeapAllocation));
		}
	}
	return NULL;
}

void Process::Dealloc(void* ptr) //throw()
{
	if (ptr != NULL)
		reinterpret_cast<HeapAllocation *> (reinterpret_cast<unsigned long> (ptr) - sizeof(HeapAllocation))->Dealloc();
}

HeapAllocation *Process::HeapHead;

void ProcessQueue::InsertEnd(Process * NewProc)
{
	//printf("insertend\n");
	ProcessNode * cur;
	for(cur = &Head; cur->Next != NULL; cur = cur->Next);
	/*{
		printf("cur: %d next: %d\n", cur, cur->Next);
	}*/
	cur->Next = new ProcessNode();
	if (cur->Next == NULL)
	{
		printf("Error, Could Not Allocate New Process");
		while (1);
	}
	cur->Next->Proc = NewProc;
}


Process * ProcessQueue::RemoveStart()
{
	ProcessNode * Temp = Head.Next;
	Head.Proc = Head.Next->Proc;
	Head.Next = Head.Next->Next;
	if (Temp != NULL)
	{
		delete Temp;
		return Head.Proc;
	}
	return NULL;
}

void ProcessQueue::Remove(Process * Proc)
{
	ProcessNode * prev = &Head;
	for(ProcessNode * cur = (&Head)->Next; cur != NULL; cur = cur->Next)
	{
		if (cur->Proc == Proc)
		{
			prev->Next = cur->Next;
			delete cur;
			break;
		}
		prev = cur;
	}
}

ProcessNode * ProcessQueue::Pop_Front()
{
	ProcessNode * Temp = Head.Next;
	Head.Proc = Head.Next->Proc;
	Head.Next = Head.Next->Next;
	//delete Temp;
	return Temp;
}

void ProcessQueue::Push_Back(ProcessNode * NewProc)
{
	if (NewProc == NULL)
		return;
	//printf("insertend\n");
	ProcessNode * cur;
	for(cur = &Head; cur->Next != NULL; cur = cur->Next);
	/*{
		printf("cur: %d next: %d\n", cur, cur->Next);
	}*/
	cur->Next = NewProc;
	NewProc->Next = NULL;
	//cur->Next->Proc = NewProc;
}


// Dont recall what this does but looks equiv of exec rather than spawn
// if it does anything at all....???
// Hey look slike it does do something, its called by the task the first time its switched to
void StartProcess()
{
	Process * Proc;
	__asm
	{
		MOV Proc, EAX
	}
	Proc->ProcessEntry(NULL);
	//__asm IRET
	while(1);
}

// spawns a new process.
int CreateProcess(Process * NewProc)
{
	//printf("Creating Process");
	DWORD Flags;
	__asm
	{
		PUSH EAX
		PUSHFD
		POP EAX
		MOV Flags, EAX
		POP EAX
		CLI
	};
	ActiveProcesses->InsertEnd(NewProc);
	ReadyProcesses->InsertEnd(NewProc);

	//printf("FindSlot");
	// Find a spare process slot
	int i;
	for (i = 0; GDTAddress[i * 2 + ProcessGDTOffset] != 0; ++i);
	//printf("FFound%d", i);
	//printf("pnum: %d\n", i);
	// Fill in the basic process details
	NewProc->ControlBlock.pid = ++LastProcessID;
	printf("pid:%d", NewProc->ControlBlock.pid);
	NewProc->ControlBlock.pnum = i;
	
	//printf("Set in GDT");

	// create the TSS Descriptor in the GDT for the process
	GDTAddress[i*2+ ProcessGDTOffset] = ((reinterpret_cast<const unsigned long> (&NewProc->ControlBlock.ProcTSS) & 0xFFFF) << 16 | 0x68);
	GDTAddress[i*2+1+ ProcessGDTOffset] = ((reinterpret_cast<const unsigned long> (&NewProc->ControlBlock.ProcTSS) & 0xFF000000) | (reinterpret_cast<const unsigned long> (&NewProc->ControlBlock.ProcTSS) & 0xFF0000) >> 16 | 0x008B00);

	printf("Address of new Proc TSS: %d\n", &NewProc->ControlBlock.ProcTSS);

	// set the values of the important bits of the TSS
	NewProc->ControlBlock.ProcTSS.SS = 0x10;
	NewProc->ControlBlock.ProcTSS.CS = 0x8;
	NewProc->ControlBlock.ProcTSS.DS = 0x10;
	NewProc->ControlBlock.ProcTSS.ES = 0x10;
	NewProc->ControlBlock.ProcTSS.FS = 0x10;
	NewProc->ControlBlock.ProcTSS.GS = 0x10;

	NewProc->ControlBlock.ProcTSS.ESP = reinterpret_cast<unsigned long> (NewProc->Stack) + 1023;
	NewProc->ControlBlock.ProcTSS.EAX = reinterpret_cast<unsigned long> (NewProc);
	NewProc->ControlBlock.ProcTSS.EIP = reinterpret_cast<unsigned long> (StartProcess);

	// all flags cleared excep interrupt enable and the reserved bit
	NewProc->ControlBlock.ProcTSS.EFLAGS = 0x202;



	//printf("Rest Flags");
	
	__asm
	{
		PUSH EAX
		MOV EAX, Flags
		PUSH EAX
		POPFD
		POP EAX
		// dont need STI because flags are returned to initial state
		//STI
	}
}






	