#include <iostream>
#include <limits>
#include <cmath>
#include <memory>
#include "pair.hpp"
#include "utils.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template <
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> > >
	class map {
///////////////////////////********TYPEDEF**********////////////////////////////////
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;
			typedef Allocator									allocator_type;
			typedef value_type									&reference;
			typedef const value_type							&const_reference;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef value_type									*pointer;
			typedef const value_type							*const_pointer;

///////////////////////////**********NODE************////////////////////////////////
		private:
			struct Node {
				bool			end;
				value_type		pair;
				int				height;
				Node			*parent;
				Node			*left;
				Node			*right;
			};
///////////////////////////************************////////////////////////////////

			//////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
			///////////////////////////ITERATOR///////////////////////////////////////////
			////////////////////////////SYSTEM/////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////

	template <class U>	
	class MapIt {
///////////////////////////********FRIEND***********////////////////////////////////
		friend class map<Key, T, Compare, Allocator>;
///////////////////////////************************////////////////////////////////

			public:
				typedef U										value_type;
				typedef value_type								*pointer;
				typedef value_type								&reference;
				typedef std::ptrdiff_t							difference_type;
				typedef std::bidirectional_iterator_tag			iterator_category;


				Node	*_p;
				Node	*_end;
				Compare	_comp;
///////////////////////////************************////////////////////////////////

			private:
				explicit MapIt(Node *node, Node *end) : _p(node), _end(end) {}
///////////////////////////************************////////////////////////////////

			public:

				MapIt() {}
				MapIt(const MapIt<typename std::remove_const<U>::type> &it) : _p(it._p), _end(it._end) {}
				~MapIt() {};
				/*
				MapIt &operator=(const MapIt &it) {
					_p = it._p;
					_end = it._end;
					return *this;
				};
				*/
///////////////////////////************************////////////////////////////////

				reference operator*() {return _p->pair;}
				reference operator*() const {return _p->pair;}
				pointer operator->() {return &(_p->pair);}
				const pointer operator->() const {return &(_p->pair);}
				Node *base() {return _p;}
				const Node *base() const {return _p;}
///////////////////////////************************////////////////////////////////

				MapIt &operator++() {
					if (_p->right) {
						if (!_p->right->left || _p->right == _end)
							_p = _p->right;
						else
							_p = minValueNode(_p->right);
					} else if (_p->parent) {
						Node	*tmp = _p;
						_p = _p->parent;
						while (_p && _comp(tmp->pair.first, _p->pair.first) == false)
							_p = _p->parent;
					}
					return *this;
				};

				MapIt &operator--() {
					if (_p == _end) {
						_p = _end->parent;
						return *this;
					}
					if (_p->left) {
						if (!_p->left->right)
							_p = _p->left;
						else
							_p = maxValueNode(_p->left);
					} else if (_p->parent) {
						Node	*tmp = _p;
						_p = _p->parent;
						while (_p && _comp(_p->pair.first, tmp->pair.first) == false)
							_p = _p->parent;
					}
					return *this;
				};
///////////////////////////************************////////////////////////////////
				MapIt operator++(int) {MapIt tmp(*this); operator++(); return tmp;}
				MapIt operator--(int) {MapIt tmp(*this); operator--(); return tmp;}
			
				MapIt &operator+=(int n) {for (int i = 0; i < n; i++) {operator++();} return *this;}
				MapIt &operator-=(int n) {for (int i = 0; i < n; i++) {operator--();} return *this;}

				MapIt operator+(int n) const {MapIt r(*this); r+=n; return r;}
				MapIt operator-(int n) const {MapIt r(*this); r-=n; return r;}
///////////////////////////************************////////////////////////////////

			bool operator!=(const MapIt &rhs) const {
				return _p != rhs._p;
			}

			bool operator==(const MapIt &rhs) const {
				return !(_p != rhs._p);
			}
	};
///////////////////////////************************////////////////////////////////


			//////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
			///////////////////////////AVL-TREE///////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
			
			
			private:

				int max(int a, int b) {
					return (a > b) ? a : b;
				};

				int height(Node *node) {
					if (!node) {return 0;}
					return node->height;
				};

				void UpdateHeight(Node *root) {
					if (root) {
						int h = 1;
						if (root->left)
							h = root->left->height + 1;
						if (root->right)
							h = max(h, root->right->height + 1);
						root->height = h;
					}
				}

				void getMaxHeight(Node *root, int *height) {
					if (!root) {return ;}
					getMaxHeight(root->left, height);
					if (root->height > *height) {*height = root->height;}
					getMaxHeight(root->right, height);
				};

				static Node *minValueNode(Node *node) {
					Node	*current = node;
					while (current && current->left != NULL)
						current = current->left;
					return current;
				};

				static Node *maxValueNode(Node *node) {
					Node	*current = node;
					while (current && current->right != NULL && !current->right->end)
						current = current->right;
					return current;
				};

				Node *newNode() {
					Node	*ret = _allocNode.allocate(1);
					ret->end = false;
					ret->height = 1;
					ret->parent = NULL;
					ret->left = NULL;
					ret->right = NULL;
					return ret;
				}

				Node *newNode(const value_type &pr) {
					Node	*ret = _allocNode.allocate(1);

					++_size;
					ret->end = false;
					ret->height = 1;
					_alloc.construct(&ret->pair, pr);
					ret->parent = NULL;
					ret->left = NULL;
					ret->right = NULL;
					return ret;
				}

///////////////////////////************************////////////////////////////////


				Node *LLR(Node *root) {
					Node *tmpNode = root->left;
					root->left = tmpNode->right;
					if (tmpNode->right)
						tmpNode->right->parent = root;
					tmpNode->right = root;
					tmpNode->parent = root->parent;
					root->parent = tmpNode;
					if (tmpNode->parent && _comp(root->pair.first, tmpNode->parent->pair.first))
						tmpNode->parent->left = tmpNode;
					else {
						if (tmpNode->parent)
							tmpNode->parent->right = tmpNode;
					}
					root = tmpNode;
					UpdateHeight(root->left);
					UpdateHeight(root->right);
					UpdateHeight(root);
					UpdateHeight(root->parent);
					return root;
				}

				Node *RRR(Node *root) {
					Node *tmpNode = root->right;
					root->right = tmpNode->left;
					if (tmpNode->left)
						tmpNode->left->parent = root;
					tmpNode->left = root;
					tmpNode->parent = root->parent;
					root->parent = tmpNode;
					if (tmpNode->parent && _comp(root->pair.first, tmpNode->parent->pair.first))
						tmpNode->parent->left = tmpNode;
					else {
						if (tmpNode->parent)
							tmpNode->parent->right = tmpNode;
					}
					root = tmpNode;
					UpdateHeight(root->left);
					UpdateHeight(root->right);
					UpdateHeight(root);
					UpdateHeight(root->parent);
					return root;
				}

				Node *LRR(Node *root) {
					root->left = RRR(root->left);
					return LLR(root);
				}

				Node *RLR(Node *root) {
					root->right = LLR(root->right);
					return RRR(root);
				}

				Node *Balance(Node *root) {
					int firstheight = 0;
					int secondheight = 0;
					if (root->left)
						firstheight = root->left->height;
					if (root->right)
						secondheight = root->right->height;
					if (abs(firstheight - secondheight) == 2) {
						if (firstheight < secondheight) {
							int rightheight1 = 0;
							int rightheight2 = 0;
							if (root->right->right)
								rightheight2 = root->right->right->height;
							if (root->right->left)
								rightheight1 = root->right->left->height;
							if (rightheight1 > rightheight2)
								root = RLR(root);
							else
								root = RRR(root);
						} else {
							int leftheight1 = 0;
							int leftheight2 = 0;
							if (root->left->right)
								leftheight2 = root->left->right->height;
							if (root->left->left)
								leftheight1 = root->left->left->height;
							if (leftheight1 > leftheight2)
								root = LLR(root);
							else
								root = LRR(root);
						}
					}
					return root;
				}

				Node *Insert(Node *root,
									Node *parent, const value_type &pair){
					if (!root) {
						root = newNode(pair);
						root->parent = parent;
					} else if (_comp(pair.first, root->pair.first)) {
						root->left = Insert(root->left, root, pair);
						int firstHeight = 0;
						int secondHeight = 0;

						if (root->left)
							firstHeight = root->left->height;
						if (root->right)
							secondHeight = root->right->height;
						if (abs(firstHeight - secondHeight) == 2) {
							if (root->left && _comp(pair.first, root->left->pair.first))
								root = LLR(root);
							else
								root = LRR(root);
						}
					} else if (_comp(root->pair.first, pair.first)) {
						root->right = Insert(root->right, root, pair);
						int firstHeight = 0;
						int secondHeight = 0;

						if (root->left)
							firstHeight = root->left->height;
						if (root->right)
							secondHeight = root->right->height;
						if (abs(firstHeight - secondHeight) == 2) {
							if (root->right && _comp(pair.first, root->right->pair.first))
								root = RLR(root);
							else
								root = RRR(root);
						}
					}
					UpdateHeight(root);
					return root;
				}

///////////////////////////************************////////////////////////////////


				Node *searchIt(Node *node, const value_type &pr) const {
					if (!node || node == _end)
						return NULL;
					if (!_comp(pr.first, node->pair.first) 
							&& !_comp(node->pair.first, pr.first))
						return node;
					if (node->left && _comp(pr.first, node->pair.first))
						return searchIt(node->left, pr);
					else if (node->right)
						return searchIt(node->right, pr);
					else
						return NULL;
				}

///////////////////////////************************////////////////////////////////

				void delEnd() {
					if (_end) {
						if (_end->parent)
							_end->parent->right = NULL;
					}
				}

				void getEnd() {
					if (!_end)
						_end = newNode();
					_end->end = true;
					_end->right = NULL;
					_end->left = NULL;
					_end->parent = maxValueNode(_root);
					if (_end->parent)
						_end->parent->right = _end;

				};

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

		public:
			typedef MapIt<value_type>					iterator;
			typedef MapIt<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
///////////////////////////************************////////////////////////////////

		private:
			Node		*_root;
			Node		*_end;
			size_type	_size;
			key_compare	_comp;
			Allocator	_alloc; // use it to construct and deallocate
			typename allocator_type::template rebind<Node>::other	_allocNode; //use it only to allocate 1 Node

///////////////////////////************************////////////////////////////////
	class value_compare
	: public std::binary_function<value_type,value_type,bool> {
		friend class map;
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
	};
///////////////////////////************************////////////////////////////////


			//////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
			///////////////////////////MEMBER-FUNCTION////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////


	public:
	// 23.3.1.1 construct/copy/destroy:
		explicit map(const Compare& comp = Compare(),
				const Allocator& alloc = Allocator()) :
				_root(NULL), _end(NULL), _size(0), _comp(comp), _alloc(alloc) {getEnd();}

///////////////////////////************************////////////////////////////////
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
				const Compare& comp = Compare(),
				const Allocator& alloc = Allocator()) :
				_root(NULL), _end(NULL), _size(0), _comp(comp), _alloc(alloc) {
			getEnd();
			for (InputIterator it = first; it != last; it++) {
				insert(ft::make_pair(it->first, it->second));
			}
		}
