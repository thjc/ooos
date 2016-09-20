#pragma once

#include "types.h"
#include "process.h"



class HeapAllocation
{
public:
	void Alloc(size_t Size, HeapAllocation* After);
	void Dealloc(void);
	HeapAllocation(void);
	~HeapAllocation(void);

private:
	HeapAllocation * Next;
	HeapAllocation * Prev;
	size_t AllocSize;
	size_t SpaceSize;
	
	friend Process;

};
