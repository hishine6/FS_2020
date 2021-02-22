// fixlen.cc#include "fixlen.h"#include "length.h"#include <string.h>//class FixedLengthBuffer// public membersFixedLengthBuffer :: FixedLengthBuffer (int recordSize) // construct with a maximum of maxFields: IOBuffer (recordSize){	Init (recordSize);}void FixedLengthBuffer :: Clear ()// clear fields from buffer{	IOBuffer::Clear ();	Buffer[0]=0;	Packing = TRUE;}int FixedLengthBuffer::Delete(ostream& stream, int recref,int next_addr) {	stream.seekp(recref, ios::beg);	if ((int)stream.tellp() != recref) return -1;	char temp = '*';	stream.write(&temp, sizeof(temp));	recref += 1;	stream.seekp(recref, ios::beg);	stream.write((char*)&next_addr, sizeof(next_addr));	if (!stream) return -1;}int FixedLengthBuffer::Get_Next_Addr(istream& stream, int recref) {	recref += 1;	stream.seekg(recref, ios::beg);	int temp;	stream.read((char*)&temp, sizeof(temp));	if (!stream.good()) { stream.clear(); return -1; }	return temp;}int FixedLengthBuffer :: Read (istream & stream)// write the number of bytes in the buffer field definitions{	int recaddr = stream . tellg (); stream.clear();	Clear ();	Packing = FALSE;	//KHJ	char temp;	stream.read(&temp, sizeof(temp));	if (!stream.good()) { stream.clear(); return -1; }	//KHJ_END	stream . read (Buffer, BufferSize);	if (!stream.good()) { stream.clear(); return recaddr; }	if (temp == '*')		return -2;	return recaddr;}int FixedLengthBuffer :: Write (ostream & stream) const// read the number of bytes in the buffer field definitions// return the location of the record in the file{	int recaddr = stream . tellp ();	//KHJ	char temp = '\0';	stream.write(&temp, sizeof(temp));	//KHJ_END	stream . write (Buffer, BufferSize);	if (! stream . good ()) return -1;	return recaddr;}static const char * headerStr = "Fixed";static const int headerStrSize = 5;int FixedLengthBuffer :: ReadHeader (istream & stream, int* delete_addr)// read the header and check for consistency// see WriteHeader for header record structure{	char str[headerStrSize+1];	int recordSize;	int result;	// read the IOBuffer header	result = IOBuffer::ReadHeader (stream, delete_addr);	if (result < 0) return -1;	// read the string "Fixed"	stream . read (str, headerStrSize);	if (!stream.good()) return -1;	if (strncmp (str, headerStr, headerStrSize) != 0) return -1;	stream . read ((char*)&recordSize, sizeof(recordSize));	if (Initialized) // check header for consistency	{		if (recordSize != BufferSize) return -1;	}	// else initialize the buffer from the header	ChangeRecordSize (recordSize);	//KHJ	int temp;	stream.read((char*)&temp, sizeof(delete_addr));	*delete_addr = temp;	if (!stream) return -1;	//KHJ_END	return stream.tellg();}int FixedLengthBuffer :: WriteHeader (ostream & stream,int delete_addr) const// write a buffer header to the beginning of the stream// A header consists of the //	IOBUFFER header	//	FIXED			5 bytes//	record size		2 bytes{	int result;	if (!Initialized) return -1; // cannot write unitialized buffer	// write the parent (IOBuffer) header	result = IOBuffer::WriteHeader (stream, delete_addr);	if (!result) return -1;	// write the string "Fixed"	stream . write (headerStr, headerStrSize);	if (!stream . good ()) return -1;	// write the record size	stream . write ((char *)&BufferSize, sizeof(BufferSize));	if (!stream.good()) return -1;	//KHJ	stream.write((char*)&delete_addr, sizeof(delete_addr));	if (!stream) return -1;	//KHJ_END	return stream . tellp ();}void FixedLengthBuffer :: Print (ostream & stream) const{	IOBuffer::Print (stream);	stream <<  "Fixed ";}int FixedLengthBuffer :: Init (int recordSize) // construct with a maximum of maxFields{	Clear ();	BufferSize = recordSize;	return 1;}int FixedLengthBuffer :: ChangeRecordSize (int recordSize) // construct with a maximum of maxFields{	BufferSize = recordSize;	return 1;}