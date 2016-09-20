#pragma once

#include "types.h"


// GDT details, if changed here need changed in bootloader
const unsigned int GDTBase = 0x800;
const unsigned int GDTEntries = 768;

// Pnum is index to TSS in GDT offset by this much
const unsigned int ProcessGDTOffset = 20;
const unsigned int ProcessMax = (GDTEntries - ProcessGDTOffset)/2;

extern unsigned int LastProcessID;

class HeapAllocation;


struct TSS
{
	WORD TaskLink;
	WORD Res0;
	DWORD ESP0;
	WORD SS0;
	WORD Res1;
	DWORD ESP1;
	WORD SS1;
	WORD Res2;
	DWORD ESP2;
	WORD SS2;
	WORD Res3;
	DWORD CR3;
	DWORD EIP;
	DWORD EFLAGS;
	DWORD EAX;
	DWORD ECX;
	DWORD EDX;
	DWORD EBX;
	DWORD ESP;
	DWORD EBP;
	DWORD ESI;
	DWORD EDI;
	WORD ES;
	WORD Res4;
	WORD CS;
	WORD Res5;
	WORD SS;
	WORD Res6;
	WORD DS;
	WORD Res7;
	WORD FS;
	WORD Res8;
	WORD GS;
	WORD Res9;
	WORD LDT;
	WORD Res10;
	WORD T;
	WORD IOMap;
};



class PCB
{
public:
	unsigned long pid;
	unsigned long pnum;
	struct TSS ProcTSS;
	int Quantum;

};




class Process
{
public:
	virtual void ProcessEntry(void** args) {};
	Process(void * Start, void * End);
	~Process(void);

	void* Alloc(size_t);// throw(std::bad_alloc);
    //void* operator new[](std::size_t) throw(std::bad_alloc);
    void Dealloc(void*); //throw();
    //void operator delete[](void*) throw();

	PCB ControlBlock;
	BYTE Stack[1024];

private:

	void * HeapStart;
	void * HeapEnd;

	static HeapAllocation *HeapHead;

};

class ProcessNode
{
public:
	ProcessNode() {Next = NULL;};

	ProcessNode *Next;
	Process * Proc;
};

class ProcessQueue
{
public:
	ProcessQueue() : Head() {};

	void InsertEnd(Process * NewProc);
	Process * RemoveStart();
	void Remove(Process *);

	ProcessNode * Pop_Front();
	void Push_Back(ProcessNode * NewProc);

//private:
	ProcessNode Head;


};

int CreateProcess(Process * NewProc);
