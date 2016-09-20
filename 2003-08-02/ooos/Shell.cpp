#include "shell.h"
#include "keyboarddriver.h"
#include "videodriver.h"
#include "global.h"
#include "snake.h"


int strcmp(wchar_t* L, wchar_t * R)
{
	int i;
	for (i = 0; L[i] != NULL && R[i] != NULL; ++i)
	{
		if (L[i] > R[i])
			return 1;
		if (L[i] < R[i])
			return -1;
	}
	if (L[i] == R[i])
		return 0;
	return 1;
}

Shell::~Shell(void)
{
}


void Shell::ProcessEntry(void** args)
{
	wchar_t TempChr[2];
	TempChr[1] = 0;
	wchar_t *Buffer;
	int BuffSize = 16;
	int BuffCount = 0;
	Buffer = new wchar_t[BuffSize];
	*Buffer = '\0';
	int Temp;

	pDisp->WriteString(L"> ");

	while(1)
	{
		bool full = false;
		//printf("S");
		//i_VideoDriver.WriteHexByte(KeyboardDriver::KeysBuffered());
		//i_VideoDriver.WriteString(L" ");
		TempChr[0] = KeyboardDriver::GetKey();
		if (TempChr[0] != NULL)
		{
			if (TempChr[0] != '\n')
			{
				if (BuffCount < BuffSize -1)
				{
					Buffer[BuffCount] = TempChr[0];
					BuffCount++;
					Buffer[BuffCount] = '\0';
				}
				else
				{
					wchar_t* TempBuffer;
					TempBuffer = new wchar_t[BuffSize *2];
					if (TempBuffer != NULL)
					{
						for (int i = 0; i < BuffCount + 1; ++i)
						{
							TempBuffer[i] = Buffer[i];
						}
						delete[] Buffer;
						Buffer = TempBuffer;
						BuffSize = 2*BuffSize;
						Buffer[BuffCount] = TempChr[0];
						BuffCount++;
						Buffer[BuffCount] = '\0';
					}
					else
					{
						full = true;
					}
				}
			}
			else
			{
				// got command,s ee if we can process it
				if (strcmp(Buffer,L"snake") == 0)
				{
					// Launchign Snake
					pDisp->WriteString(L"Creating Snake Process...");
					Process * SnakeProcess = new Snake(reinterpret_cast<void *> (0xA13000), reinterpret_cast<void *> (0xA14000));
					CreateProcess(SnakeProcess);
					pDisp->WriteString(L"Done\n");
				}


				// Now clear buffer ready for enxt command
				full = false;
				BuffCount = 0;
				Buffer[0] = '\0';
			}

			if (full == false)
			{
				pDisp->WriteString(TempChr);
				if (TempChr[0] == '\n')
				{
					pDisp->WriteString(L"> ");
				}
			}
		}
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
		//Temp = KeyboardDriver::KeysBuffered();
		//while (KeyboardDriver::KeysBuffered() == Temp);



	}
}