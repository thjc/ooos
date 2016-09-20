typedef unsigned char BYTE;

void main()
{
	BYTE Colour = 0x4;
	char HWS[12] = "Hello World";
	BYTE * VidMem = reinterpret_cast<BYTE *> (0xB8000);
	for (BYTE i = 0; HWS[i] != '\0'; ++i)
	{
		VidMem[(i<<1) + 1] = Colour;
		VidMem[(i<<1)] = HWS[i];
	}
}


