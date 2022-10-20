#include <bits/stdc++.h>
using namespace std;

typedef struct AVLwithparent Node;

struct AVLwithparent {
	Node* left;
	Node* right;
	int key;
	Node* parent;
	int height;
};

void Updateheight(Node* root) {
	if (root != NULL) {
		int val = 1;

		if (root->left != NULL)
			val = root->left->height + 1;

		if (root->right != NULL)
			val = max(val, root->right->height + 1);

		root->height = val;
	}
}

Node* LLR(Node* root) {
	Node* tmpnode = root->left;

	root->left = tmpnode->right;
	if (tmpnode->right != NULL)
		tmpnode->right->parent = root;

	tmpnode->right = root;
	tmpnode->parent = root->parent;
	root->parent = tmpnode;

	if (tmpnode->parent != NULL && root->key < tmpnode->parent->key) {
		tmpnode->parent->left = tmpnode;
	} else {
		if (tmpnode->parent != NULL)
			tmpnode->parent->right = tmpnode;
	}
	root = tmpnode;

	Updateheight(root->left);
	Updateheight(root->right);
	Updateheight(root);
	Updateheight(root->parent);

	return root;
}

Node* RRR(Node* root) {
	Node* tmpnode = root->right;

	root->right = tmpnode->left;
	if (tmpnode->left != NULL)
		tmpnode->left->parent = root;

	tmpnode->left = root;
	tmpnode->parent = root->parent;
	root->parent = tmpnode;

	if (tmpnode->parent != NULL && root->key < tmpnode->parent->key) {
		tmpnode->parent->left = tmpnode;
	} else {
		if (tmpnode->parent != NULL)
			tmpnode->parent->right = tmpnode;
	}
	root = tmpnode;

	Updateheight(root->left);
	Updateheight(root->right);
	Updateheight(root);
	Updateheight(root->parent);

	return root;
}

Node* LRR(Node* root) {
	root->left = RRR(root->left);
	return LLR(root);
}

Node* RLR(Node* root) {
	root->right = LLR(root->right);
	return RRR(root);
}

Node* Balance(Node* root) {
	int firstheight = 0;
	int secondheight = 0;

	if (root->left != NULL)
		firstheight = root->left->height;

	if (root->right != NULL)
		secondheight = root->right->height;

	if (abs(firstheight - secondheight) == 2) {
		if (firstheight < secondheight) {

			int rightheight1 = 0;
			int rightheight2 = 0;
			if (root->right->right != NULL)
				rightheight2 = root->right->right->height;

			if (root->right->left != NULL)
				rightheight1 = root->right->left->height;

			if (rightheight1 > rightheight2) {
				root = RLR(root);
			} else {
				root = RRR(root);
			}
		} else {
			int leftheight1 = 0;
			int leftheight2 = 0;
			if (root->left->right != NULL)
				leftheight2 = root->left->right->height;

			if (root->left->left != NULL)
				leftheight1 = root->left->left->height;

			if (leftheight1 > leftheight2) {
				root = LLR(root);
			} else {
				root = LRR(root);
			}
		}
	}
	return root;
}

Node* Insert(Node* root, Node* parent, int key) {
	if (root == NULL) {
		root = new Node;

		if (root == NULL) {
			cout << "Error in memory" << endl;
		} else {
			root->height = 1;
			root->left = NULL;
			root->right = NULL;
			root->parent = parentent;
			root->key = key;
		}
	} else if (root->key > key) {
		root->left = Insert(root->left,
				root, key);

		int firstheight = 0;
		int secondheight = 0;

		if (root->left != NULL)
			firstheight = root->left->height;

		if (root->right != NULL)
			secondheight = root->right->height;

		if (abs(firstheight - secondheight) == 2) {
			if (root->left != NULL && key < root->left->key) {
				root = LLR(root);
			} else {
				root = LRR(root);
			}
		}
	} else if (root->key < key) {
		root->right = Insert(root->right, root, key);

		int firstheight = 0;
		int secondheight = 0;

		if (root->left != NULL)
			firstheight
				= root->left->height;

		if (root->right != NULL)
			secondheight = root->right->height;

		if (abs(firstheight - secondheight) == 2) {
			if (root->right != NULL && key < root->right->key) {
				root = RLR(root);
			} else {
				root = RRR(root);
			}
		}
	} else {
	}
	Updateheight(root);

	return root;
}

Node* Delete(Node* root, int key) {
	if (root != NULL) {

		if (root->key == key) {
			if (root->right == NULL && root->left != NULL) {
				if (root->parent != NULL) {
					if (root->parent->key < root->key)
						root->parent->right = root->left;
					else
						root->parent->left = root->left;
					Updateheight(root->parent);
				}
				root->left->parent = root->parent;
				root->left = Balance(root->left);

				return root->left;
			} else if (root->left == NULL && root->right != NULL) {
				if (root->parent != NULL) {
					if (root->parent->key < root->key)
						root->parent->right = root->right;
					else
						root->parent->left = root->right;
					Updateheight(root->parent);
				}
				root->right->parent = root->parent;
				root->right = Balance(root->right);

				return root->right;
			} else if (root->left == NULL && root->right == NULL) {
				if (root->parent->key < root->key) {
					root->parent->right = NULL;
				} else {
					root->parent->left = NULL;
				}
				if (root->parent != NULL)
					Updateheight(root->parent);
				root = NULL;

				return NULL;
			} else {
				Node* tmpnode = root;

				tmpnode = tmpnode->right;
				while (tmpnode->left != NULL) {
					tmpnode = tmpnode->left;
				}
				int val = tmpnode->key;

				root->right = Delete(root->right, tmpnode->key);
				root->key = val;
				root = Balance(root);
			}
		} else if (root->key < key) {
			root->right = Delete(root->right, key);

			root = Balance(root);
		} else if (root->key > key) {
			root->left = Delete(root->left, key);

			root = Balance(root);
		}
		if (root != NULL) {
			Updateheight(root);
		}
	} else {
		cout << "Key to be deleted " << "could not be found\n";
	}

	return root;
}

void printpreorder(Node* root) {
	cout << "Node: " << root->key << ", parentent Node: ";

	if (root->parent != NULL)
		cout << root->parent->key << endl;
	else
		cout << "NULL" << endl;

	if (root->left != NULL) {
		printpreorder(root->left);
	}

	if (root->right != NULL) {
		printpreorder(root->right);
	}
}

int main() {
	Node* root = NULL;

	root = Insert(root, NULL, 10);
	root = Insert(root, NULL, 20);
	root = Insert(root, NULL, 30);
	root = Insert(root, NULL, 40);
	root = Insert(root, NULL, 50);
	root = Insert(root, NULL, 25);

	printpreorder(root);
	root = Delete(root, 10);

	cout << "After deletion:\n";
	printpreorder(root);

}
