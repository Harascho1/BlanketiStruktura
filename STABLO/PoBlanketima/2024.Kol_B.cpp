//BSTreeInt.h

{
public:
	void populate(int* arData, const int n);
	int sumInterval(const int min, const int max);
private:
	void add(int data);
	int sumInterval(BSTNodeInt* ptr, const int min, const int max);
}


//BSTreeInt.cpp

void BSTreeInt::populate(int* arData, const int n) {
	for (int i = 0; i < n; i++) {
		this->add(arData[i]);
	}
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

int BSTreeInt::sumInterval(const int min, const int max) {
	return sumInterval(root,min,max);
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

