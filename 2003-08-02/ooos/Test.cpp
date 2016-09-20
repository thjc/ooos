
#include "VideoDriver.h"
#include "KeyboardDriver.h"
#include "TimerDriver.h"
#include "pcat.h"
#include "init.h"
#include "idle.h"
#include "shell.h"
#include "global.h"
#include "Process.h"
#include "kernel.h"



extern void Exception0();
extern void Exception1();
extern void Exception2();
extern void Exception3();
extern void Exception4();
extern void Exception5();
extern void Exception6();
extern void Exception7();
extern void Exception8();
extern void Exception9();
extern void Exception10();
extern void Exception11();
extern void Exception12();
extern void Exception13();
extern void Exception14();

struct RegDump
{
	DWORD EAX;
	DWORD EBX;
	DWORD ECX;
	DWORD EDX;
	DWORD EDI;
	DWORD ESI;
	DWORD EBP;
	DWORD ESP;
	DWORD ECODE;
	DWORD EIP;
	DWORD CS;
	DWORD EFLAGS;
	

};

struct RegDump DumpSpace;
void * pDump = &DumpSpace;

struct TSS GlobalTSS, DispatchTSS;



void Exception10_CPP()
{
//	DWORD Temp;
	//pDisp->ClearScreen();
	pDisp->SetColour(14);
	printf("Invalid TSS\n");
	printf("ECODE %d\n", DumpSpace.ECODE);
	printf("CS:EIP %d:%d\n", DumpSpace.CS, DumpSpace.EIP);
	printf("FLAGS %d\n", DumpSpace.EFLAGS);

	DWORD Temp;
	__asm STR Temp;
	printf("Current task Seg: %d\n", Temp);


	printf("Register Dump\n");
	printf("EAX: %d    EBX: %d    ECX: %d    EDX: %d\n", DumpSpace.EAX, DumpSpace.EBX, DumpSpace.ECX, DumpSpace.EDX);
	printf("EDI: %d    ESI: %d    EBP: %d    ESP: %d\n", DumpSpace.EDI, DumpSpace.ESI, DumpSpace.EBP, DumpSpace.ESP);

	/*for (int i = 0;i<6;++i)
	{
		printf("%d: %d %d\n", i, GDTAddress[i*2], GDTAddress[i*2+1]);
	}

	for (int i = 0;i<3;++i)
	{
		printf("%d: %d %d\n", i, IDTAddress[i*2], IDTAddress[i*2+1]);
	}

	for (int i = 32;i<34;++i)
	{
		printf("%d: %d %d\n", i, IDTAddress[i*2], IDTAddress[i*2+1]);
	}*/

	printf("GlobalTSS Dump\n");
	for (DWORD * i = reinterpret_cast<DWORD *> (&GlobalTSS) + (100/4); i>=reinterpret_cast<DWORD *> (&GlobalTSS); i-=4)
	{
		printf("%d %d %d %d\n", *i, *(i-1), *(i-2), *(i-3));
	}
	//printf("EAX: %d    EBX: %d    ECX: %d    EDX: %d\n", GlobalTSS.EAX, GlobalTSS.EBX, GlobalTSS.ECX, GlobalTSS.EDX);
	//printf("EDI: %d    ESI: %d    EBP: %d    ESP: %d\n", GlobalTSS.EDI, GlobalTSS.ESI, GlobalTSS.EBP, GlobalTSS.ESP);
	//printf("CS: %d     SS: %d     DS: %d     ES: %d\n", GlobalTSS.EDI, GlobalTSS.ESI, GlobalTSS.EBP, GlobalTSS.ESP);


	while(1);


}

void Exception13_CPP()
{
//	DWORD Temp;
	//pDisp->ClearScreen();
	pDisp->SetColour(14);
	printf("General Protection Fault\n");
	printf("ECODE %d\n", DumpSpace.ECODE);
	printf("CS:EIP %d:%d\n", DumpSpace.CS, DumpSpace.EIP);
	printf("FLAGS %d\n", DumpSpace.EFLAGS);

	printf("Register Dump\n");
	printf("EAX: %d    EBX: %d    ECX: %d    EDX: %d\n", DumpSpace.EAX, DumpSpace.EBX, DumpSpace.ECX, DumpSpace.EDX);
	printf("EDI: %d    ESI: %d    EBP: %d    ESP: %d\n", DumpSpace.EDI, DumpSpace.ESI, DumpSpace.EBP, DumpSpace.ESP);

	for (int i = 0;i<4;++i)
	{
		printf("%d: %d %d\n", i, GDTAddress[i*2], GDTAddress[i*2+1]);
	}
	printf("GlobalTSS Dump\n");
	for (DWORD * i = reinterpret_cast<DWORD *> (&GlobalTSS) + (100/4); i>=reinterpret_cast<DWORD *> (&GlobalTSS); i-=4)
	{
		printf("%d %d %d %d\n", *i, *(i-1), *(i-2), *(i-3));
	}


	while(1);


}


