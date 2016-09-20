#pragma once

#include "process.h"

class Process;
class ProcessNode;
class VideoDriver;
extern ProcessNode * CurrentProcess;
extern VideoDriver * pDisp;

extern ProcessQueue * ActiveProcesses;
extern ProcessQueue * ReadyProcesses;
extern struct TSS DispatchTSS;


	void* operator new(size_t);// throw(std::bad_alloc);
    //void* operator new[](std::size_t) throw(std::bad_alloc);
    void operator delete(void*); //throw();
    //void operator delete[](void*) throw();


extern unsigned long * IDTAddress; // interrupt table address base
extern unsigned long * GDTAddress; // global segment table address base