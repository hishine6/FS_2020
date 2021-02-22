#ifndef INFILE_H
#define INFILE_H

#include "recfile.h"
#include "tindbuff.h"
#include <sstream>
#include <string>
// template class to support direct read and write of records
// The template parameter RecType must support the following
//	int Pack (BufferType &); pack record into buffer
//	int Unpack (BufferType &); unpack record from buffer

template <class RecType>
class TextIndexedFile
{public:
	int Read (RecType & record); // read next record
	int Read (char * key, RecType & record); // read by key
	int Append (RecType & record);
	int Update (char * oldKey, RecType & record);
	int Create (char * name, int mode=ios::in|ios::out);
	int Open (char * name, int mode=ios::in|ios::out);
	int Close ();

	//KHJ
	int Delete(char* key);
	int Create_from_data(char* name, int keySize, int maxKeys = 100, int mode = (ios::in | ios::out));

	TextIndexedFile (IOBuffer & buffer, 
		int keySize, int maxKeys = 100); 
	~TextIndexedFile (); // close and delete
protected:
	TextIndex Index;
	BufferFile IndexFile;
	TextIndexBuffer IndexBuffer;
	RecordFile<RecType> DataFile;
	char * FileName; // base file name for file
	int SetFileName(char * fileName,
		char *& dataFileName, char *& indexFileName);
};

// template method bodies
template <class RecType>
int TextIndexedFile<RecType>::Read (RecType & record)
{	return DataFile . Read (record, -1); }

template <class RecType>
int TextIndexedFile<RecType>::Read (char * key, RecType & record)
{
	int ref = Index.Search(key);
	if (ref < 0) return -1;
	int result = DataFile . Read (record, ref);
	return result;
}

template <class RecType>
int TextIndexedFile<RecType>::Append (RecType & record)
{
	char * key = record.Key();
	int ref = Index.Search(key);
	if (ref != -1) // key already in file
		return -1;
	ref = DataFile . Append(record);
	int result = Index . Insert (record.Key (), ref);
	return ref;
}

template <class RecType>
int TextIndexedFile<RecType>::Update (char * oldKey, RecType & record){	
	unsigned short total_l = DataFile.Get_Packed_Length(record);
	int result = Delete(oldKey);
	
	DataFile.Rewind();

	int before_addr = -1;
	int addr = DataFile.show_Delete_first();
	int flag = 0;
	while (addr != -1) {
		unsigned short s = DataFile.Get_Buffer_Length(addr);
		int next = DataFile.Get_Next_Addr(addr);
		if (s >= total_l) { //현 주소 addr에 담을 수 있는 경우
			flag = 1;
			printf("hi");
			DataFile.Update(record, addr, s); //현 주소에 새 레코드 입력
			if (before_addr == -1) { // next를 header에 delete head로 넣어준다
				DataFile.update_Delete_first(next);
			}
			else { //before_addr가 가리키는 곳에 next를 넣어준다.
				DataFile.update_Deleted(before_addr, next);
			}
			break;
		}
		before_addr = addr;
		addr = next;
	}
	if (flag == 0) { //뒤에 append 해야되는 경우
		addr=DataFile.Append(record);
	}

	Index.Insert(oldKey, addr);
	return 1;
}


template <class RecType>
int TextIndexedFile<RecType>::SetFileName(char * fileName,
	char *& dataFileName, char *& indexFileName)
// generate names for the data file and the index file
{
	if (FileName != 0) // object is already attached to a file
		return 0;
	// set FileName member
	FileName = _strdup(fileName);
	// generate real file names
	ostringstream dataName, indexName;
	dataName << FileName <<".dat"<<ends;
	indexName<< FileName<<".ind"<<ends;
	dataFileName = _strdup(dataName . str().c_str ());
	indexFileName = _strdup(indexName . str().c_str ());
	return 1;
}

template <class RecType>
int TextIndexedFile<RecType>::Create (char * fileName, int mode)
// use fileName.dat and fileName.ind
{
	int result;
	char * dataFileName, * indexFileName;
	result = SetFileName (fileName, dataFileName, indexFileName);
//	cout <<"file names "<<dataFileName<<" "<<indexFileName<<endl;
	if (result == -1) return 0;
	result = DataFile.Create (dataFileName, mode);
	if (!result)
	{
		FileName = 0; // remove connection
		return 0;
	}
	result = IndexFile.Create (indexFileName, ios::out|ios::in);
	if (!result)
	{
		DataFile . Close(); // close the data file
		FileName = 0; // remove connection
		return 0;
	}
	return 1;
}
template <class RecType>
int TextIndexedFile<RecType>::Create_from_data(char* fileName, int keySize, int maxKeys, int mode) {
	int result;
	char* dataFileName, * indexFileName;
	result = SetFileName(fileName, dataFileName, indexFileName);
	if (result == -1) return 0;
	result = DataFile.Open(dataFileName, mode);	//data file은 연다
	if (!result)
	{
		FileName = 0; // remove connection
		return 0;
	}
	
	TextIndex temp_index(maxKeys);
	while (1) {
		RecType t;
		int recaddr = DataFile.Read(t);
		if (recaddr == -1)
			break;
		temp_index.Insert(t.Key(), recaddr);
	}
	DataFile.Close();

	TextIndexBuffer idxbuf(keySize, maxKeys);
	BufferFile tt(idxbuf);
	tt.Create(indexFileName, mode);
	tt.Rewind();
	idxbuf.Pack(temp_index);
	result = tt.Write();
	tt.Close();
	if (!result)
	{
		FileName = 0; // remove connection
		return 0;
	}
	Open(fileName, mode);
	return 1;
}

template <class RecType>
int TextIndexedFile<RecType>::Open (char * fileName, int mode)
// open data and index file and read index file
{
	int result;
	char * dataFileName, * indexFileName;
	result = SetFileName (fileName, dataFileName, indexFileName);
	if (!result) return 0;
	// open files
	result = DataFile.Open (dataFileName, mode);
	if (!result)
	{
		FileName = 0; // remove connection
		return 0;
	}
	result = IndexFile.Open (indexFileName, mode);
	if (!result)
	{
		DataFile . Close(); // close the data file
		FileName = 0; // remove connection
		return 0;
	}
	// read index into memory
	result = IndexFile . Read ();
	if (result != -1)
	{
		result = IndexBuffer . Unpack (Index);
		if (result != -1) return 1;
	}
	// read or unpack failed!
	DataFile.Close();
	IndexFile.Close();
	FileName = 0;
	return 0;
}

template <class RecType>
int TextIndexedFile<RecType>::Close ()
{	int result;
	if (!FileName) return 0; // already closed!
	DataFile . Close();
	IndexFile . Rewind();
	IndexBuffer.Pack (Index);
	result = IndexFile . Write ();
//	cout <<"result of index write: "<<result<<endl;
	IndexFile . Close ();
	FileName = 0;
	return 1;
}

template <class RecType>
TextIndexedFile<RecType>::TextIndexedFile (IOBuffer & buffer,
		int keySize, int maxKeys)
	:DataFile(buffer), Index (maxKeys), 
	IndexFile(IndexBuffer), IndexBuffer(keySize, maxKeys)
{
	FileName = 0;
}

template <class RecType>
TextIndexedFile<RecType>::~TextIndexedFile ()
{	Close(); }


template <class RecType>
int TextIndexedFile<RecType>::Delete(char* key) {
	int ref = Index.Search(key);
	if (ref < 0)return-1;
	int result = DataFile.Delete(ref);
	result = Index.Remove(key);
	return result;
}
#endif

