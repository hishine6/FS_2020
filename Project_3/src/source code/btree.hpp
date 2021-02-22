//btree.tc
#include "btnode.h"
#include "indbuff.h"
#include "btree.h"
#include <iostream>

const int MaxHeight = 5;
template <class keyType>
BTree<keyType>::BTree(int order, int keySize, int unique)
: Buffer (1+2*order,sizeof(int)+order*keySize+order*sizeof(int)),
	BTreeFile (Buffer), Root (order)
{
	Height = 1;
	Order = order;
	PoolSize = MaxHeight*2;
	Nodes = new BTNode * [PoolSize];
	BTNode::InitBuffer(Buffer,order);
	Nodes[0] = &Root;
}

template <class keyType>
BTree<keyType>::~BTree()
{
	Close();
	delete Nodes;
}

template <class keyType>
int BTree<keyType>::Open (char * name, int mode)
{
	int result;
	result = BTreeFile.Open(name, mode);
	if (!result) return result;
	// load root
	BTreeFile.Read(Root);
	Height = 4; // find height from BTreeFile!
	return 1;
}

template <class keyType>
int BTree<keyType>::Create (char * name, int mode)
{
	int result;
	result = BTreeFile.Create(name, mode);
	if (!result) return result;
	// append root node
	result = BTreeFile.Write(Root);
	Root.RecAddr=result;
	return result != -1;	
}

template <class keyType>
int BTree<keyType>::Close ()
{
	int result;
	result = BTreeFile.Rewind();
	if (!result) return result;
	result = BTreeFile.Write(Root);
	if (result==-1) return 0;
	return BTreeFile.Close();
}


template <class keyType>
int BTree<keyType>::Insert (const keyType key, const int recAddr)
{
	int result; int level = Height-1; 
	int newLargest=0; keyType prevKey, largestKey; 
	BTNode * thisNode, * newNode=NULL, * parentNode;
	thisNode = FindLeaf (key);

	// test for special case of new largest key in tree
	if (key > thisNode->LargestKey())
		{newLargest = 1; prevKey=thisNode->LargestKey();}

	result = thisNode -> Insert (key, recAddr);

	// handle special case of new largest key in tree
	if (newLargest)
		for (int i = 0; i<Height-1; i++) 
		{
			Nodes[i]->UpdateKey(prevKey,key);
			if (i>0) Store (Nodes[i]);
		}

	while (result==-1) // if overflow and not root
	{
		//remember the largest key
		largestKey=thisNode->LargestKey();
		// split the node
		newNode = NewNode();
		thisNode->Split(newNode);
		Store(thisNode); Store(newNode);
		level--; // go up to parent level
		if (level < 0) break;
		// insert newNode into parent of thisNode
		parentNode = Nodes[level];
		result = parentNode->UpdateKey
			(largestKey,thisNode->LargestKey());
		result = parentNode->Insert
			(newNode->LargestKey(),newNode->RecAddr);
		thisNode=parentNode;
	}
	Store(thisNode);
	if (level >= 0) return 1;// insert complete
	// else we just split the root
	int newAddr = BTreeFile.Append(Root); // put previous root into file
	// insert 2 keys in new root node
	Root.Keys[0]=thisNode->LargestKey();
	Root.RecAddrs[0]=newAddr;
	Root.Keys[1]=newNode->LargestKey();
	Root.RecAddrs[1]=newNode->RecAddr;
	Root.NumKeys=2; 
	Height++;
	return 1;	
}

