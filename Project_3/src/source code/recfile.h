#ifndef RECFILE_H
#define RECFILE_H

#include "buffile.h"
#include "iobuffer.h"
// template class to support direct read and write of records
// The template parameter RecType must support the following
//	int Pack (BufferType &); pack record into buffer
//	int Unpack (BufferType &); unpack record from buffer

template <class RecType>
class RecordFile: public BufferFile
{public:
	int Read (RecType & record, int recaddr=-1);
	int Write (const RecType & record, int recaddr = -1);
	int Append (const RecType & record, int recaddr = -1);

	int Delete(int recaddr = -1);
	int Search(const RecType& record);
	int show_Delete_first();	//���� ����Ʈ ó�� �ּ�
	unsigned short Get_Buffer_Length(int recaddr = -1);	//������ ���ڵ��� ����
	unsigned short Get_Packed_Length(const RecType& record); //pack���� ũ�� ��ȯ
	int Get_Next_Addr(int recaddr = -1);	//���� ����Ʈ ���� �ּ�
	int Update(const RecType& record, int recaddr, unsigned short length); //�ش� �ּҿ� ������Ʈ
	int update_Delete_first(int recaddr);	//���� ����Ʈ�� ù �ּ� ����
	int update_Deleted(int recaddr, int next); //���� ����Ʈ �̾��ֱ�
	int Search_For_Purchase(const RecType& record); //game id, member id�ε� search�� ��

	RecordFile (IOBuffer & buffer): BufferFile (buffer) {}
};

// template method bodies
template <class RecType>
int RecordFile<RecType>::Read (RecType & record, int recaddr)
{
	int readAddr, result;
	readAddr = BufferFile::Read (recaddr);
	if (readAddr==-1)return -1;
	else if (readAddr == -2) {
		return -1;
	}
	result = record . Unpack (Buffer);
	if (!result) return -1;
	return readAddr;
}

template <class RecType>
int RecordFile<RecType>::Write (const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Write (recaddr);
}

template <class RecType>
int RecordFile<RecType>::Append (const RecType & record, int recaddr)
{
	int result;
	result = record . Pack (Buffer);
	if (!result) return -1;
	return BufferFile::Append ();
}

//KHJ
template <class RecType>
int RecordFile<RecType>::Delete(int recaddr) {
	return BufferFile::Delete(recaddr);
}
template <class RecType>
int RecordFile<RecType>::show_Delete_first() {
	return BufferFile::show_Delete_first();
}

template <class RecType>
int RecordFile<RecType>::Search(const RecType& record) 
//return the finding addr, if there isn't return -1
{
	int readAddr = -1;
	int result;
	RecType temp = RecType();
	while (1) {
		readAddr = BufferFile::Read(-1); //������ �����̸� -2�� ���� ������ ���ų� ������ ����� -1�� ��ȯ�Ѵ�.
		if (readAddr == -1)
			break;
		if (readAddr == -2)
			continue;
		result = temp.Unpack(Buffer);
		if (!result) 
			return -1;
		if (temp == record)
			return readAddr;
	}
	return readAddr;
}
template <class RecType>
unsigned short RecordFile<RecType>::Get_Buffer_Length(int recaddr) {
	return BufferFile::Get_Buffer_Length(recaddr);
}


template <class RecType>
int RecordFile<RecType>::Get_Next_Addr(int recaddr) {
	return BufferFile::Get_Next_Addr(recaddr);
}


template <class RecType>
int RecordFile<RecType>::Update(const RecType& record, int recaddr, unsigned short length) {
	int result;
	result = record.Pack(Buffer);
	if (!result) return -1;
	return BufferFile::Update(recaddr,length);
}

template <class RecType>
int RecordFile<RecType>::update_Delete_first(int recaddr) {
	return BufferFile::update_Delete_first(recaddr);
}

template <class RecType>
int  RecordFile<RecType>::update_Deleted(int recaddr, int next) {
	return BufferFile::update_Deleted(recaddr,next);
}

template <class RecType>
unsigned short RecordFile<RecType>::Get_Packed_Length(const RecType& record) {
	int result;
	result = record.Pack(Buffer);
	if (!result)return -1;

	return BufferFile::Get_Packed_Length();
}

template <class RecType>
int RecordFile<RecType>::Search_For_Purchase(const RecType& record) {
	int readAddr = -1;
	int result;
	RecType temp = RecType();
	while (1) {
		readAddr = BufferFile::Read(-1); //������ �����̸� -2�� ���� ������ ���ų� ������ ����� -1�� ��ȯ�Ѵ�.
		if (readAddr == -1)
			break;
		if (readAddr == -2)
			continue;
		result = temp.Unpack(Buffer);
		if (!result)
			return -1;
		if (temp.compare(record))
			return readAddr;
	}
	return readAddr;
}

//KHJ_END
#endif

