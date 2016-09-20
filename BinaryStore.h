typedef long size_tp;
typedef unsigned char BYTE;

class BinaryStore
{
	BYTE 	*Start, *End, *Head, *Tail;
	size_t	Size;
	long	Mode;
	long	Lock;
public: 
	BinaryStore(size_tp Size);
	BYTE * Read(long Length);
	void Write(long Length, BYTE * Data);
};