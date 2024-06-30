#include "BinaryMaxHeapInt.h"

#include <iostream>
using namespace std;

void main()
{
	BinaryMaxHeapInt BMH(10);
	cout << BMH.isEmpty() << endl;
	BMH.insert(4);
	BMH.insert(5);
	BMH.insert(9);
	BMH.insert(2);
	BMH.insert(8);
	BMH.print();
}