///////////////////////////************************////////////////////////////////

		map(const map& other) : _root(NULL), _end(NULL), _size(0), _comp(other._comp), _alloc(other._alloc) {
			getEnd();
			for (const_iterator it = other.begin(); it != other.end(); it++) {
				insert(ft::make_pair(it->first, it->second));
			}
		}
///////////////////////////************************////////////////////////////////

		~map() {
			_size = 0;
		}
///////////////////////////************************////////////////////////////////

		map &operator=(const map& other) {
			if (_size > 0)
				this->clear();
			_root = NULL;
			getEnd();
			this->insert(other.begin(), other.end());
			return *this;
		}

///////////////////////////************************////////////////////////////////
		// iterators:
		iterator begin() {
			if (_size == 0) {
				return end();
			}
			return iterator(minValueNode(_root), _end);
		}

		const_iterator begin() const {
			if (_size == 0) {
				return end();
			}
			return const_iterator(minValueNode(_root), _end);
		}

///////////////////////////************************////////////////////////////////
		iterator end() {
			return iterator(_end, _end);
		}

		const_iterator end() const {
			return const_iterator(_end, _end);
		}

///////////////////////////************************////////////////////////////////
		//reverse_iterators:
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(end());
		}
///////////////////////////************************////////////////////////////////
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(begin());
		}