template <class keyType>
int BTree<keyType>::Remove(const keyType key, const int recAddr)
{
	/* 1. ������ key�� ��� node�� ã�´� */
	/* 2. ������ ���� under flow�� �߻��ϴ��� Ȯ���Ѵ� */
	/* 3. underflow Ȯ���� root�� node�� 1������ Ȯ���Ѵ� */
	/* 4. 1���� ��� root�� �����ϰ� level�� 1���ҽ�Ų�� */
	int result, level = Height - 1;
	BTNode* thisNode = NULL;
	BTNode* siblingNode = NULL, * newRoot = NULL;
	bool Large_flag = false;
	keyType largestKey, Large_key_merge;

	thisNode = FindLeaf(key);

	largestKey = thisNode->LargestKey();
	if (largestKey == key)
		Large_flag = true;
	result = thisNode->Remove(key, recAddr);
	if (result != -1) { //�ּ� ���� �̻�   
		if (Large_flag) {
			for (int i = 0; i < Height - 1; i++) {
				Nodes[i]->UpdateKey(largestKey, thisNode->LargestKey()); //���ο� �ִ밪 ����
				if (i > 0) Store(Nodes[i]);
			}
		}
		Store(thisNode);
	}
	else {	//node�� key�� �ּҰ������� ���� ������ ��.
		while (result == -1) // if overflow and not root
		{
			BTNode* parentNode;
			parentNode = Nodes[--level];
			if (level < 0)
				break;
			int k = 0;
			int flag = 0;
			for (int i = 0; i < parentNode->NumKeys; i++) {
				siblingNode = Fetch(Nodes[level]->RecAddrs[i]);
				if (siblingNode->RecAddr == thisNode->RecAddr) {
					k = i;
					break;
				}
			}//thisnode�� �θ��� k��° �ڽ��̴�.
			if (k - 1 >= 0) {
				siblingNode = Fetch(Nodes[level]->RecAddrs[k - 1]);
				Large_key_merge = siblingNode->LargestKey();
				if (siblingNode->Merge(thisNode)) {
					flag = 1;
				}
			}
			if (flag == 0 && k + 1 < parentNode->NumKeys) {
				siblingNode = Fetch(Nodes[level]->RecAddrs[k + 1]);
				Large_key_merge = siblingNode->LargestKey();
				if (thisNode->Merge(siblingNode)) {
					flag = 2;
				}
			}

			if (flag == 0) {	//sibling�� merge ��� ����, merge �� overflow�߻�
				if (k - 1 >= 0) { //�տ� sibling������ �ʶ� ������ ��
					siblingNode = Fetch(Nodes[level]->RecAddrs[k - 1]);
					Large_key_merge = siblingNode->LargestKey();
					for (int i = 0; i < thisNode->NumKeys; i++) {
						keyType temp = Fetch(thisNode->RecAddrs[i])->LargestKey();
						siblingNode->Insert(temp, Fetch(thisNode->RecAddrs[i])->RecAddr);
					}
					BTNode* newNode = NewNode();
					siblingNode->Split(newNode);
					Store(siblingNode); Store(newNode);
					parentNode->UpdateKey(Large_key_merge, siblingNode->LargestKey());
					parentNode->UpdateKey(largestKey, newNode->LargestKey());
				}
				else { // �տ� ������ �ڶ� ��
					siblingNode = Fetch(Nodes[level]->RecAddrs[k + 1]);
					Large_key_merge = siblingNode->LargestKey();
					for (int i = 0; i < siblingNode->NumKeys; i++) {
						keyType temp = Fetch(siblingNode->RecAddrs[i])->LargestKey();
						thisNode->Insert(temp, Fetch(siblingNode->RecAddrs[i])->RecAddr);
					}
					BTNode* newNode = NewNode();
					thisNode->Split(newNode);
					Store(thisNode); Store(newNode);
					parentNode->UpdateKey(largestKey, thisNode->LargestKey());
					parentNode->UpdateKey(Large_key_merge, newNode->LargestKey());
				}
				break;
			}
			else if (flag == 1) {
				result = parentNode->Remove(Large_key_merge, -1); //���� siblig�� ����, ���� sibling�� max key ����
				thisNode = siblingNode;
				Store(thisNode);
			}
			else if (flag == 2) {
				result = parentNode->Remove(Large_key_merge, -1); //������ sibling�� ����, thisnode�� max key����
				parentNode->UpdateKey(largestKey, Large_key_merge);
				Store(thisNode);
			}
			thisNode = parentNode;
			largestKey = thisNode->LargestKey();
		}
		Store(thisNode);
		if (level >= 0) return 1;// delete complete
		// else we just delete the root
		newRoot = Fetch(Root.RecAddrs[0]);
		Root = *newRoot;
		Height--;
	}
	return 1;
}
template <class keyType>
int BTree<keyType>::Update(const keyType key, const int recAddr ) {
	Remove(key);
	Insert(key, recAddr);
	return 1;
}

template <class keyType>
int BTree<keyType>::Search (const keyType key, const int recAddr)
{
	BTNode * leafNode;
	leafNode = FindLeaf (key); 
	return leafNode -> Search (key, recAddr);
}

template <class keyType>
void BTree<keyType>::Print (ostream & stream) 
{
	stream << "BTree of height "<<Height<<" is "<<endl;
	Root.Print(stream);
	if (Height>1)
		for (int i = 0; i<Root.numKeys(); i++)
		{
			Print(stream, Root.RecAddrs[i], 2);
		}
	stream <<"end of BTree"<<endl;
}

template <class keyType>
void BTree<keyType>::Print 
	(ostream & stream, int nodeAddr, int level) 
{
	BTNode * thisNode = Fetch(nodeAddr);
	stream<<"Node at level "<<level<<" address "<<nodeAddr<<' ';
	thisNode -> Print(stream);
	if (Height>level)
	{
		level++;
		for (int i = 0; i<thisNode->numKeys(); i++)
		{
			Print(stream, thisNode->RecAddrs[i], level);
		}
		stream <<"end of level "<<level<<endl;
	}
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::FindLeaf (const keyType key)
// load a branch into memory down to the leaf with key
{
	int recAddr, level;
	for (level = 1; level < Height; level++)
	{
		recAddr = Nodes[level-1]->Search(key,-1,0);//inexact search
		Nodes[level]=Fetch(recAddr);
	}
	return Nodes[level-1];
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::NewNode ()
{// create a fresh node, insert into tree and set RecAddr member
	BTNode * newNode = new BTNode(Order);
	int recAddr = BTreeFile . Append(*newNode);
	newNode -> RecAddr = recAddr;
	return newNode;
}

template <class keyType>
BTreeNode<keyType> * BTree<keyType>::Fetch(const int recaddr)
{// load this node from File into a new BTreeNode
	int result;
	BTNode * newNode = new BTNode(Order);
	result = BTreeFile.Read (*newNode, recaddr);
	if (result == -1) return NULL;
	newNode -> RecAddr = result;
	return newNode;
}

template <class keyType>
int BTree<keyType>::Store (BTreeNode<keyType> * thisNode)
{
	return BTreeFile.Write(*thisNode, thisNode->RecAddr);
}
