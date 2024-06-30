#pragma once

class BinaryMaxHeapInt
{
	//stack
private:
	//niz
	int* array;
	//duzinaNiza
	long length;
	//brojElemenata
	long numOfElements;

public:
	BinaryMaxHeapInt(long len);
	~BinaryMaxHeapInt() { delete[] array; };

	bool isEmpty() const { return numOfElements == 0; };
	int getFirst() const;

	void insert(int el);
	int deleteRoot();
	//Ovo sam ja dodao
	void print();
};

