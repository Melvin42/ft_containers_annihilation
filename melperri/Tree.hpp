#ifndef TREE_HPP
#define TREE_HPP

#include <bits/stdc++.h>

namespace ft {

	template <class T>
		class Node {
			public:
				Node() {}
				Node(const Node<T> &node) { *this = node; }

				~Node() {}

				Node	&operator=(const Node<T> &node) {
					_pair = node._pair;
					left = node.left;
					right = node.right;
					height = node.height;

					return *this;
				}

				T		_pair;
				Node	*left;
				Node	*right;
				int		height;
		};

	template <class T>
		class Tree {
			public:
				Tree() : _root(NULL) {}

		//		AVLTree	&operator=(const AVLTree &tree) {
		//			_root = tree._
		//			return *this;
		//		}

				~Tree() { destroyTree(); }

				int	height(Node<T> *node) {
					if (!node)
						return 0;
					return node->height;
				}

				int	max(int a, int b) {
					return (a > b) ? a : b;
				}

				void	destroyTree() {
					destroyTree(_root);
				}

				void	insert(T pair) {
					_root = insert(_root, pair);
				}

				void	printTree() {
					preOrder(_root);
				}

			private:
				Node<T>	*newNode(T pair) {
					Node<T>	*node = new Node<T>();

					node->_pair = pair;
					node->left = NULL;
					node->right = NULL;
					node->height = 1;

					return (node);
				}

				Node<T>	*rightRotate(Node<T> *y) {
					Node<T>	*x = y->left;
					Node<T>	*T2 = x->right;

					x->right = y;
					y->left = T2;

					y->height = max(height(y->left), height(y->right)) + 1;
					x->height = max(height(x->left), height(x->right)) + 1;

					return x;
				}

				Node<T>	*leftRotate(Node<T> *x) {
					Node<T>	*y = x->right;
					Node<T>	*T2 = y->left;

					y->left = x;
					x->right = T2;

					x->height = max(height(x->left), height(x->right)) + 1;
					y->height = max(height(y->left), height(y->right)) + 1;

					return y;
				}

				int	getBalance(Node<T> *node) {
					if (!node)
						return 0;
					return height(node->left) - height(node->right);
				}

				Node<T>	*insert(Node<T> *node, T pair) {
					if (!node)
						return (newNode(pair));

					if (pair < node->_pair)
						node->left = insert(node->left, pair);
					else if (pair > node->_pair)
						node->right = insert(node->right, pair);
					return node;

					node->height = 1 + max(height(node->left), height(node->right));

					int balance = getBalance(node);

					if (balance > 1 && pair < node->left->_pair)
						return rightRotate(node);

					if (balance < -1 && pair > node->right->_pair)
						return leftRotate(node);

					if (balance > 1 && pair > node->left->_pair) {
						node->left = leftRotate(node->left);
						return rightRotate(node);
					}

					if (balance < -1 && pair < node->right->_pair) {
						node->right = rightRotate(node->right);
						return leftRotate(node);
					}

					return node;
				}

				void	preOrder(Node<T> *root) {
					if (root) {
						std::cout << root->_pair.first << " ";
						preOrder(root->left);
						preOrder(root->right);
					}
				}

				void	destroyTree(Node<T> *leaf) {
					if (leaf) {
						destroyTree(leaf->left);
						destroyTree(leaf->right);
						delete leaf;
					}
				}

				Node<T>	*_root;
		};
}

#endif
