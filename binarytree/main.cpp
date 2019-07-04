#include <iostream>

class BinaryTree {
public:
	BinaryTree() {
		root = nullptr;
	}
	~BinaryTree() {
		this->destroy(root);
	}
public:
	struct Node {
		int value;
		Node* left = nullptr;
		Node* right = nullptr;
	};
private:
	Node* root;
private:
	void insert(int value, Node* leaf) {
		if(value < leaf->value) {
			if(leaf->left)
				insert(value, leaf->left);
			else {
				leaf->left = new Node();
				leaf->left->value = value;
			}
		} else if(value >= leaf->value) {
			if(leaf->right)
				insert(value, leaf->right);
			else {
				leaf->right = new Node();
				leaf->right->value = value;
			}
		}
	}
	Node* search(int value, Node* leaf) {
		if(leaf) {
			if(value == leaf->value)
				return (leaf);
			if(value > leaf->value)
				search(value, leaf->right);
			else
				search(value, leaf->left);
		} else {
			return 0;
		}
	}
	void destroy(Node* leaf) {
		if(leaf) {
			if(leaf->left)
				destroy(leaf->left);
			if(leaf->right)
				destroy(leaf->right);
			delete leaf;
		}
	}
public:
	void insert(int value) {
		if(root) {
			insert(value, root);
		} else {
			root = new Node();
			root->value = value;
		}
	}
	Node* search(int value) {
		return search(value, root);
	}

	Node* getRoot() { return root; }
	void inorder_print(Node* leaf) {
		if(leaf) {
			inorder_print(leaf->left);
			std::cout << leaf->value << ",";
			inorder_print(leaf->right);
		}
	}
};


int main() {
	BinaryTree binTree;

	for(int i = 0; i < 100; i++) {
		if(i % 2 == 0)
			binTree.insert(i);
		else
			binTree.insert(-i);
	}

	binTree.inorder_print(binTree.getRoot());

	//std::cin.get();
	return 0;
}