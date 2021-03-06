#include "global.h"

#include "process.h"
#include "videodriver.h"
Process * CurrentProcess = NULL;
VideoDriver * pDisp = NULL;

ProcessQueue * ActiveProcesses;
ProcessQueue * ReadyProcesses;

unsigned long * IDTAddress =  (0x0); // interrupt table address base
unsigned long * GDTAddress = reinterpret_cast<unsigned long *> (GDTBase); // global segment table address base

/*extern "C" int __cdecl __purecall(void)
{
  return 0;
}*/


	void* operator new(size_t sz)
	{
		if (CurrentProcess != NULL)
		{
			return CurrentProcess->Alloc(sz);
		}
		return NULL;
	}

    void operator delete(void* ptr)
	{
		if (CurrentProcess != NULL)
		{
			CurrentProcess->Dealloc(ptr);
		}
	}
