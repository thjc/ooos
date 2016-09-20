#include <stdio.h>
#include <iostream>
using namespace std;
#include "main.h"

int main(int argc, char * argv[])
{
	FILE *exe, *bin;

	if (argc < 3)
	{
		cout << "Wrong number of arguments" << endl << "Usage: " << argv[0] << " <exe file> <bin filename>" << endl;
		return 1;
	}

	// open exe file
	exe = fopen(argv[1],"rb");
	if (exe == NULL)
	{
		cout << "Error Opening exe file" <<  endl;
		return 1;
	}

	// open binary output file
	bin = fopen(argv[2], "wb");
	if (bin == NULL)
	{
		cout << "Error Opening binary file for writing" << endl;
		return 1;
	}

	// locate offset of Image (location 0x3c)
	fseek(exe,0x3c, SEEK_SET);
	BYTE ImageOffset;
	fread(&ImageOffset, sizeof(BYTE), 1, exe);

	cout << "Image Data Starts at: 0x" << hex << static_cast<int> (ImageOffset) << endl;

	// Check file is a PE file
	fseek(exe, ImageOffset, SEEK_SET);
	unsigned long Sig;
	fread(&Sig, sizeof(unsigned long), 1, exe);

	if (Sig != 0x4550)
	{
		cout << "Not a valie PE file" << endl;
		return 1;
	}

	cout << "Valid PE Signature found" << endl;

	// Start reading in the COFF header
	COFFHeader chead;
	fread(&chead, sizeof(COFFHeader), 1, exe);

	cout << "Number of Sections: 0x" << chead.NumberOfSections << endl;
	cout << "Size of Optional Header: 0x" << chead.SizeOfOptionalHeader << endl;

	// Get Optional Header
	if (chead.SizeOfOptionalHeader == 0)
	{
		cout << "No Optional Header" << endl;
	}
	else
	{
		// Get Magic number 
		unsigned short OptMagic;
		fread(&OptMagic, sizeof(unsigned short), 1, exe);
		if (OptMagic == 0x10b)
		{
			cout << "PE32 Format Optional Header" << endl;
		}
		else if (OptMagic == 0x20b)
		{
			cout << "PE32+ Format Optional Header" << endl;
		}
		else
		{
			cout << "Unknown Format Optional Header" << endl;
		}
		cout << "Discarding rest of optional header" << endl;

		fseek(exe, chead.SizeOfOptionalHeader - 2, SEEK_CUR);
	}

	// Get Section Headers
	SectionHeader * Sections;
	Sections = new SectionHeader[chead.NumberOfSections];
	fread(Sections, sizeof(SectionHeader), chead.NumberOfSections, exe);

	// Get Each Section and write it to the binary file, pad with 0's as needed
	for (int ii = 0; ii < chead.NumberOfSections; ++ii)
	{
		cout << "Processing Section " << dec << ii << endl;
		cout << "\tData Size: 0x" << hex << Sections[ii].SizeOfRawData << endl;
		cout << "\tFile Data Pointer: 0x" << Sections[ii].PointerToRawData << endl;
		cout << "\tOffset in Bin File: 0x" << Sections[ii].VirtualAddress << endl;
		
		// locate start of data section in exe
		fseek(exe, Sections[ii].PointerToRawData, SEEK_SET);

		// locate write poitn in binary file
		fseek(bin, Sections[ii].VirtualAddress, SEEK_SET);

		// loop through data copying from exe to bin file
		BYTE Temp;
		for (unsigned int jj = 0; jj < Sections[ii].SizeOfRawData; jj++)
		{
			fread(&Temp, sizeof(BYTE), 1, exe);
			fwrite(&Temp, sizeof(BYTE), 1, bin);
		}
	}

	delete Sections;
	cout << "Complete" << endl;

	// close files
	fclose (bin);
	fclose (exe);

	return 0;
}
