#include <iostream>
using namespace std;

#include "LinkedNodeInt.h"

LinkedNodeInt::LinkedNodeInt()
	: node(), adj(nullptr), next(nullptr), status()
{

}

LinkedNodeInt::LinkedNodeInt(int nodeN)
	: node(nodeN), adj(nullptr), next(nullptr), status()
{

}

LinkedNodeInt::LinkedNodeInt(int nodeN, LinkedEdgeInt* adjN, LinkedNodeInt* nextN)
	: node(nodeN), adj(adjN), next(nextN), status()
{

}

LinkedNodeInt::LinkedNodeInt(int nodeN, LinkedEdgeInt* adjN, LinkedNodeInt* nextN, int statusN)
	: node(nodeN), adj(adjN), next(nextN), status(statusN)
{

}

void LinkedNodeInt::visit()
{
	cout << node << " ";
}
