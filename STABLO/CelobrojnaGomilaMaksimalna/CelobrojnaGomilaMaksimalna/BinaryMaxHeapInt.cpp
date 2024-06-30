#include "BinaryMaxHeapInt.h"

#include <exception>
#include <iostream>
using namespace std;

BinaryMaxHeapInt::BinaryMaxHeapInt(long len)
{
	length = len;
	numOfElements = 0;
	array = new int[length + 1];
}

int BinaryMaxHeapInt::getFirst() const
{
	if (numOfElements == 0)
		throw new exception("The heap is empty!");
	return array[1];
}

void BinaryMaxHeapInt::insert(int el)
{
	if (numOfElements == length)
		throw new exception("The heap is full!");
	numOfElements++;
	int pos = numOfElements;
	while (pos > 1 && array[pos / 2] < el)
	{
		array[pos] = array[pos / 2];
		pos /= 2;
	}
	array[pos] = el;
}

int BinaryMaxHeapInt::deleteRoot()
{
	if (numOfElements == 0)
		throw new exception("The heap is empty!");
	int result = array[1];
	int last = array[numOfElements];
	numOfElements--;
	long pos = 1;
	while (2 * pos < numOfElements + 1)
	{
		long child = 2 * pos;
		if (child + 1 < numOfElements + 1 && array[child + 1] > array[child])
			child += 1;
		if (last >= array[child])
			break;
		array[pos] = array[child];
		pos = child;
	}
	array[pos] = last;
	return result;
}

void BinaryMaxHeapInt::print() {
	using namespace std;
	cout << "HEAP\n";
	for (int i = 1; i < numOfElements + 1; i++) {
		cout << array[i] << " ";
	}
	cout << "\nKraj HEAPa\n";
}
