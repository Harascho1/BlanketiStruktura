#pragma once

//#include "LinkedEdgeInt.h"
#include "LinkedNodeInt.h"

class GraphAsListsInt
{
protected:
	LinkedNodeInt* start;
	long nodeNum;
public:
	GraphAsListsInt();
	~GraphAsListsInt();
	LinkedNodeInt* findNode(const int& data) const;
	LinkedEdgeInt* findEdge(const int& dataSrc, const int& dataDest) const;
	void insertNode(const int& data);
	bool insertEdge(const int& dataSrc, const int& dataDest, const double& weight = 0);
	bool deleteEdge(const int& dataSrc, const int& dataDest) const;
	bool deleteNode(const int& data);
	void print() const;
	long depthFirstTraversalRecursive(const int& data) const;
	long breadthFirstTraversal(const int& data) const;
	long depthFirstTraversalIterative(const int& data) const;
	long topologicalOrderTravrsal() const;

	//JUN 2024
	int printMaxConnectedComponentNodes();
	//KOLB 2024
	int whichOneIsCloser(const int a, const int b, const int c);
	void ensureEdgeExist(int b, int c);
	//JAN 2024
	bool arePathsPossible(const int start, const int goal1, const int goal2, const int mid);
	//JUNII 2024
	bool isCyclic() const;
private:
	void deleteEdgeToNode(const LinkedNodeInt* pDest);
	long depthFirstTraversalRecursive(LinkedNodeInt* ptr) const;
	void setStatusForAllNodes(int status) const;

	//JUN 2024
	int printMaxConnectedComponentNodes(LinkedNodeInt* ptr);
	//KOLB 2024
	int whichOneIsCloser(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB, LinkedNodeInt* ptrC);
	//JAN 2024
	bool arePathsPossible(LinkedNodeInt* start, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid);
	bool isOnePathPossible(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB);
	void postOrder(LinkedNodeInt* ptr);
	
	
};

