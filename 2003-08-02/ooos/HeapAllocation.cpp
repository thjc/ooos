#include "heapallocation.h"
#include "global.h"
#include "videodriver.h"

HeapAllocation::HeapAllocation(void)
{
}

HeapAllocation::~HeapAllocation(void)
{
}

void HeapAllocation::Alloc(size_t Size, HeapAllocation* After)
{
	Next = After->Next;
	Prev = After;
	AllocSize = Size;
	SpaceSize = Prev->SpaceSize - AllocSize - sizeof(HeapAllocation);
	
	if (Next != NULL)
		Next->Prev = this;
	
	Prev->Next = this;
	Prev->SpaceSize = 0;
}

void HeapAllocation::Dealloc()
{
	Prev->Next = Next;
	Prev->SpaceSize += AllocSize + SpaceSize + sizeof(HeapAllocation);

	if (Next != NULL)
		Next->Prev = Prev;
}