#ifndef map_HPP
#define map_HPP

#include <memory>
#include <limits>
#include <cstddef>
#include <iostream>
#include "utils.hpp"
#include "pair.hpp"
#include <map>
#include "iterator_traits.hpp"
#include <type_traits>

namespace ft {
	template <class Key, class T, class Compare, class Alloc> class map;

	template <class T> struct less : std::binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const { return x < y; }
	};

	template <	class Key,
				class T,
				class Compare = ft::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
		class map {

			private:
				struct Node;

			public:
				/* TYPES */
				typedef Key											key_type;
				typedef T											mapped_type;
				typedef ft::pair<const key_type, mapped_type>		value_type;
				typedef Compare										key_compare;
				typedef Alloc										allocator_type;
				typedef typename allocator_type::reference			reference;
				typedef typename allocator_type::const_reference	const_reference;
				typedef typename allocator_type::pointer			pointer;
				typedef typename allocator_type::const_pointer		const_pointer;
				typedef std::size_t									size_type;

			private:





				struct Node {
					value_type		_pair;
					Node			*parent;
					Node			*left;
					Node			*right;
					int				height;
				};




				class value_compare
				{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
					friend class map;

					protected:
						Compare comp;
						value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
					public:
						typedef bool result_type;
						typedef value_type first_argument_type;
						typedef value_type second_argument_type;

						bool	operator() (const value_type& x, const value_type& y) const {
								return comp(x.first, y.first);
						}
				};
//****************************************************************************//
//*                            MAP ITERATOR                                  *//
//****************************************************************************//

	template <	class U,
				class Distance = std::ptrdiff_t,
				class Pointer = U*,
				class Reference = U& >
		class	IteratorMap {

			friend class map<Key, T, Compare, Alloc>;

			public:
				typedef U							value_type;
				typedef Pointer						pointer;
				typedef Reference					reference;
				typedef Distance					difference_type;
				typedef typename map::key_compare	key_compare;

			protected:
				Node		*_pos;
				Node		*_p_end;
				key_compare	_comp;

			public:
				IteratorMap() : _pos(NULL) {}

//				operator IteratorMap<const U>() const {
//					return IteratorMap<const U>(_pos);
//				}

				IteratorMap(const IteratorMap<typename std::remove_const<U>::type> &it)
					: _pos(it._pos), _p_end(it._p_end), _comp(it._comp) {}

			private:
				explicit IteratorMap(Node *pos, Node *end, key_compare comp)
					: _pos(pos), _p_end(end), _comp(comp) {}


			public:
//					IteratorMap(const IteratorMap<U> &it) {
//						*this = it;
//					}

//					IteratorMap	&operator=(const IteratorMap<U> &it) {
//						std::cout << "operator = iterator\n";
//						_pos = it._pos;
//						_pos->parent = it._pos->parent;
//						_pos->left = it._pos->left;
//						_pos->right = it._pos->right;
//
//						_p_end = it._p_end;
//						_comp = it._comp;
//						return *this;
//					}

				~IteratorMap() {}

				reference	operator*() const { return _pos->_pair; }
				pointer		operator->() const { return &(_pos->_pair); }

				IteratorMap	operator++(int) {
					IteratorMap	tmp(*this);

					if (_pos->right) {
						if (!_pos->right->left || _pos->right == _p_end)
							_pos = _pos->right;
						else
							_pos = ft::map<Key, T, Compare, Alloc>::minValueNode(_pos->right);
					} else if (_pos->parent) {
						Node	*tmpNode = _pos;

						_pos = _pos->parent;
						while (_pos && _comp(tmpNode->_pair.first, _pos->_pair.first) == false)
							_pos = _pos->parent;
					}
					return tmp;
				}

				IteratorMap	&operator++() {

					if (_pos->right) {
						if (!_pos->right->left || _pos->right == _p_end) {
							_pos = _pos->right;
						}
						else {
							_pos = ft::map<Key, T, Compare, Alloc>::minValueNode(_pos->right);
						}
					} else if (_pos->parent) {
						Node	*tmpNode = _pos;

						_pos = _pos->parent;
						while (_pos && _comp(tmpNode->_pair.first, _pos->_pair.first) == false) {
								_pos = _pos->parent;
						}
					}
					return *this;
				}

				IteratorMap	operator--(int) {
					IteratorMap	tmp(*this);

					if (_pos == _p_end) {
						_pos = _p_end->parent;
						return tmp;
					} else if (_pos == _p_end->right) {
						_pos = _p_end;
						return tmp;
					}
					if (_pos->left) {
						if (!_pos->left->right)
							_pos = _pos->left;
						else
							_pos = ft::map<Key, T, Compare, Alloc>::maxValueNode(_pos->left, _p_end);
					} else if (_pos->parent) {
						Node *tmpNode = _pos;

						_pos = _pos->parent;
						while (_comp(_pos->_pair.first, tmpNode->_pair.first) == false)
							_pos = _pos->parent;
					}
					return tmp;
				}

				IteratorMap	&operator--() {
					if (_pos == _p_end) {
						_pos = _p_end->parent;
						return *this;
					} else if (_pos == _p_end->right) {
						_pos = _p_end;
						return *this;
					}
					if (_pos->left) {
						if (!_pos->left->right)
							_pos = _pos->left;
						else
							_pos = ft::map<Key, T, Compare, Alloc>::maxValueNode(_pos->left, _p_end);
					} else if (_pos->parent != NULL) {
						Node *tmpNode = _pos;

						_pos = _pos->parent;
						while (_pos && _comp(_pos->_pair.first, tmpNode->_pair.first) == false)
							_pos = _pos->parent;
					}
					return *this;
				}

				bool	operator==(const IteratorMap &it) const {
					return _pos == it._pos;
				}

				bool	operator!=(const IteratorMap &it) const {
					return _pos != it._pos;
				}
		};

			public:
				typedef IteratorMap<value_type>								iterator;
				typedef IteratorMap<const value_type>						const_iterator;
				typedef std::reverse_iterator<iterator>						reverse_iterator;
				typedef std::reverse_iterator<const_iterator>				const_reverse_iterator;
				typedef typename iterator_traits<iterator>::difference_type	difference_type;


//****************************************************************************//
//*                            MAP IMPLEMENTATION                            *//
//****************************************************************************//

			public:
				/* CONSTRUCT/COPY/DESTROY */

				map	&operator=(const ft::map<Key, T, Compare, Alloc> &map) {
					if (this != &map) {
						clear();
						_alloc = map.get_allocator();
						_comp = map._comp;
//						std::cout << "Tout est clear!!!\n";
//						std::cout << _root->_pair.first << '\n';
						_size = 0;
//						_p_end = _alloc_node.allocate(1);
						_root =	NULL;
						_p_end->parent = NULL;
						_p_end->left = NULL;
						_p_end->right = NULL;
						_p_end->height = 0;
						insert(map.begin(), map.end());
					}
					return *this;
				}

				//empty (1)
				explicit map(const key_compare &comp = key_compare(),
						const allocator_type &alloc = allocator_type())
					: _alloc(alloc), _comp(comp), _size(0), _root(NULL) {
						_p_end = _alloc_node.allocate(1);
						_p_end->parent = _root;
						_p_end->left = NULL;
						_p_end->right = NULL;
						_p_end->height = 0;
					}

				//fill (2)
				template <class InputIterator>
					map(InputIterator first, InputIterator last,
							const key_compare &comp = key_compare(),
							const allocator_type &alloc = allocator_type())
					: _alloc(alloc), _comp(comp), _size(0), _root(NULL) {
						_p_end = _alloc_node.allocate(1);
						_p_end->parent = _root;
						_p_end->left = NULL;
						_p_end->right = NULL;
						_p_end->height = 0;

						this->insert(first, last);
					}

				//copy (3)
				map(const ft::map<Key, T, Compare, Alloc> &map) {

					_alloc = map.get_allocator();
					_comp = map._comp;
					_size = 0;
					_p_end = _alloc_node.allocate(1);
					_root = NULL;
					_p_end->parent = _root;
					_p_end->parent = NULL;
					_p_end->left = NULL;
					_p_end->right = NULL;
					_p_end->height = 0;

					insert(map.begin(), map.end());
//					linkEnd();
				}

				~map() {
					clear();
					_alloc_node.deallocate(_p_end, 1);
				}

				allocator_type	get_allocator() const {
					return _alloc;
				}

				void	printTree() {
					std::cout << "PRINT TREE!!! \n";
					preOrder(_root);
				}

				/* ITERATORS */
				iterator				begin() {
					if (_size == 0)
						return end();
					return iterator(minValueNode(_root), _p_end, _comp);
				}

				const_iterator			begin() const {
					if (_size == 0)
						return end();
					return const_iterator(minValueNode(_root), _p_end, _comp);
				}

				iterator				end() {
					return iterator(_p_end, _p_end, _comp);
				}

				const_iterator			end() const {
					return const_iterator(_p_end, _p_end, _comp);
				}

				reverse_iterator		rbegin() {
					if (_size == 0)
						return begin();
					return reverse_iterator(_p_end, _p_end, _comp);
				}

				const_reverse_iterator	rbegin() const {
					if (_size == 0)
						return begin();
					return const_reverse_iterator(_p_end, _p_end, _comp);
				}

				reverse_iterator		rend() {
					return reverse_iterator(minValueNode(_root, _p_end, _comp));
				}

				const_reverse_iterator	rend() const {
					return const_reverse_iterator(minValueNode(_root, _p_end, _comp));
				}

				/* CAPACITY */
				size_type	size() const { return _size; }

				size_type	max_size() const { return _alloc.max_size(); }

				bool		empty() const { return (_size == 0); }

				/* ELEMENT ACCES */

				mapped_type	&operator[](const key_type &k) {
//					std::cout << mapped_type() << std::endl;
//					std::cout << ft::make_pair(k, mapped_type()).second <<'\n';
					return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
				};

				/* UTILS */

				key_compare		key_comp() const {
					return key_compare();
				}

				value_compare	value_comp() const {
					return value_compare(key_comp());
				}

				size_type		count(const key_type &k) const {
//					return (search(k) != NULL);
					if (search(k))
						return 1;
					return 0;
				}

				iterator		find(const key_type &k) {
					Node	*tmp = search(k);

					if (!tmp) {
						return end();
					}
					return iterator(tmp, _p_end, _comp);
				}

				const_iterator	find(const key_type &k) const {
					Node	*tmp = search(k);

					if (!tmp)
						return end();
					return const_iterator(tmp, _p_end, _comp);
				}

				iterator		lower_bound(const key_type &k) {
					return (iterator(find(k), _p_end, _comp));
				}

				const_iterator	lower_bound(const key_type &k) const {
					return (const_iterator(find(k), _p_end, _comp));
				}

				iterator		upper_bound(const key_type &k) {
					iterator	it(find(k), _p_end, _comp);

					if (it != end())
						++it;
					return it;
				}

				const_iterator	upper_bound(const key_type &k) const {
					const_iterator	it(find(k), _p_end, _comp);

					if (it != end())
						++it;
					return it;

				}

				pair<const_iterator, const_iterator>	equal_range(
						const key_type &k) const {
					return (ft::make_pair(lower_bound(k), upper_bound(k)));
				}

				pair<iterator, iterator>	equal_range(const key_type &k) {
					return (ft::make_pair(lower_bound(k), upper_bound(k)));
				}

				/* MODIFIERS */

				//INSERT

				//single element (1)
				pair<iterator, bool>	insert(const value_type& val) {

						if (!_root) {
							_root = insert(_root, ft::make_pair(val.first, val.second));
							linkEnd();
							return ft::make_pair<iterator, bool>(find(val.first), true);
						}
						linkEnd();
						Node	*tmp;

						tmp = search(val.first);

						if (tmp)
							return ft::make_pair<iterator, bool>(find(val.first), false);
					unlinkEnd();
					_root = insert(_root, ft::make_pair(val.first, val.second));
					linkEnd();
					return ft::make_pair<iterator, bool>(find(val.first), true);
				}

				//with hint (2)
				iterator	insert(iterator pos, const value_type& val) {
					insert(val);
					return pos;
				}

				//range (3)
				template <class InputIterator>
					void	insert(InputIterator first, InputIterator last) {
//					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
						while (first != last) {
							this->insert(*first);
							++first;
						}
					}

				void	erase(iterator position) {
					erase(position->first);
				}

				size_type	erase(const key_type &k) {
					Node	*node = search(k);

					if (node) {
						unlinkEnd();
						_root = deleteNode(_root, node->_pair);
						std::cout << "ROOOOOOT =" << _root->_pair.first <<std::endl;
						linkEnd();
						return 1;
					}
					linkEnd();
					return 0;
				}

				void	erase(iterator first, iterator last) {
					while (first != last) {
						erase(first->first);
//						this->printTree();
						++first;
					}
				}

				void		swap(map<Key, T, Compare, Alloc> &x) {
					Node		*tmp;
					size_type	tmp_size;
					key_compare	tmp_comp;

					tmp = _root;
					_root = x._root;
					x._root = tmp;

					tmp = _p_end;
					_p_end = x._p_end;
					x._p_end = tmp;

					tmp_size = _size;
					_size = x._size;
					x._size = tmp_size;

					tmp_comp = _comp;
					_comp = x._comp;
					x._comp = tmp_comp;
				}

				void		clear() {
					if (_size != 0) {
						unlinkEnd();
						destroyTree();
						_size = 0;
					}
				}

//****************************************************************************//
//*                              AVL TREE                                    *//
//****************************************************************************//

			private:
				int	height(Node *node) {
					if (!node)
						return 0;
					return node->height;
				}

				int	max(int a, int b) {
					return (a > b) ? a : b;
				}

				Node	*newNode(value_type pair) {
					Node	*node = _alloc_node.allocate(1);

					_alloc.construct(&node->_pair, pair);
					node->parent = NULL;
					node->left = NULL;
					node->right = NULL;
					node->height = 1;
					++_size;

					return (node);
				}

/*
** T1, T2 and T3 are subtrees of the tree,
** rooted with y (on the left side) or x (on the right side)
**
**     y                               x
**    / \     Right Rotation          /  \
**   x   T3   - - - - - - - >        T1   y
**  / \       < - - - - - - -            / \
** T1  T2     Left Rotation            T2  T3
**
*/

				Node	*rightRotate(Node *y) {
					Node	*x = y->left;
					Node	*T2 = x->right;

					x->right = y;
					x->parent = y->parent;
					y->parent = x;
					y->left = T2;
					if (y->left)
						y->left->parent = y;

					y->height = max(height(y->left), height(y->right)) + 1;
					x->height = max(height(x->left), height(x->right)) + 1;
					return x;
				}

				Node	*leftRotate(Node *x) {
					Node	*y = x->right;
					Node	*T2 = y->left;

					y->left = x;
					y->parent = x->parent;
					x->parent = y;
					x->right = T2;

					if (x->right)
						x->right->parent = x;

					x->height = max(height(x->left), height(x->right)) + 1;
					y->height = max(height(y->left), height(y->right)) + 1;
					return y;
				}

				int	getBalance(Node *node) {
					if (!node)
						return 0;
					return height(node->left) - height(node->right);
				}

				Node	*search(const key_type &k) const {
					return searchRecurs(_root, k);
				}

				Node	*searchRecurs(Node *node, const key_type &k) const {
					if (!node || node == _p_end) {
						return NULL;
					}
					if (_comp(k, node->_pair.first) == false
						&& _comp(node->_pair.first, k) == false)
						return node;

					if (node->left && _comp(k, node->_pair.first)) {
						return searchRecurs(node->left, k);
					}
					else if (node->right) {// && node->right != _p_end) {
						return searchRecurs(node->right, k);
					}
					return NULL;
				}

				Node	*insert(Node *node, value_type pair) {
					if (!node) {
						return (newNode(pair));
					}

					unlinkEnd();
					if (pair.first < node->_pair.first) {
						node->left = insert(node->left, pair);
						node->left->parent = node;
					} else if (pair.first > node->_pair.first) {
						node->right = insert(node->right, pair);
						node->right->parent = node;
					} else {
						linkEnd();
						return node;
					}

					node->height = 1 + max(height(node->left), height(node->right));

					int balance = getBalance(node);

					if (balance > 1 && pair.first < node->left->_pair.first)
						return rightRotate(node);

					if (balance < -1 && pair.first > node->right->_pair.first)
						return leftRotate(node);

					if (balance > 1 && pair.first > node->left->_pair.first) {
						node->left = leftRotate(node->left);
						return rightRotate(node);
					}

					if (balance < -1 && pair.first < node->right->_pair.first) {
						node->right = rightRotate(node->right);
						return leftRotate(node);
					}

					linkEnd();
					return node;
				}

				void	preOrder(Node *root) {
					if (root && root != _p_end) {
						std::cout << "First: " << root->_pair.first
							<< " " << root->_pair.second << ", height = " << root->height
							<< " " << "root addr = " << &root << ", parent addr = " << root->parent << '\n';
						if (root->left)
							std::cout << "left " << root->left->_pair.first << '\n';
						if (root->right && root->right != _p_end)
							std::cout << "right " << root->right->_pair.first << '\n';
						preOrder(root->left);
						preOrder(root->right);
					}
				}

				void	linkEnd() {
					if (_root && _size > 0) {
						Node	*tmp;

						tmp = maxValueNode(_root, _p_end);
//						std::cout << "LINK MAX = " << tmp->_pair.first << std::endl;
						tmp->right = _p_end;
						_p_end->parent = tmp;
					}
				}

				void	unlinkEnd() {
					if (_root) {
						if (_p_end->parent) {
//							if (_p_end->parent->right)
								_p_end->parent->right = NULL;
						}
					}
				}

				static Node	*minValueNode(Node *root) {
					if (!root || !root->left)
						return root;
					if (root->left->_pair.first < root->_pair.first)
						return minValueNode(root->left);
					return root;
				}

				static Node	*maxValueNode(Node *root, Node *end) {
					if (!root || !root->right || root->right == end)
						return root;
					if (root->right->_pair.first > root->_pair.first)
						return maxValueNode(root->right, end);
					return root;
				}

				Node	*deleteNode(Node *node, const value_type &val) {
					if (!node) {
						return node;
					}
					if (val.first < node->_pair.first)
						node->left = deleteNode(node->left, val);
					else if (val.first > node->_pair.first)
						node->right = deleteNode(node->right, val);
					else {
						if (!node->left || !node->right) {
							Node	*tmp = node->left ? node->left : node->right;

							if (!tmp) {
								tmp = node;
//								if (node->parent)
//									tmp->parent->left = NULL;
//									tmp->parent->right = NULL;
//								node->parent->right = NULL;
								std::cout << "NULLLL\n";
								node = NULL;
							} else {

								node->parent = tmp->parent;
//								if (node->parent)
//									std::cout << "PARENT = " << node->parent->_pair.first << std::endl;
								node->left = tmp->left;
//								if (node->left)
//									std::cout << "left = " << node->left->_pair.first << std::endl;
								node->right = tmp->right;
//								if (node->right)
//									std::cout << "right = " << node->right->_pair.first << std::endl;
								node->height = tmp->height;

								_alloc_node.destroy(&node->_pair);
								_alloc.construct(&node->_pair, tmp->_pair);
							}
							_alloc_node.destroy(&tmp->_pair);
							_alloc_node.deallocate(tmp, 1);
							--_size;
						} else {
							Node	*tmp = minValueNode(node->right);

							_alloc_node.destroy(&node->_pair);
							_alloc.construct(&node->_pair, tmp->_pair);

							node->right = deleteNode(node->right, tmp->_pair);
						}
					}
					if (!node) {
						return node;
					}

					node->height = 1 + max(height(node->left),
											height(node->right));

					int	balance = getBalance(node);

					if (balance > 1 && getBalance(node->left) >= 0)
						return rightRotate(node);

					if (balance > 1 && getBalance(node->left) < 0) {
						node->left = leftRotate(node->left);
						return rightRotate(node);
					}

					if (balance < -1 && getBalance(node->right) <= 0)
						return leftRotate(node);

					if (balance < -1 && getBalance(node->right) > 0) {
						node->right = rightRotate(node->right);
						return leftRotate(node);
					}
					return node;
				}

				void	destroyTree() {
					destroyTree(_root);
				}

				void	destroyTree(Node *leaf) {
					if (leaf) {
						if (leaf->left)
							destroyTree(leaf->left);
						if (leaf->right)// && leaf->right != _p_end)
							destroyTree(leaf->right);
						_alloc_node.destroy(&leaf->_pair);
						_alloc_node.deallocate(leaf, 1);
					}
				}

				Alloc		_alloc;
				key_compare	_comp;
				size_type	_size;
				Node		*_root;
				Node		*_p_end;
				typename allocator_type::template rebind<Node>::other	_alloc_node;
		};

	template<class Key, class T, class Compare, class Alloc>
		bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			if (lhs.size() != rhs.size())
				return false;
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (!(lhs == rhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator<(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.begin()));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (!(rhs < lhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator>(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (rhs < lhs);
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (!(lhs < rhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
			x.swap(y);
		}
}

#endif
