#include "BSTreeInt.h"

int main()
{
	BSTreeInt* drvo = new BSTreeInt();
	drvo->insert(7);
	drvo->insert(4);
	drvo->insert(3);
	drvo->insert(10);
	drvo->insert(6);
	drvo->insert(5);
	drvo->insert(11);
	//drvo->deleteByCopying(7);
	//drvo->deleteByMerging(7);
	//std::cout << drvo->depth() << '\n';
	/*drvo->preorder();
	drvo->balance();
	std::cout << std::endl;*/

	drvo->inorder();
	cout << '\n';
	int d = drvo->inorderDistance(6,12); //Kako da napravim da mi veaca -1
	cout << "Kolika je distanca: " << d << '\n';
	drvo->preorder();
	cout << '\n';
	//drvo->deleteLeaves();
	drvo->inorder();
	cout << '\n';
	int maxLVL = drvo->maxLevel();
	cout << "Koji je nivo sa najvecim brojem covorova: " << maxLVL << '\n';
	drvo->inorder();
	cout << '\n';
	BSTreeInt tree;
	int arr[14] = { 10,5, 8, 14,12,16,3, 11,2,7,15,7,8,20 };
	tree.populate(arr, 14);
	cout << "Drvo definisano preko niza je:\n";
	tree.inorder();
	cout << '\n' << tree.sumInterval(4, 15);
	delete drvo;
	return 0;
}
