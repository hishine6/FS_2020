// fixlen.h
#ifndef FIXLEN_H
#define FIXLEN_H

#include <stdlib.h>
#include <iostream>
#include "iobuffer.h"

class FixedLengthBuffer: public IOBuffer
// Abstract class designed to support fixed length records
{
   public:
	FixedLengthBuffer (int recordSize = 1000);
	FixedLengthBuffer (const FixedLengthBuffer & buffer); // copy constructor

	void Clear (); // clear values from buffer
	int Read (istream &);
	int Write (ostream &) const;
	int ReadHeader (istream &); // read header from stream
	int WriteHeader (ostream &) const; // write a header to the stream
	void Print (ostream &) const;
	int SizeOfBuffer () const; // return size of buffer

	//KHJ
	int Delete(ostream&, int, int);
	unsigned short Get_Buffer_Length(istream&, int);
	int Get_Next_Addr(istream&, int);
	int Update(ostream&, int recaddr, unsigned short length);
	int update_Deleted(ostream&, int recaddr, int next);
	unsigned short Get_Packed_Length();
	//KHJ_ENd


 protected:
 	int Init (int recordSize);
	int ChangeRecordSize (int recordSize);
};

inline FixedLengthBuffer :: FixedLengthBuffer (const FixedLengthBuffer & buffer)
: IOBuffer (buffer)
{
	Init (buffer . BufferSize);
}

#endif
