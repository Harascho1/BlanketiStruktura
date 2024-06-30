#include "GraphInt.h"

#include <iostream>
#include <memory>
using namespace std;

#include "QueueAsArrayInt.h"

#include "StackAsArrayInt.h"

GraphAsListsInt::GraphAsListsInt() : start(nullptr), nodeNum()
{
}

GraphAsListsInt::~GraphAsListsInt()
{
	cout << "Not implemented!" << endl;
}

LinkedNodeInt* GraphAsListsInt::findNode(const int& data) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data)
		ptr = ptr->next;
	return ptr;
}

LinkedEdgeInt* GraphAsListsInt::findEdge(const int& dataSrc, const int& dataDest) const
{
	LinkedNodeInt* ptr = findNode(dataSrc);
	if (ptr == nullptr)
		return nullptr;
	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest)
		pEdge = pEdge->link;
	return pEdge;
}

void GraphAsListsInt::insertNode(const int& data)
{
	start = new LinkedNodeInt(data, nullptr, start);
	nodeNum++;
}

bool GraphAsListsInt::insertEdge(const int& dataSrc, const int& dataDest, const double& weight /*= 0*/)
{
	LinkedNodeInt* pSrc = nullptr;
	LinkedNodeInt* pDest = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && (pSrc == nullptr || pDest == nullptr)) {
		if (ptr->node == dataSrc) {
			pSrc = ptr;
		}
		else if (ptr->node == dataDest) {
			pDest = ptr;
		}
		ptr = ptr->next;
	}
	if (pSrc == nullptr || pDest == nullptr)
		return false;
	pSrc->adj = new LinkedEdgeInt(pDest, pSrc->adj);
	return true;
}

bool GraphAsListsInt::deleteEdge(const int& dataSrc, const int& dataDest) const
{
	LinkedNodeInt* pSrc = findNode(dataSrc);
	if (pSrc == nullptr)
		return false;

	LinkedEdgeInt* pEdgePrev = nullptr;
	LinkedEdgeInt* pEdge = pSrc->adj;
	while (pEdge != nullptr && pEdge->dest->node != dataDest) {
		pEdgePrev = pEdge;
		pEdge = pEdge->link;
	}
	if (pEdge == nullptr)
		return false;

	if (pEdgePrev == nullptr)
		pSrc->adj = pEdge->link;
	else
		pEdgePrev->link = pEdge->link;

	delete pEdge;

	return true;
}

int GraphAsListsInt::printMaxConnectedComponentNodes() {
	return printMaxConnectedComponentNodes(start);
}

int GraphAsListsInt::whichOneIsCloser(const int a, const int b, const int c) {
	LinkedNodeInt* ptrA = nullptr, * ptrB = nullptr, * ptrC = nullptr, * ptr = start;

	while (ptr != nullptr && (ptrA == nullptr || ptrB == nullptr || ptrC == nullptr)) {
		if (ptr->node == a) {
			ptrA = ptr;
		}
		if (ptr->node == b) {
			ptrB = ptr;
		}
		if (ptr->node == c) {
			ptrC = ptr;
		}
		ptr = ptr->next;
	}
	ensureEdgeExist(b, c);
	return whichOneIsCloser(ptrA, ptrB,ptrC);

}

void GraphAsListsInt::ensureEdgeExist(int b, int c) {
	LinkedNodeInt* ptrB = findNode(b);
	LinkedNodeInt* ptrC = findNode(c);
	LinkedEdgeInt* edgeB = ptrB->adj;
	LinkedEdgeInt* edgeC = ptrC->adj;
	while (edgeB != nullptr) {
		if (edgeB->dest == ptrC)	 return;
		edgeB = edgeB->link;
	}
	while (edgeC != nullptr) {
		if (edgeC->dest == ptrB) return;
		edgeC = edgeC->link;
	}
	ptrB->adj = new LinkedEdgeInt(ptrC, ptrB->adj);
}

bool GraphAsListsInt::arePathsPossible(const int start, const int goal1, const int goal2, const int mid) {
	LinkedNodeInt* ptrStart = findNode(start), * ptrGoal1 = findNode(goal1), * ptrGoal2 = findNode(goal2), * ptrMid = findNode(mid);
	if (ptrStart == nullptr || ptrGoal1 == nullptr || ptrGoal2 == nullptr || ptrMid == nullptr)
		return false;
	arePathsPossible(ptrStart, ptrGoal1, ptrGoal2, ptrMid);
}