///////////////////////////************************////////////////////////////////
		// capacity:
		bool empty() const {
			return _size == 0;
		}

///////////////////////////************************////////////////////////////////
		size_type size() const {
			return _size;
		}
///////////////////////////************************////////////////////////////////

		size_type max_size() const {
			return std::numeric_limits<difference_type>::max();
		}
///////////////////////////************************////////////////////////////////

		// 23.3.1.2 element access:
		allocator_type get_allocator() const {
			return _alloc;
		}
///////////////////////////************************////////////////////////////////

		T& operator[](const key_type &x) {
			return ((this->insert(ft::make_pair(x, mapped_type()))).first)->second;
		}
///////////////////////////************************////////////////////////////////

		T& at(const Key &x) {
			if (searchIt(_root, ft::make_pair(x.first, mapped_type()))) {
				return find(x)->second;
			}
			throw std::out_of_range("no element finded");
		}
///////////////////////////******INSERT*******////////////////////////////////
		// modifiers:
		ft::pair<iterator, bool> insert(const value_type &val) {
			if (!_root) {
				_root = Insert(_root, NULL, ft::make_pair(val.first, val.second));
				getEnd();
				return ft::make_pair<iterator, bool>(find(val.first), true);
			}
			Node    *tmp;

			tmp = searchIt(_root, val);

			if (tmp)
				return ft::make_pair<iterator, bool>(find(val.first), false);
			delEnd();
			_root = Insert(_root, NULL, ft::make_pair(val.first, val.second));
			getEnd();
			return ft::make_pair<iterator, bool>(find(val.first), true);
		}

		iterator insert(iterator position, const value_type& x) {
			(void)position;
			return this->insert(x).first;
		};

		template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				for (InputIterator it = first; it != last; it++) {
					value_type	val = ft::make_pair(it->first, it->second);
					this->insert(val);
				}
			};
