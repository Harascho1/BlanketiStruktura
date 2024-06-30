#pragma once

#include "BSTNodeInt.h"
#include "StackAsArrayInt.h"

class BSTreeInt
{

public:
	BSTreeInt() { root = nullptr; numOfElements = 0; }
	~BSTreeInt() { deleteTree(root); }

	bool isEmpty() const { return root == nullptr; }

	bool isInTree(int el) const { return search(el) != nullptr; }
	BSTNodeInt* search(int el) const;
	int max(int a, int b);
	void insert(int el);
	void deleteByCopying(int el);
	void deleteByMerging(int el);

	void preorder() const { preorder(root); }
	void inorder() const { inorder(root); }
	void postorder() const { postorder(root); }

	void iterativePreorder() const;
	void breadthFirstSearch() const;



	


	//zadaci
	int depth() { return depth(root); }
	void balance() {
		const int n = numOfElements;
		int* stack = new int [n];
		int i = 0;
		while (root) {
			stack[i++] = root->getKey();
			deleteByCopying(root->getKey());
		}
		for (int i = 0; i < n-2; i++) {
			for (int j = i+1; j < n-1; j++) {
				if (stack[j] < stack[i]) {
					int temp = stack[i];
					stack[i] = stack[j];
					stack[j] = temp;
				}
			}
		}
		balance(stack, 0, n-1);
		delete[] stack;
	}

	//KOL1 2024
	int inorderDistance(int a, int b);
	//KOL2 2024
	void populate(int* arData, const int n);
	int sumInterval(const int min, const int max);
	//JUN 2024
	void deleteLeaves();
	int maxLevel();
	//JAN 2024
	int countCloseParent(const int n) const;
	//JUN 2024
	int subTreeSize() const;
	int countSmaller(const int d);
protected:
	BSTNodeInt* root;
	long numOfElements;

	//Brise celo drvo
	void deleteTree(BSTNodeInt* ptr);

	//traverse fje:
	//Obilazak po dubini
	void inorder(const BSTNodeInt* ptr) const;
	void preorder(const BSTNodeInt* ptr) const;
	void postorder(const BSTNodeInt* ptr) const;


	//zadaci za vezbu
	int depth(const BSTNodeInt* ptr);
	void balance(int* stack, int first, int last);


	

	int subTreeSize(const BSTNodeInt* ptr) const;
	int countSmaller(BSTNodeInt* ptr, const int d);


	//KOL1 2024
	int inorderDistance(BSTNodeInt* ptr, int a, int b);
	//KOL2 2024
	void add(int data);
	int sumInterval(BSTNodeInt* ptr, const int min, const int max);
	//JUN 2024
	void deleteLeaves(BSTNodeInt* ptr, BSTNodeInt* prev);
	int maxLevel(BSTNodeInt* ptr);
	//JAN 2024
	int countCloseParent(const BSTNodeInt* ptr, const int n) const;
};