bool GraphAsListsInt::isCyclic() const {
	setStatusForAllNodes(0);
	StackAsArrayLinkedNodeInt stek(this->nodeNum);
	
	stek.push(start);
	while (!stek.isEmpty()) {
		LinkedNodeInt* ptr = stek.pop();
		ptr->status = 1;
		LinkedEdgeInt* edge = ptr->adj;
		while (edge != nullptr) {
			if (edge->dest->status < 2) {
				if (edge->dest->status == 1) {
					return true;
				}
				stek.push(edge->dest);
			}
			edge = edge->link;
		}
	}
	return false;
}

bool GraphAsListsInt::arePathsPossible(LinkedNodeInt* start, LinkedNodeInt* goal1, LinkedNodeInt* goal2, LinkedNodeInt* mid) {
	setStatusForAllNodes(0);
	if (!isOnePathPossible(start, mid)) return false;
	if (!isOnePathPossible(mid, goal1)) return false;
	postOrder(goal1);
	cout << '\n';
	if (!isOnePathPossible(mid, goal2)) return false;
	postOrder(goal2);

	return false;
}

bool GraphAsListsInt::isOnePathPossible(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB) {
	LinkedEdgeInt* edgeA;
	QueueAsArrayLinkedNodeInt red(this->nodeNum);
	LinkedNodeInt* prev = nullptr;
	red.enqueue(ptrA);
	bool flag = false;
	while (!red.isEmpty()) {
		if (flag) break;
		ptrA = red.dequeue();
		edgeA = ptrA->adj;
		while (edgeA != nullptr) {
			if (edgeA->dest->status == 0 || edgeA->dest->status == 1) {
				prev = ptrA;
				edgeA->dest->prev = prev;
				if (edgeA->dest == ptrB) {
					setStatusForAllNodes(0);
					if (edgeA->dest == nullptr) return false;
					LinkedNodeInt* tmp = edgeA->dest;
					while (tmp != nullptr) {
						tmp->status++;
						tmp = tmp->prev;
					}
					return true;
				}
				edgeA->dest->status = 3;
				red.enqueue(edgeA->dest);
			}
			edgeA = edgeA->link;
		}
	}
	return false;
}

void GraphAsListsInt::postOrder(LinkedNodeInt* ptr) {
	if (ptr != nullptr) {
		postOrder(ptr->prev);
		ptr->visit();
	}
}

void GraphAsListsInt::deleteEdgeToNode(const LinkedNodeInt* pDest)
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		LinkedEdgeInt* pEdgePrev = nullptr;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr && pEdge->dest != pDest) {
			pEdgePrev = pEdge;
			pEdge = pEdge->link;
		}
		if (pEdge != nullptr)
		{
			if (pEdgePrev == nullptr)
				ptr->adj = pEdge->link;
			else
				pEdgePrev->link = pEdge->link;
		}
		ptr = ptr->next;
	}
}

bool GraphAsListsInt::deleteNode(const int& data)
{
	LinkedNodeInt* prev = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr && ptr->node != data) {
		prev = ptr;
		ptr = ptr->next;
	}
	if (ptr == nullptr)
		return false;

	LinkedEdgeInt* pEdge = ptr->adj;
	while (pEdge != nullptr) {
		LinkedEdgeInt* pEdgeTmp = pEdge->link;
		delete pEdge;
		pEdge = pEdgeTmp;
	}
	ptr->adj = nullptr;

	deleteEdgeToNode(ptr);

	if (prev == nullptr)
		start = start->next;
	else
		prev->next = ptr->next;

	delete ptr;
	nodeNum--;

	return true;
}

void GraphAsListsInt::print() const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr)
	{
		cout << ptr->node << " -> ";
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			cout << pEdge->dest->node << " | ";
			pEdge = pEdge->link;
		}
		cout << endl;
		ptr = ptr->next;
	}
}

void GraphAsListsInt::setStatusForAllNodes(int status) const
{
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = status;
		ptr = ptr->next;
	}
}

int GraphAsListsInt::printMaxConnectedComponentNodes(LinkedNodeInt* ptr) {

	LinkedNodeInt* tmp = ptr;
	while (tmp != nullptr) {
		LinkedEdgeInt* edgeT = tmp->adj;
		while (edgeT != nullptr) {
			if(!findEdge(edgeT->dest->node,tmp->node))
				edgeT->dest->adj = new LinkedEdgeInt(tmp, edgeT->dest->adj);
			edgeT = edgeT->link;
		}
		tmp = tmp->next;
	}
	int max = 0, i = 0;
	LinkedNodeInt* maxNode = start;
	tmp = start;
	while (tmp != nullptr) {
		LinkedEdgeInt* edgeT = tmp->adj;
		while (edgeT != nullptr) {
			i++;
			edgeT = edgeT->link;
		}
		if (i > max) {
			max = i;
			maxNode = tmp;
		}
		i = 0;
		tmp = tmp->next;
	}
	if (maxNode == nullptr) return -1;
	LinkedEdgeInt* edge = maxNode->adj;
	cout << "Cvor sa najvise grana je: " << maxNode->node << "\ni cvorovi na koje je on povezan su:\n";
	cout << maxNode->node << " ->";
	while (edge) {
		cout << ' ' << edge->dest->node << " |";
		edge = edge->link;
	}
	return max;
}