///////////////////////////*********ERASE************////////////////////////////////
		void erase(iterator position) {
			Node	*posParent = position.base()->parent;

			--_size;

			if (!position.base()->left && !position.base()->right) {
				if (posParent) {
					if (posParent->left == position.base())
						posParent->left = NULL;
					else
						posParent->right = NULL;
				} else {
					_root = NULL;
				}
				_alloc.destroy(&(position.base()->pair));
				_allocNode.deallocate(position.base(), 1);
				if (posParent && _root)
					_root = Balance(_root);
				getEnd();
				return ;
			} else if (!position.base()->left && position.base()->right) {
				if (!posParent) {
					position.base()->right->parent = NULL;
					Node	*tmp = position.base()->right;
					_alloc.destroy(&(position.base()->pair));
					_allocNode.deallocate(position.base(), 1);
					_root = tmp;
					getEnd();
					return ;
				}
				if (posParent->left == position.base())
					posParent->left = position.base()->right;
				else
					posParent->right = position.base()->right;
				position.base()->right->parent = posParent;
				_alloc.destroy(&(position.base()->pair));
				_allocNode.deallocate(position.base(), 1);
				if (posParent && _root)
					_root = Balance(_root);
				getEnd();
				return ;
			} else if (position.base()->left && !position.base()->right) {
				if (!posParent) {
					position.base()->left->parent = NULL;
					Node	*tmp = position.base()->left;
					_alloc.destroy(&(position.base()->pair));
					_allocNode.deallocate(position.base(), 1);
					_root = tmp;
					getEnd();
					return ;
				}
				if (posParent->left == position.base())
					posParent->left = position.base()->left;
				else
					posParent->right = position.base()->left;
				position.base()->left->parent = posParent;
				_alloc.destroy(&(position.base()->pair));
				_allocNode.deallocate(position.base(), 1);
				if (posParent && _root)
					_root = Balance(_root);
				getEnd();
				return ;
			} else {
				Node	*futurRoot = minValueNode(position.base()->right);
				if (!futurRoot || futurRoot == _end)
					futurRoot = maxValueNode(position.base()->left);
				_alloc.destroy(&(position.base()->pair));
				if (futurRoot != position.base()->right) {
					futurRoot->parent->left = futurRoot->right;
					if (futurRoot->right)
						futurRoot->right->parent = futurRoot->parent;
					futurRoot->right = position.base()->right;
					futurRoot->right->parent = futurRoot;
				}
				futurRoot->parent = position.base()->parent;
				if (futurRoot->parent) {
					if (futurRoot->parent->left == position.base())
						futurRoot->parent->left = futurRoot;
					else
						futurRoot->parent->right = futurRoot;
				} else
					_root = futurRoot;
				futurRoot->left = position.base()->left;
				if (futurRoot->left)
					futurRoot->left->parent = futurRoot;
				_allocNode.deallocate(position.base(), 1);
				if (posParent && _root)
					_root = Balance(_root);
				getEnd();
				return ;
			}
		};
