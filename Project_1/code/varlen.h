// fvarlen.h
#ifndef VARLEN_H
#define VARLEN_H

#include <stdlib.h>
#include <iostream>
#include "iobuffer.h"

class VariableLengthBuffer: public IOBuffer
// Abstract class designed to support variablelength records
// Fields may be of a variety of types
//   
{  public:
	VariableLengthBuffer (int MaxBytes = 1000);
	VariableLengthBuffer (const VariableLengthBuffer & buffer) // copy constructor
		: IOBuffer(buffer){}

	void Clear (); // clear fields from buffer
	int Read (istream &);
	int Write (ostream &) const;
	//KHJ
	int Delete(ostream&, int,int);
	unsigned short Get_Buffer_Length(istream& , int);
	int Get_Next_Addr(istream&, int);
	int Update(ostream&, int recaddr, unsigned short length);
	int update_Deleted(ostream&, int recaddr, int next);
	unsigned short Get_Packed_Length();
	//KHJ_ENd
	int ReadHeader (istream &, int*); // write a buffer to the stream
	int WriteHeader (ostream &, int) const; // write a buffer to the stream
	int PackFixLen (void *, int);
	int PackDelimeted (void *, int);
	int PackLength (void *, int);
	void Print (ostream &) const;
	int SizeOfBuffer () const; // return current size of buffer
 	int Init ();
 protected:
};

#endif
