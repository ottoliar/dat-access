struct Node {
	int value;
	Node *left;
	Node *right;
};

class BSTree {
private:
	Node *root;
	void destroy_tree(Node *leaf) {
		if (leaf != NULL) {
			destroy_tree(leaf->left);
			destroy_tree(leaf->right);
			delete leaf;
		}
	}
	void insert(int key, Node *leaf) {
		if (key < leaf->value) {
			if (leaf->left != NULL) {
				insert(key, leaf->left);
			} else {
				leaf->left = new Node;
				leaf->left->value = key;
				leaf->left->left = NULL;
				leaf->left->right = NULL;
			}
		} else if (key > leaf->value) {
			if (leaf->right != NULL) {
				insert(key, leaf->right)
			} else {
				leaf->right = new Node;
				leaf->right->value = key;
				leaf->right->left = NULL;
				leaf->right->right = NULL;
			}
		}
	}
	Node *search(int key, Node* leaf) {
		if (leaf != NULL) {
			if (key == leaf->value) {
				return leaf;
			} else if (key < leaf->value) {
				return search(key, leaf->left);
			} else {
				return search(key, leaf->right);
			}
		} else {
			return NULL;
		}
	}
public:
	BSTree() {
		root = NULL;
	}
	void insert(int key) {
		if (root != NULL) {
			insert(key, root);
		} else {
			Node *root = new Node;
			root->value = key;
			root->right = root->left = NULL;
		}
	}
	Node *search(int key) {
		return search(key, root);
	}
	void destroy_tree() {
		destroy_tree(root);
	}
	// Depth first searches
	// Visit Node, left, right
	void preorder(Node *root) {
		if (root == NULL) return;
		std::cout << root->value << std::endl;
		preorder(root->left);
		preorder(root->right);
	}

	// left, node, right
	void inorder(Node *root) {
		if (root == NULL) return;
		inorder(root->left);
		std::cout << root->value << std::endl;
		inorder(root->right);
	}

	// left, right node
	void postorder (Node * root) {
		if (root == NULL) return;
		postorder(root->left);
		postorder(root->right);
		std::cout << root->value << std::endl;
	}
}