#include "BSTreeInt.h"

#include <exception>
using namespace std;

#include "QueueAsArrayInt.h"
#include "StackAsArrayInt.h"

void BSTreeInt::deleteTree(BSTNodeInt* ptr)
{
	if (ptr != nullptr) {
		deleteTree(ptr->left);
		deleteTree(ptr->right);
		delete ptr;
	}
}

BSTNodeInt* BSTreeInt::search(int el) const
{
	BSTNodeInt* ptr = root;
	while (ptr != nullptr)
		if (ptr->isEQ(el))
			return ptr;
		else if (ptr->isGT(el))
			ptr = ptr->left;
		else
			ptr = ptr->right;
	return nullptr;
}

int BSTreeInt::max(int a, int b) {
	if (a >= b) return a;
	else return b;
}

void BSTreeInt::insert(int el)
{
	BSTNodeInt* ptr = root, * par = nullptr;
	while (ptr != nullptr) {  // trazenje mesta za umetanje novog cvora
		par = ptr;
		if (ptr->isLT(el))
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}
	if (root == nullptr)    // stablo je prazno
		root = new BSTNodeInt(el);
	else if (par->isLT(el))
		par->right = new BSTNodeInt(el);
	else
		par->left = new BSTNodeInt(el);
	numOfElements++;
}

void BSTreeInt::deleteByCopying(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) { 	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)             // cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)         // cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			BSTNodeInt* parent = node;
			while (tmp->right != nullptr) {		// nalazenje krajnjeg desnog cvora
				parent = tmp;             		// u levom podstablu
				tmp = tmp->right;
			}
			node->setKey(tmp->getKey());		// prepisivanje reference na kljuc 
			if (parent == node)           		// tmp je direktni levi potomak node-a
				parent->left = tmp->left;		// ostaje isti raspored u levom podstablu
			else
				parent->right = tmp->left; 		// levi potomak tmp-a 
			delete tmp;							// se pomera na mesto tmp-a
			numOfElements--;
			return;
		}
		if (ptr == root)						// u slucaju (1) i (2) samo je pomerena
			root = node;						// referenca node pa je potrebno
		else if (par->left == ptr)				// izmeniti i link prethodnog cvora
			par->left = node;					// u slucaju (3) ovo nema dejstva
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::deleteByMerging(int el)
{
	BSTNodeInt* node, * ptr = root, * par = nullptr;
	while (ptr != nullptr && !ptr->isEQ(el)) {	// nalazenje cvora sa zeljenim el.
		par = ptr;
		if (ptr->isLT(el)) ptr = ptr->right;
		else ptr = ptr->left;
	}
	node = ptr;
	if (ptr != nullptr && ptr->isEQ(el)) {
		if (node->right == nullptr)				// cvor nema desnog potomka (1)
			node = node->left;
		else if (node->left == nullptr)			// cvor nema levog potomka (2)
			node = node->right;
		else {									// cvor ima oba potomka (3)
			BSTNodeInt* tmp = node->left;
			while (tmp->right != nullptr)		// nalazenje krajnjeg desnog cvora
				tmp = tmp->right;				// u levom podstablu
			tmp->right = node->right;			// prebacivanje desnog linka node-a u tmp
			node = node->left;					// na tekucem mestu bice prvi levi potomak
		}
		if (ptr == root)
			root = node;
		else if (par->left == ptr)
			par->left = node;
		else
			par->right = node;
		delete ptr;
		numOfElements--;
	}
	else if (root != nullptr)
		throw new exception("Element is not in the tree!");
	else
		throw new exception("The tree is empty!");
}

void BSTreeInt::preorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		ptr->visit();
		preorder(ptr->left);
		preorder(ptr->right);
	}
}

void BSTreeInt::inorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		inorder(ptr->left);
		ptr->visit();
		inorder(ptr->right);
	}
}

void BSTreeInt::postorder(const BSTNodeInt* ptr) const
{
	if (ptr != nullptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		ptr->visit();
	}
}

int BSTreeInt::depth(const BSTNodeInt* ptr){
	if (ptr == nullptr)
		return 0;
	if (ptr->left == nullptr && ptr->right == nullptr)
		return 0;
	return 1 + max(depth(ptr->left), depth(ptr->right));
}

void BSTreeInt::balance(int* stack, int first, int last) {
	if(first <= last)
	{
		int middle = (first + last) / 2;
		insert(stack[middle]);
		balance(stack, first, middle - 1);
		balance(stack, middle + 1, last);
	}
	
}

int BSTreeInt::countCloseParent(const BSTNodeInt* ptr, const int n) const {
	if (!ptr) return 0;
	if (!ptr->left && !ptr->right) return 0;
	if (ptr->left && ptr->right) {
		if (abs(ptr->left->getKey() - ptr->getKey() <= n)
			&& abs(ptr->right->getKey() - ptr->getKey()) <= n) {
			return 1 + countCloseParent(ptr->left, n) + countCloseParent(ptr->right, n);
		}
	}
	return countCloseParent(ptr->left, n) + countCloseParent(ptr->right, n);
}

int BSTreeInt::subTreeSize(const BSTNodeInt* ptr) const{
	if (!ptr) return 0;
	return 1 + subTreeSize(ptr->left) + subTreeSize(ptr->right);
}

int BSTreeInt::countSmaller(BSTNodeInt* ptr, const int d) {
	if (!ptr) return 0;
	int count = 0;
	int leftBranch = subTreeSize(ptr->left);
	int rightBranch = subTreeSize(ptr->right);
	int n = 1 + leftBranch + rightBranch;
	if ((leftBranch > 0 && n - d < leftBranch) ||
		(rightBranch > 0 && n - d < rightBranch))
		count++;
	count += countSmaller(ptr->left, d);
	count += countSmaller(ptr->right, d);
	
	return count;
}

