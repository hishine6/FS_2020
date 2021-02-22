// varlen.cc

#include "varlen.h"
#include <string.h>

//class VariableLengthBuffer

// public members

VariableLengthBuffer :: VariableLengthBuffer (int maxBytes)
 // construct with a maximum of maxFields
: IOBuffer (maxBytes)
{
	Init ();
}

void VariableLengthBuffer :: Clear ()
// clear fields from buffer
{
	IOBuffer::Clear();
}

int VariableLengthBuffer::Read(istream& stream)
// write the number of bytes in the buffer field definitions
// the record length is represented by an unsigned short value
{
	if (stream.eof()) return -1;
	int recaddr = (int)stream.tellg();
	Clear();
	unsigned short bufferSize;

	//KHJ
	char temp;
	stream.read(&temp, sizeof(temp));
	if (!stream.good()) { stream.clear(); return -1; }
	//KHJ_END

	stream.read((char*)&bufferSize, sizeof(bufferSize));
	if (!stream.good()) { stream.clear(); return -1; }
	BufferSize = bufferSize;
	if (BufferSize > MaxBytes) return -1; // buffer overflow
	stream.read(Buffer, BufferSize);
	if (!stream.good()) { stream.clear(); return -1; }

	if (temp == '*')
		return -2;

	return recaddr;
}


int VariableLengthBuffer :: Write (ostream & stream) const
// write the length and buffer into the stream
{
	int recaddr = (int)stream . tellp ();
	unsigned short bufferSize;
	bufferSize = BufferSize;
	//KHJ
	char temp = '\0';
	stream.write(&temp, sizeof(temp));
	//KHJ_END
	
	stream . write ((char *)&bufferSize, sizeof(bufferSize));
	if (!stream) return -1;
	stream . write (Buffer, BufferSize);
	if (! stream . good ()) return -1;
	return recaddr;
}
//KHJ
int VariableLengthBuffer::Delete(ostream& stream, int recref,int next_addr) {
	stream.seekp(recref, ios::beg);
	if ((int)stream.tellp() != recref) return -1;

	char temp = '*';
	stream.write(&temp, sizeof(temp));
	recref += 3;
	stream.seekp(recref, ios::beg);
	stream.write((char*)&next_addr, sizeof(next_addr));
	if (!stream) return -1;
}

unsigned short VariableLengthBuffer::Get_Buffer_Length(istream & stream, int recref) {
	recref += 1;
	stream.seekg(recref, ios::beg);
	unsigned short temp;
	stream.read((char*)&temp, sizeof(temp));
	if (!stream.good()) { stream.clear(); return -1; }
	return temp;
}

int VariableLengthBuffer::Get_Next_Addr(istream& stream, int recref) {
	recref += 3;
	stream.seekg(recref, ios::beg);
	int temp;
	stream.read((char*)&temp, sizeof(temp));
	if (!stream.good()) { stream.clear(); return -1; }
	return temp;
}

int VariableLengthBuffer::Update(ostream& stream, int recaddr, unsigned short length) {
	stream.seekp(recaddr, ios::beg);
	char temp = '\0';
	stream.write(&temp, sizeof(temp));
	recaddr += 3;
	stream.seekp(recaddr, ios::beg);
	unsigned short bufferSize;
	bufferSize = BufferSize;

	stream.write(Buffer, BufferSize);
	if (!stream.good()) return -1;
	temp = ' ';
	for(int i=0;i<length-BufferSize;i++)
		stream.write(&temp, sizeof(temp));
	return recaddr;
}

int VariableLengthBuffer::update_Deleted(ostream& stream, int recaddr, int next) {
	recaddr += 3;
	stream.seekp(recaddr, ios::beg);
	stream.write((char*)&next,sizeof(next));
	if (!stream.good()) return -1;

}
unsigned short VariableLengthBuffer::Get_Packed_Length() {
	return BufferSize;
}

//KHJ_END
const char * headerStr = "Variable";
//const int headerSize = strlen (headerStr);
const int headerSize = 8;

int VariableLengthBuffer :: ReadHeader (istream & stream, int *delete_addr)
// read the header and check for consistency
{
	char str[headerSize+1];
	int result;
	// read the IOBuffer header
	result = IOBuffer::ReadHeader (stream,delete_addr);
	if (!result) return FALSE;
	// read the header string
	stream . read (str, headerSize);
	if (!stream.good()) return FALSE;
	if (strncmp (str, headerStr, headerSize) != 0) return FALSE;
	// read and check the record description

	//KHJ
	int temp;
	stream.read((char*)&temp, 4);
	*delete_addr = temp;
	if (!stream.good()) return FALSE;
	//KHJ_END

	return (int)stream . tellg ();
}

int VariableLengthBuffer :: WriteHeader (ostream & stream,int delete_addr) const
// write a buffer header to the beginning of the stream
// A header consists of the 
//	IOBUFFER header	
//	header string
//	Variable sized record of length fields
//		that describes the file records
{
	int result;
	// write the parent (IOBuffer) header
	result = IOBuffer::WriteHeader (stream,delete_addr);
	if (!result) return FALSE;
	// write the header string
	stream . write (headerStr, headerSize);
	if (!stream . good ()) return FALSE;
	// write the record description


	//KHJ
	stream.write((char*)&delete_addr, sizeof(delete_addr));
	if (!stream) return -1;
	//KHJ_END

	return (int)stream . tellp();
}

void VariableLengthBuffer :: Print (ostream & stream) const
{
	IOBuffer::Print (stream);
}

int VariableLengthBuffer :: Init ()
 // construct with a maximum of maxFields
{
	Clear();
	return TRUE;
}