///////////////////////////************************////////////////////////////////

		size_type erase(const key_type& x) {
			Node	*tmp = searchIt(_root, ft::make_pair(x, mapped_type()));
			if (!tmp)
				return 0;
			else
				erase(iterator(tmp, _end));
			return 1;
		};

		void erase(iterator first, iterator last) {
			while (first != last) {
				erase(first++);
			}
		};

///////////////////////////************************////////////////////////////////
		void swap(map &other) {
			Node	*tmpRoot = other._root;
			Node	*tmpEnd = other._end;
			size_type	tmpSize = other._size;
			key_compare	tmpComp = other._comp;

			other._comp = _comp;
			other._root = _root;
			other._end = _end;
			other._size = _size;
			_comp = tmpComp;
			_root = tmpRoot;
			_end = tmpEnd;
			_size = tmpSize;
		};

///////////////////////////************************////////////////////////////////
		void clear() {
			this->erase(this->begin(), this->end());
		}

///////////////////////////************************////////////////////////////////
		// observers:
		key_compare key_comp() const {return _comp;};
///////////////////////////************************////////////////////////////////
		value_compare value_comp() const {return value_compare(_comp);};
		// 23.3.1.3 map operations:
		// */
///////////////////////////**********FIND************////////////////////////////////
		iterator find(const Key &x) {
			value_type	pr = ft::make_pair<key_type, mapped_type>(x, mapped_type());
			Node	*tmp = searchIt(_root, pr);

			if (!tmp)
				return end();
			return iterator(tmp, _end);
		};

		const_iterator find(const key_type& x) const {
			value_type	pr = ft::make_pair<key_type, mapped_type>(x, mapped_type());
			Node	*tmp = searchIt(_root, pr);

			if (!tmp)
				return end();
			return iterator(tmp, _end);
		};

///////////////////////////************************////////////////////////////////
		size_type count(const Key &x) const {
			if (searchIt(_root, ft::make_pair(x, mapped_type()))) {return 1;}
			return 0;
		};

///////////////////////////*******BOUND***********////////////////////////////////
		iterator lower_bound(const key_type& x) {
			iterator	ret = begin();
			while (ret != end() && _comp(ret->first, x))
				++ret;
			return ret;
		};

		const_iterator lower_bound(const key_type& x) const {
			const_iterator	ret = begin();
			while (ret != end() && _comp(ret->first, x))
				++ret;
			return ret;
		};

///////////////////////////************************////////////////////////////////
		iterator upper_bound(const key_type& x) {
			iterator	ret = begin();
			while (ret != end() && !_comp(x, ret->first))
				++ret;
			return ret;
		};

		const_iterator upper_bound(const key_type& x) const {
			const_iterator	ret = begin();
			while (ret != end() && !_comp(x, ret->first))
				++ret;
			return ret;
		}

///////////////////////////************************////////////////////////////////
		pair<iterator,iterator> equal_range(const key_type& x) {
			return (ft::make_pair(lower_bound(x), upper_bound(x)));
		}

		pair<const_iterator,const_iterator> equal_range(const key_type& x) const {
			return (ft::make_pair(lower_bound(x), upper_bound(x)));
		}
///////////////////////////************************////////////////////////////////
	};

///////////////////////////*******COMP-OPE********////////////////////////////////
	template<class Key, class T, class Compare, class Alloc>
		bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			if (lhs.size() != rhs.size())
				return false;
			return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator<(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end()));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator>(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return (!(lhs < rhs) && !(rhs == lhs));
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return !(lhs == rhs);
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return !(lhs > rhs);
		}

	template<class Key, class T, class Compare, class Alloc>
		bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
							const map<Key, T, Compare, Alloc> &rhs) {
			return !(lhs < rhs);
		}

	template<class Key, class T, class Compare, class Alloc>
		void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
			x.swap(y);
		}
///////////////////////////************************////////////////////////////////

}
