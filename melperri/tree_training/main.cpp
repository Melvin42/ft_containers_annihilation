#include <cstddef>
#include <iostream>

using namespace std;

struct	node;
class	Btree;

struct	node {
	int		key_value;
	node	*left;
	node	*right;
};

class Btree {
	public:
		Btree() : _root(NULL) {}
		~Btree() { destroy_tree(); }

		void	insert(int key) {
			if (_root)
				insert(key, _root);
			else {
				_root = new node;
				_root->key_value = key;
				_root->left = NULL;
				_root->right = NULL;
			}
		}

		node	*search(int key) {
			 return search(key, _root);
		}

		void	destroy_tree() {
			destroy_tree(_root);
		}

		void	print_tree() {
			print_node(_root);
		}

	private:
		void	print_node(node *leaf) {
			if (leaf) {
				cout << leaf->key_value << '\n';
				print_node(leaf->left);
				print_node(leaf->right);
			}
		}

		void	destroy_tree(node *leaf) {
			if (leaf) {
				destroy_tree(leaf->left);
				destroy_tree(leaf->right);
				delete leaf;
			}
		}

		void	insert(int key, node *leaf) {
			if (key < leaf->key_value)
			{
				if (leaf->left) {
					insert(key, leaf->left);
				} else {
					leaf->left = new node;
					leaf->left->key_value = key;
					leaf->left->left = NULL;
					leaf->left->right = NULL;
				}
			} else if (key >= leaf->key_value) {
				if (leaf->right) {
					insert(key, leaf->right);
				} else {
					leaf->right = new node;
					leaf->right->key_value = key;
					leaf->right->left = NULL;
					leaf->right->right = NULL;
				}
			}
		}

		node	*search(int key, node *leaf) {
			if (leaf) {
				if (key == leaf->key_value)
					return leaf;
				if (key < leaf->key_value)
					return search(key, leaf->left);
				else
					return search(key, leaf->right);
			} else
				return NULL;
		}

		node	*_root;
};

int	main() {
	Btree	tree;

	tree.insert(2);
	tree.insert(16);
	tree.insert(6);
	tree.insert(3);
	tree.insert(0);
	tree.insert(1);
	tree.insert(4);
	tree.insert(5);
	tree.insert(8);
	tree.insert(10);
	tree.insert(14);
	tree.insert(15);
	tree.insert(11);
	tree.insert(9);
	tree.insert(12);
	tree.insert(13);
	tree.insert(7);

	tree.print_tree();
	return 0;
}
