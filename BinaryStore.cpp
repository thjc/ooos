#include "BinaryStore.h"

BinaryStore::BinaryStore(size_tp Size)
{
	Start = End = Head = Tail = new BYTE[Size];
}

BYTE * BinaryStore::Read(long Length)
{
	BYTE * Temp = Head;
	Head += Length;
	return Temp;
}

void BinaryStore::Write(long Length, BYTE * Data)
{
	for (int i = 0 ; i < Length; ++i)
	{
		if (Head == Start)
			Head--;
		++Head;
		*Head = *Data;
		++Data;
	}
}



		