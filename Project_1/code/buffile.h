// buffile.h

#ifndef BUFFILE_H
#define BUFFILE_H

#include <stdlib.h>
#include <fstream>
#include "iobuffer.h"


#ifndef FALSE
#define FALSE (0)
#define TRUE (1)
#endif

class BufferFile 
// Class to represent buffered file operations
// 	Used in conjunction with the IOBuffer classes 
// Each buffered file is associated with a disk file of a specific
// 	record type.
// Each buffered file object has a buffer object which can be used
// 	for file I/O
// Sequential and random access read and write are supported
// 	each write returns the record address of the record
// 	this record address can be used to read that record
//	the values of the record address depend on the type of file and buffer
{
   public:
	BufferFile (IOBuffer &); // create with a buffer

	int Open (char * filename, int MODE); // open an existing file
	int Create (char * filename, int MODE); // create a new file
	int Close ();
	int Rewind (); // reset to the first data record
	// Input and Output operations
	int Read (int recaddr = -1); 
		// read a record into the buffer
		// return the record address
		// return <0 if read failed
		// if recaddr == -1, read the next record in the file
		// if recaddr != -1, read the record at that address
	int Write (int recaddr = -1); // write the current buffer contents
	int Append (); // write the current buffer at the end of file
	
	//KHJ
	int Delete(int recaddr);
	int show_Delete_first();	//���� ����Ʈ�� ù �ּҸ� ��ȯ�Ѵ�.
	unsigned short Get_Buffer_Length(int recaddr);	//�ּҿ� �ش��ϴ� record���� ��ȯ
	unsigned short Get_Packed_Length();	//���� pack�� ���ڵ尡 ����� buffer�� ����
	int Get_Next_Addr(int recaddr);	//������ ������ �о ���� �ּҸ� �����´�.
	int Update(int recaddr, unsigned short length);	// ������ record�� ���� ����.
	int update_Delete_first(int);	//���� ����Ʈ�� ù �ּ� update
	int update_Deleted(int recaddr, int next);	//������ record�� �����Ѵ� (���븮��Ʈ�� ���� �ּ� ����)
	//KHJ_END
		
		// Access to IOBuffer
	IOBuffer & GetBuffer ();

   protected:
	IOBuffer & Buffer;
	fstream File;
	int HeaderSize; // size of header

	//KHJ
	int Delete_first=-1;
	//KHJ_END

	int ReadHeader (); 
	int WriteHeader ();
};

#endif