int BSTreeInt::inorderDistance(BSTNodeInt* ptr, const int a, const int b) {
	
	if (ptr != nullptr) {
		
		if (ptr->getKey() == a)
		{
			if (ptr->right) return inorderDistance(ptr->right, a, b);
		}
		else if (ptr->getKey() == b)
		{
			if (ptr->left) return inorderDistance(ptr->left, a, b);
		}
		else {
			if (ptr->left && ptr->right)
				return inorderDistance(ptr->left, a, b) + inorderDistance(ptr->right, a, b);
			if (ptr->left) {
				return inorderDistance(ptr->left, a, b);
			}
			if (ptr->right) {
				return inorderDistance(ptr->right, a, b);
			}
		}
	}
	return 1;
	//inorder
	//nesto
	//inorder
}

void BSTreeInt::add(int data) {
	if (root == nullptr) {
		root = new BSTNodeInt(data);
		return;
	}
	BSTNodeInt* ptr = root, *prev = nullptr;
	while (ptr != nullptr) {
		prev = ptr;
		if (ptr->isEQ(data))
			return;
		if (ptr->isLT(data)) {
			ptr = ptr->right;
		}
		else {
			ptr = ptr->left;
		}

	}
	if (prev->isLT(data)) {
		prev->right = new BSTNodeInt(data);
	}
	else {
		prev->left = new BSTNodeInt(data);
	}
}

int BSTreeInt::sumInterval(BSTNodeInt* ptr, const int min, const int max) {
	if (ptr == nullptr) {
		return 0;

	}
	if (ptr->right == nullptr && ptr->left == nullptr && ptr->getKey()>min && ptr->getKey()<max) return ptr->key;
	if (ptr->isLT(min)) {
		return sumInterval(ptr->right, min, max);
	}
	else if (ptr->isGT(max)) {
		return sumInterval(ptr->left, min, max);
	}
	return ptr->key + sumInterval(ptr->left, min,max) + sumInterval(ptr->right,min,max);

}

void BSTreeInt::deleteLeaves(BSTNodeInt* ptr, BSTNodeInt* prev) {
	if (ptr == nullptr) {
		return;
	}
	if (ptr->left == nullptr && ptr->right == nullptr) {
		if (prev->left == ptr) {
			delete ptr;
			prev->left = nullptr;
		}
		else {
			delete ptr;
			prev->right = nullptr;
		}
	}
	else {
		deleteLeaves(ptr->left,ptr);
		deleteLeaves(ptr->right,ptr);
	}
}

int BSTreeInt::maxLevel(BSTNodeInt* ptr) {
	QueueAsArrayBSTNodeInt red(this->numOfElements);
	red.enqueue(ptr);
	int lvl = 0, maxLvl = 0, maxNodes = 0;
	while (!red.isEmpty()) {

		int brojCvorova = red.numberOfElements();
		if (brojCvorova > maxNodes) {
			maxNodes = brojCvorova;
			maxLvl = lvl;
		}
		for (int i = 0; i < brojCvorova; i++) {
			BSTNodeInt* tmp = red.dequeue();
			if (tmp->left != nullptr)
				red.enqueue(tmp->left);
			if (tmp->right != nullptr)
				red.enqueue(tmp->right);
		}
		lvl++;
	}
	return maxLvl;


	/*if (ptr == nullptr) return 0;
	if (ptr->left == nullptr && ptr->right == nullptr) return 1;
	int maxLeft = maxLevel(ptr->left);
	int maxRight = maxLevel(ptr->right);
	return 1+(maxLeft > maxRight ? maxLeft : maxRight);*/
}



void BSTreeInt::iterativePreorder() const
{
	BSTNodeInt* ptr = root;
	StackAsArrayBSTNodeInt stack(numOfElements);
	if (ptr != nullptr) {
		stack.push(ptr);
		while (!stack.isEmpty()) {
			ptr = stack.pop();
			ptr->visit();
			if (ptr->right != nullptr)	// levi potomak se stavlja u magacin
				stack.push(ptr->right); // posle desnog, da bi se prvi obradio
			if (ptr->left != nullptr)
				stack.push(ptr->left);
		}
	}
}

void BSTreeInt::breadthFirstSearch() const
{
	BSTNodeInt* ptr = root;
	QueueAsArrayBSTNodeInt queue(numOfElements);
	if (ptr != nullptr) {
		queue.enqueue(ptr);
		while (!queue.isEmpty()) {
			ptr = queue.dequeue();
			ptr->visit();
			if (ptr->left != nullptr)
				queue.enqueue(ptr->left);
			if (ptr->right != nullptr)
				queue.enqueue(ptr->right);
		}
	}
}

int BSTreeInt::countCloseParent(int n) const {
	return countCloseParent(root,n);
}

int BSTreeInt::subTreeSize() const {
	return subTreeSize(root);
}

int BSTreeInt::countSmaller(const int d) {
	return countSmaller(root, d);
}

int BSTreeInt::inorderDistance(int a, int b) {
	int brojCvorova = inorderDistance(root, a, b);
	return brojCvorova == numOfElements ? -1 : brojCvorova;
}

void BSTreeInt::populate(int* arData, const int n) {
	for (int i = 0; i < n; i++) {
		this->add(arData[i]);
	}
}

int BSTreeInt::sumInterval(const int min, const int max) {
	return sumInterval(root,min,max);
}

void BSTreeInt::deleteLeaves() {
	deleteLeaves(root,nullptr);
}

int BSTreeInt::maxLevel() {
	return maxLevel(root);
}
