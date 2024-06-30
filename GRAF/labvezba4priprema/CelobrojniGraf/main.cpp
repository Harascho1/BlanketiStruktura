#include <iostream>
using std::cout;

#include "GraphInt.h"

int main(int argc, char* argv[]) 
{

	GraphAsListsInt graf;
	graf.insertNode(40);
	graf.insertNode(30);
	graf.insertNode(20);
	graf.insertNode(90);
	graf.insertNode(100);
	graf.insertNode(10);
	graf.insertEdge(40, 20);
	graf.insertEdge(10, 20);
	graf.insertEdge(90, 30);//
	graf.insertEdge(100, 90);//
	graf.insertEdge(20, 100);//
	graf.insertEdge(30, 40);
	graf.insertEdge(30, 10);
	graf.insertEdge(30, 20);
	graf.insertEdge(90, 20);

	cout << (graf.isCyclic() ? "true" : "false");
	cout << '\n';

	/*graf.print();
	graf.printMaxConnectedComponentNodes();
	int c = graf.whichOneIsCloser(40, 90, 10);*/
	
	GraphAsListsInt Aerodrom;
	Aerodrom.insertNode(10);
	Aerodrom.insertNode(20);
	Aerodrom.insertNode(30);
	Aerodrom.insertNode(40);
	Aerodrom.insertNode(50);
	Aerodrom.insertNode(60);
	Aerodrom.insertNode(70);
	Aerodrom.insertNode(100);
	Aerodrom.insertEdge(10, 20);
	Aerodrom.insertEdge(10, 30);
	Aerodrom.insertEdge(20, 40);
	Aerodrom.insertEdge(20, 50);
	Aerodrom.insertEdge(30, 70);
	Aerodrom.insertEdge(50, 40);
	Aerodrom.insertEdge(50, 60);
	Aerodrom.insertEdge(60, 70);
	Aerodrom.insertEdge(40, 100);
	
	bool c = Aerodrom.arePathsPossible(10, 40, 100, 50);
	cout << '\n';
	cout << c;
}

