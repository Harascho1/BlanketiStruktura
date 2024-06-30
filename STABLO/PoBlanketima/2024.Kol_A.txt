//BSTree.h
{
public:
	int inorderDistance(BSTNodeInt* ptr, int a, int b);
private:
	int inorderDistance(int a, int b);
}

//BSTree.cpp

int BSTreeInt::inorderDistance(int a, int b) {
	int brojCvorova = inorderDistance(root, a, b);
	return brojCvorova == numOfElements ? -1 : brojCvorova;
}

int BSTreeInt::inorderDistance(BSTNodeInt* ptr, const int a, const int b) {
	
	if (ptr != nullptr) {
		
		if (ptr->getKey() == a) {
			if (ptr->right) return inorderDistance(ptr->right, a, b);
		}
		else if (ptr->getKey() == b) {
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