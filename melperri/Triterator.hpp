#ifndef TRITERATOR_HPP
#define TRITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template <	class Category,
				class T,
				class Distance = typename iterator_traits<T*>::difference_type,
				class Pointer = typename iterator_traits<T*>::pointer,
				class Reference = typename iterator_traits<T*>::reference >
		class Triterator {
			public:
				typedef typename iterator_traits<T*>::value_type value_type;
				typedef Pointer		pointer;
				typedef Reference	reference;
				typedef Distance	difference_type;
				typedef Category	iterator_category;

			protected:
				node	_pos;

			public:

				iterator() : _pos(NULL) {}

				iterator(pointer it) : _pos(it) {}

				template <class U>
					iterator(const iterator<Category, U> &it) {
						*this = it;
					}

				template <class U>
					iterator	&operator=(const iterator<Category, U> &it) {
						_pos = it.base();
						return *this;
					}

				~iterator() {}

				pointer	base() {
					return _pos;
				}

				const pointer	base() const {
					return _pos;
				}

				reference	operator*() const { return *_pos; }
				pointer		operator->() const { return _pos; }

				iterator	operator-=(int n) {
					for (int i = 0; i < n; i++, _pos--) ;
					return *this;
				}

				iterator	operator+=(int n) {
					for (int i = 0; i < n; i++, _pos++) ;
					return *this;
				}

				iterator	operator++(int) {
					iterator	tmp(*this);

					++(*this);
					return tmp;
				}

				iterator	&operator++() {
					++_pos;
					return *this;
				}

				iterator	operator--(int) {
					iterator	tmp = *this;

					--(*this);
					return tmp;
				}

				iterator	&operator--() {
					--_pos;
					return *this;
				}

				difference_type	operator+(const iterator &it) const {
					return base() + it.base();
				}

				iterator	operator+(difference_type v) const {
					return iterator(_pos + v);
				}

				iterator	operator+(int n) {
					return iterator(base() + n);
				}

//				difference_type	operator-(const iterator &it) const {
//					return base() - it.base();
//				}

//				iterator	operator-(difference_type v) const {
//					return iterator(_pos - v);
//				}

				iterator	operator-(int n) {
					return iterator(_pos - n);
				}

				reference	operator[](difference_type v) const {
					return *(_pos + v);
				}

				template <class Iterator>
					friend bool	operator==(const Iterator &lhs, const Iterator &rhs);
				template <class Iterator>
					friend bool	operator!=(const Iterator &lhs, const Iterator &rhs);
				template <class Iterator>
					friend bool	operator<=(const Iterator &lhs, const Iterator &rhs);
				template <class Iterator>
					friend bool	operator>=(const Iterator &lhs, const Iterator &rhs);
				template <class Iterator>
					friend bool	operator<(const Iterator &lhs, const Iterator &rhs);
				template <class Iterator>
					friend bool	operator>(const Iterator &lhs, const Iterator &rhs);
		};

	template <class Iterator>
		bool	operator==(const Iterator &lhs, const Iterator &rhs) {
			return lhs._pos == rhs._pos;
		}

	template <class Iterator>
		bool	operator!=(const Iterator &lhs, const Iterator &rhs) {
			return lhs._pos != rhs._pos;
		}

	template <class Iterator>
		bool	operator<=(const Iterator &lhs, const Iterator &rhs) {
			return lhs._pos <= rhs._pos;
		}

	template <class Iterator>
		bool	operator>=(const Iterator &lhs, const Iterator &rhs) {
			return lhs._pos >= rhs._pos;
		}

	template <class Iterator>
		bool	operator<(const Iterator &lhs, const Iterator &rhs) {
			return lhs._pos < rhs._pos;
		}

	template <class Iterator>
		bool	operator>(const Iterator &lhs, const Iterator &rhs) {
			return lhs._pos > rhs._pos;
		}
	/*
	template <class Category, class T>
		bool	operator==(const iterator &lhs, const iterator &rhs) {
			return lhs._pos == rhs._pos;
		}

	template <class Category, class T>
		bool	operator!=(const iterator &lhs, const iterator &rhs) {
			return lhs._pos != rhs._pos;
		}

	template <class Category, class T>
		bool	operator<=(const iterator &lhs, const iterator &rhs) {
			return lhs._pos <= rhs._pos;
		}

	template <class Category, class T>
		bool	operator>=(const iterator &lhs, const iterator &rhs) {
			return lhs._pos <= rhs._pos;
		}

	template <class Category, class T>
		bool	operator<(const iterator &lhs, const iterator &rhs) {
			return lhs._pos < rhs._pos;
		}


	template <class Category, class T>
		bool	operator>(const iterator &lhs, const iterator &rhs) {
			return lhs._pos > rhs._pos;
		}

		};
		*/

//	template <class Category, class T>
//		iterator<Category, T> operator-(iterator<Category, T> &lhs, iterator<Category, T> &rhs) {
//			std::cout << "coucou\n";	
//			return iterator<Category, T>(lhs.base() - rhs.base());
//		}

	template <class Category, class T>
		iterator<Category, T> operator+(std::ptrdiff_t v, iterator<Category, T> &it) {
			return iterator<Category, T>(it.base() + v);
		}

//	template <class Category, class T>
//		iterator<Category, T> operator-(std::ptrdiff_t v, iterator<Category, T> &it) {
//			return iterator<Category, T>(it.base() - v);
//		}

	template <class Category, class T>
		typename iterator<Category, T>::difference_type operator+(const iterator<Category, T> &lhs, const iterator<Category, T> &rhs) {
			return lhs.base() + rhs.base();
		}

	template <class Category, class T>
		typename iterator<Category, T>::difference_type operator-(const iterator<Category, T> &lhs, const iterator<Category, T> &rhs) {
			return lhs.base() - rhs.base();
		}

	template <class Category, class T, class U>
		typename iterator<Category, T>::difference_type operator+(const iterator<Category, T> &lhs, const iterator<Category, U> &rhs) {
			return lhs.base() + rhs.base();
		}

	template <class Category, class T, class U>
		typename iterator<Category, T>::difference_type operator-(const iterator<Category, T> &lhs, const iterator<Category, U> &rhs) {
			return lhs.base() - rhs.base();
		}

//	template <class Category, class T>
//		std::ostream	&operator<<(std::ostream &os, const iterator<Category, T> &it) {
//			std::cout << "coucou\n";	
//			std::cout << it.base();
//
//			return os;
//		}
};

#endif