int GraphAsListsInt::whichOneIsCloser(LinkedNodeInt* ptrA, LinkedNodeInt* ptrB, LinkedNodeInt* ptrC) {
	setStatusForAllNodes(0);
	QueueAsArrayLinkedNodeInt red(this->nodeNum);
	LinkedNodeInt* tmp = ptrB;
	red.enqueue(tmp);
	int fromBtoA = 0, fromCtoA = 0;
	bool flag = false;
	while (!red.isEmpty()) {
		tmp = red.dequeue();
		LinkedEdgeInt* edge = tmp->adj;
		while (edge != nullptr && !flag) {
			if (edge->dest->status == 0) {
				edge->dest->status = tmp->status+1;
				if (edge->dest == ptrA) {
					fromBtoA = edge->dest->status;
					flag = true;
					break;
				}
				red.enqueue(edge->dest);
			}
			edge = edge->link;
		}
	}
	setStatusForAllNodes(0);
	flag = false;
	tmp = ptrB;
	red.enqueue(tmp);
	while (!red.isEmpty()) {
		tmp = red.dequeue();
		LinkedEdgeInt* edge = tmp->adj;
		while (edge != nullptr && !flag) {
			if (edge->dest->status == 0) {
				edge->dest->status = tmp->status +1;
				if (edge->dest == ptrA) {
					fromCtoA = edge->dest->status;
					flag = true;
					break;
				}
				red.enqueue(edge->dest);
			}
			edge = edge->link;
		}
	}
	return fromBtoA > fromCtoA ? ptrC->node : ptrB->node;
}


long GraphAsListsInt::breadthFirstTraversal(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	queue.enqueue(ptr);
	ptr->status = 2;
	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				queue.enqueue(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalIterative(const int& data) const
{
	long retVal = 0;

	LinkedNodeInt* ptr = findNode(data);
	if (ptr == nullptr)
		return 0;

	setStatusForAllNodes(1);

	StackAsArrayLinkedNodeInt stack(nodeNum);
	stack.push(ptr);
	ptr->status = 2;
	while (!stack.isEmpty()) {
		ptr = stack.pop();
		ptr->status = 3;
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			if (pEdge->dest->status == 1) {
				stack.push(pEdge->dest);
				pEdge->dest->status = 2;
			}
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(LinkedNodeInt* ptr) const
{
	int retVal = 0;
	if (ptr->status != 1) {
		ptr->visit();
		ptr->status = 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			retVal += depthFirstTraversalRecursive(pEdge->dest);
			pEdge = pEdge->link;
		}
		retVal++;
	}
	return retVal;
}

long GraphAsListsInt::depthFirstTraversalRecursive(const int& data) const
{
	LinkedNodeInt* pNode = nullptr;
	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		ptr->status = 0;
		if (ptr->node == data) {
			pNode = ptr;
		}
		ptr = ptr->next;
	}

	if (pNode == nullptr)
		return 0;

	return depthFirstTraversalRecursive(pNode);
}

long GraphAsListsInt::topologicalOrderTravrsal() const
{
	int retVal = 0;

	setStatusForAllNodes(0);

	LinkedNodeInt* ptr = start;
	while (ptr != nullptr) {
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status += 1;
			pEdge = pEdge->link;
		}
		ptr = ptr->next;
	}

	QueueAsArrayLinkedNodeInt queue(nodeNum);
	ptr = start;
	while (ptr != nullptr) {
		if (ptr->status == 0)
			queue.enqueue(ptr);
		ptr = ptr->next;
	}

	while (!queue.isEmpty()) {
		ptr = queue.dequeue();
		ptr->visit();
		retVal += 1;
		LinkedEdgeInt* pEdge = ptr->adj;
		while (pEdge != nullptr) {
			pEdge->dest->status--;
			if (pEdge->dest->status == 0)
				queue.enqueue(pEdge->dest);
			pEdge = pEdge->link;
		}
	}
	cout << endl;
	return retVal;
}