void Snake();

BYTE DispatchStack[1024];
//Init myInit();
ProcessQueue pAll;
ProcessQueue pRdy;

void KernelEntry(void)
{
	// Display start up messages
	VideoDriver i_VideoDriver;
	pDisp = &i_VideoDriver;
	i_VideoDriver.ClearScreen();
	i_VideoDriver.WriteString(L"Display Initialised\nWelcome to ");
	i_VideoDriver.SetColour(9);
	i_VideoDriver.WriteString(L"Caboose v0.0.0.1\n");
	i_VideoDriver.SetColour(15);

	Kernel ker(reinterpret_cast<void *> (0xA10000),reinterpret_cast<void *> (0xA11000));
	CurrentProcess = &ker;

	i_VideoDriver.WriteString(L"Setting up IDT (Exception Handlers) ... ");
	// set up IRQ1 (Keyboard) Interrupt Gate
	IDTAddress[0x00 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception0) & 0xFFFF0000);
	IDTAddress[0x00 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception0) & 0x0000FFFF);
	IDTAddress[0x01 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception1) & 0xFFFF0000);
	IDTAddress[0x01 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception1) & 0x0000FFFF);
	IDTAddress[0x02 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception2) & 0xFFFF0000);
	IDTAddress[0x02 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception2) & 0x0000FFFF);
	IDTAddress[0x03 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception3) & 0xFFFF0000);
	IDTAddress[0x03 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception3) & 0x0000FFFF);
	IDTAddress[0x04 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception4) & 0xFFFF0000);
	IDTAddress[0x04 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception4) & 0x0000FFFF);
	IDTAddress[0x05 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception5) & 0xFFFF0000);
	IDTAddress[0x05 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception5) & 0x0000FFFF);
	IDTAddress[0x06 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception6) & 0xFFFF0000);
	IDTAddress[0x06 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception6) & 0x0000FFFF);
	IDTAddress[0x07 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception7) & 0xFFFF0000);
	IDTAddress[0x07 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception7) & 0x0000FFFF);
	IDTAddress[0x08 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception8) & 0xFFFF0000);
	IDTAddress[0x08 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception8) & 0x0000FFFF);
	IDTAddress[0x09 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception9) & 0xFFFF0000);
	IDTAddress[0x09 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception9) & 0x0000FFFF);
	IDTAddress[0x0A * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception10) & 0xFFFF0000);
	IDTAddress[0x0A * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception10) & 0x0000FFFF);
	IDTAddress[0x0B * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception11) & 0xFFFF0000);
	IDTAddress[0x0B * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception11) & 0x0000FFFF);
	IDTAddress[0x0C * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception12) & 0xFFFF0000);
	IDTAddress[0x0C * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception12) & 0x0000FFFF);
	IDTAddress[0x0D * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception13) & 0xFFFF0000);
	IDTAddress[0x0D * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception13) & 0x0000FFFF);
	IDTAddress[0x0E * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception14) & 0xFFFF0000);
	IDTAddress[0x0E * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception14) & 0x0000FFFF);
	/*IDTAddress[0x0F * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x0F * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x10 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x10 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x11 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x11 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x12 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x12 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x13 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x13 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x14 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x14 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x15 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x15 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x16 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x16 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x17 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x17 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x18 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x18 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x19 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x19 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x1A * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x1A * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x1B * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x1B * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x1C * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x1C * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x1D * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x1D * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x1E * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x1E * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	IDTAddress[0x1F * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (Exception) & 0xFFFF0000);
	IDTAddress[0x1F * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (Exception) & 0x0000FFFF);
	*/
	i_VideoDriver.WriteString(L"Done\n");
	

	// Set up Initialiser Task bits & Bobs
	i_VideoDriver.WriteString(L"Setting Initial TSS & Dispatch TSS ... ");
	//printf("\n%d\n", reinterpret_cast<const unsigned long> (&GlobalTSS));
	GDTAddress[6] = ((reinterpret_cast<const unsigned long> (&GlobalTSS) & 0xFFFF) << 16 | 0x68);
	GDTAddress[7] = ((reinterpret_cast<const unsigned long> (&GlobalTSS) & 0xFF000000) | (reinterpret_cast<const unsigned long> (&GlobalTSS) & 0xFF0000) >> 16 | 0x008900);
	//GDTAddress[7] = ((reinterpret_cast<const unsigned long> (&GlobalTSS) & 0xFF000000) | (reinterpret_cast<const unsigned long> (&GlobalTSS) & 0xFF0000) >> 16 | 0x008B00);
	GlobalTSS.SS = 0x10;
	GlobalTSS.CS = 0x8;
	GlobalTSS.DS = 0x10;
	GlobalTSS.ES = 0x10;
	GlobalTSS.FS = 0x10;
	GlobalTSS.GS = 0x10;

	//GlobalTSS.ESP = reinterpret_cast<unsigned long> (DispatchStack) + 1023;
	//GlobalTSS.EIP = reinterpret_cast<unsigned long> (TimerDriver::RawISR);
	GlobalTSS.LDT = 0;
	GlobalTSS.TaskLink = 0;	
	/*printf("GlobalTSS Dump\n");
	for (DWORD * i = reinterpret_cast<DWORD *> (&GlobalTSS) + (100/4); i>=reinterpret_cast<DWORD *> (&GlobalTSS); i-=4)
	{
		printf("%d %d %d %d\n", *i, *(i-1), *(i-2), *(i-3));
	}*/


	__asm
	{
		PUSH ax
		MOV ax, 0x18
		LTR ax
		POP ax
	};
	//i_VideoDriver.WriteString(L"Next\n");

	// Seg 0x20, dispatch segment setup
	GDTAddress[8] = ((reinterpret_cast<const unsigned long> (&DispatchTSS) & 0xFFFF) << 16 | 0x68);
	GDTAddress[9] = ((reinterpret_cast<const unsigned long> (&DispatchTSS) & 0xFF000000) | (reinterpret_cast<const unsigned long> (&DispatchTSS) & 0xFF0000) >> 16 | 0x008900);
	DispatchTSS.SS = 0x10;
	DispatchTSS.CS = 0x8;
	DispatchTSS.DS = 0x10;
	DispatchTSS.ES = 0x10;
	DispatchTSS.FS = 0x10;
	DispatchTSS.GS = 0x10;

	DispatchTSS.ESP = reinterpret_cast<unsigned long> (DispatchStack) + 1023;
	DispatchTSS.EIP = reinterpret_cast<unsigned long> (TimerDriver::RawISR);
	DispatchTSS.LDT = 0;
	DispatchTSS.TaskLink = 0;

	i_VideoDriver.WriteString(L"Done\n");

	i_VideoDriver.WriteString(L"Setting up IDT (Interrupt Handlers) ... ");

	// Interrupt Service Routines
	IDTAddress[0x21 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (KeyboardDriver::RawISR) & 0xFFFF0000); 
	IDTAddress[0x21 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (KeyboardDriver::RawISR) & 0x0000FFFF); 
	//IDTAddress[0x20 * 2 + 1] = 0x00008E00 | (reinterpret_cast<const unsigned long> (TimerDriver::RawISR) & 0xFFFF0000); 
	//IDTAddress[0x20 * 2] = 0x00080000 | (reinterpret_cast<const unsigned long> (TimerDriver::RawISR) & 0x0000FFFF); 
	IDTAddress[0x20 * 2 + 1] = 0x8500;
	IDTAddress[0x20 * 2] = 0x200000;

	i_VideoDriver.WriteString(L"Done\n");


	i_VideoDriver.WriteString(L"Enable PIC's and interrupts ... ");
    __asm
	{
		// ICW1
		MOV al, 0x11
		OUT IO_PIC1, al
		OUT IO_PIC2, al

		// ICW2
		MOV al, 0x20
		OUT IO_PIC1+1, al

		MOV al, 0x28
		OUT IO_PIC2+1, al

		// ICW3
		MOV al, 0x04
		OUT IO_PIC1+1, al

		MOV al, 0x02
		OUT IO_PIC2+1, al

		// ICW4
		MOV al, 0x01
		OUT IO_PIC1+1, al
		OUT IO_PIC2+1, al

		// Set up the time of day counter
		MOV al, 0x37
		OUT IO_TMR + 4, al
		MOV al, 0x95
		OUT IO_TMR, al
		MOV al, 0x2e
		OUT IO_TMR, al

		// PIC's are set up
		// now unmask keybd interrupt and timer interrupt
		MOV al, 0xFC
		OUT IO_PIC1 + 1, al
		MOV al, 0xFF
		OUT IO_PIC2 + 1, al

		// Enable Interupts
		//STI
	}
	
	i_VideoDriver.WriteString(L"Done\n");
	/*__asm int 0x20;
	while(1);
	i_VideoDriver.WriteString(L"One Int\n");
	__asm int 0x20;
	i_VideoDriver.WriteString(L"Two Int\n");*/
	//while(1) printf("G");

	/*for (int i = 0; 1 ; ++i)
	{
		i_VideoDriver.WriteHexByte(i);
		i_VideoDriver.WriteString(" ");
	}*/


	//Snake();

	// Set up Process Queues
	ActiveProcesses = &pAll;
	ReadyProcesses = &pRdy;
	pAll.Head.Next = NULL;
	pRdy.Head.Next = NULL;

	//Snake();
	//while(1);
	
	// Alloc Test
	i_VideoDriver.WriteString(L"Creating Init Process...");
	Init InitProcess(reinterpret_cast<void *> (0xA11000), reinterpret_cast<void *> (0xA12000));
	CreateProcess(&InitProcess);
	i_VideoDriver.WriteString(L"Done\n");



	i_VideoDriver.WriteString(L"Creating Idle Process...");
	Idle IdleProcess(reinterpret_cast<void *> (0xA12000), reinterpret_cast<void *> (0xA13000));
	CreateProcess(&IdleProcess);
	i_VideoDriver.WriteString(L"Done\n");


	ReadyProcesses->RemoveStart();
	CurrentProcess = &InitProcess;

	// Unset the busy flag of the first process
	GDTAddress[21] &= ~0x000200;


	//__asm STI
	//while(1);
	
	__asm
	{
		//STI


		;call [0x50:0]
		_emit 0x9A
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x50
		_emit 0x00
	};



	//InitProcess.ProcessEntry(0, NULL);
	i_VideoDriver.WriteString(L"Init Process Terminated\n");
	printf("That is bad, System Halted");
    while(1);

	// interrupt test
	
	wchar_t TempChr[2];
	TempChr[1] = 0;
	int Temp;
	while(1)
	{
		printf("S");
		//i_VideoDriver.WriteHexByte(KeyboardDriver::KeysBuffered());
		//i_VideoDriver.WriteString(L" ");
		TempChr[0] = KeyboardDriver::GetKey();
		//i_VideoDriver.WriteString(TempChr);
        //i_VideoDriver.WriteString(L" ");
		//i_VideoDriver.WriteHexByte(TempChar[0]);
        //i_VideoDriver.WriteString(L"\n");

		/*BYTE Return, Command;

		Command = 0x0A;
		__asm
		{
			MOV al, Command
			OUT IO_PIC1, al
			IN al, IO_PIC1
			MOV Return, al
		}
		i_VideoDriver.WriteHexByte(Return);*/
		//i_VideoDriver.WriteString("\n");
		Temp = KeyboardDriver::KeysBuffered();
		while (KeyboardDriver::KeysBuffered() == Temp);



	}


	// Keyboard test routines
	
	
	BYTE Return, Command;

	Command = 0xF6;
	Return = 0x08;
    __asm
	{
		MOV al, Command
		OUT IO_KybdCmd, al
		OUT IO_KybdData, al
	}

	while (1)
	{
		for (Return = 0; (Return & 0x04) == 0; )
		{
		
			__asm
			{
				IN al, IO_KybdCmd
				MOV Return, al
			}
		}

		__asm
		{
			IN al, IO_KybdData
			MOV Command, al
		}
		i_VideoDriver.WriteHexByte(Return);
		i_VideoDriver.WriteString(L" ");
		i_VideoDriver.WriteHexByte(Command);
		i_VideoDriver.WriteString(L"\n");

	}
	

	// Well its gettign there slowly
	i_VideoDriver.WriteString(L"\nThats all Folks\n");

	while(1);
}


void Snake()
{
	VideoDriver vid;
	//vid.ClearScreen();
	
	unsigned long OldTicks = 0;
	unsigned char Seconds = 0;
	while (1)
	{
		while (OldTicks + 100 >= (TimerDriver::Ticks));
		OldTicks = TimerDriver::Ticks;
		if (++Seconds == 60)
			Seconds = 0;
		vid.WriteHexByte(Seconds);

	}

}
