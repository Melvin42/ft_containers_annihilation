#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft {
	template <class T>
		class	iterator {
			public:
				typedef typename iterator_traits<T*>::value_type		value_type;
				typedef typename iterator_traits<T*>::difference_type	difference_type;
				typedef typename iterator_traits<T*>::pointer			pointer;
				typedef typename iterator_traits<T*>::reference			reference;
				typedef std::random_access_iterator_tag					iterator_category;

			protected:
				pointer	_pos;

			public:

				iterator() : _pos(NULL) {}

				explicit iterator(pointer it) : _pos(it) {}

//				template <class U>
//					iterator(const iterator<U> &it) {
////							*this = it;
//						}

//				template <class U>
//					iterator	&operator=(const pointer it) {
//						_pos = it;
//						return *this;
//					}
					iterator	&operator=(const iterator &it) {
						_pos = it.base();
						return *this;
					}
			iterator(const iterator<typename std::remove_const<T>::type> &it) : _pos(it.base()) {
//					*this = it;
				}

//				template <class U>
//					iterator	&operator=(const iterator<U> &it) {
//						_pos = it.base();
//						return *this;
//					}


				~iterator() {}

				pointer	base() {
					return _pos;
				}

				const pointer	base() const {
					return _pos;
				}

				reference	operator*() { return *_pos; }
				reference	operator*() const { return *_pos; }
				pointer		operator->() { return _pos; }
				pointer		operator->() const { return _pos; }

				iterator	&operator-=(difference_type n) {
					for (int i = 0; i < n; i++)
						--_pos;
					return *this;
				}

				iterator	&operator+=(difference_type n) {
					for (int i = 0; i < n; i++)
						++_pos;
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

//				difference_type	operator+(const iterator &it) const {
//					return base() + it.base();
//				}

				iterator	operator+(difference_type v) const {
					iterator	tmp(*this);

					tmp += v;
					return tmp;
//					return iterator(_pos.base() + v);
				}

				iterator	operator-(difference_type v) const {
					iterator	tmp(*this);

					tmp -= v;
					return tmp;
//					return iterator(_pos.base() - v);
				}

//				iterator	operator-(difference_type v) const {
//					iterator	tmp(*this);

//					tmp -= v;
//					return tmp;
//					return iterator(_pos.base() - v);
//				}

				template <class Iterator>
					difference_type	operator-(const iterator<Iterator> &it) const {
						return base() - it.base();
					}

//				iterator	operator-(difference_type v) {
//					iterator	tmp(*this);

//					tmp -= v;
//					return tmp;
//				}

				reference	operator[](difference_type v) const {
					return *(_pos + v);
				}

				template <class Iterator>
					bool	operator==(const iterator<Iterator> &it) const {
						return base() == it.base();
					}

				template <class Iterator>
					bool	operator!=(const iterator<Iterator> &it) const {
						return base() != it.base();
					}

				template <class Iterator>
					bool	operator<=(const iterator<Iterator> &it) const {
						return base() <= it.base();
					}

				template <class Iterator>
					bool	operator>=(const iterator<Iterator> &it) const {
						return base() >= it.base();
					}

				template <class Iterator>
					bool	operator<(const iterator<Iterator> &it) const {
						return base() < it.base();
					}

				template <class Iterator>
					bool	operator>(const iterator<Iterator> &it) const {
						return base() > it.base();
					}
		};

	template <class Iterator>
		Iterator operator+(
				typename Iterator::difference_type v,
				const Iterator &it) {
				Iterator	tmp(it);

				tmp += v;
				return tmp;
//			return iterator<Iterator>(it.base() + v);
		}

	template <class Iterator>
		Iterator operator-(
				typename Iterator::difference_type v,
				const Iterator &it) {
				Iterator	tmp(it);

				tmp -= v;
				return tmp;
//			return iterator<Iterator>(it.base() + v);
//			return iterator<Iterator>(it.base() - v);
		}

//	template <class T>
//		typename iterator<T>::difference_type operator-(const iterator<T> &lhs, const iterator<T> &rhs) {
//			return rhs.base() - lhs.base();
//		}

//	template <class T, class U>
//		typename iterator<T>::difference_type operator+(const iterator<T> &lhs, const iterator<U> &rhs) {
//			return lhs.base() + rhs.base();
//		}

	template <class T, class U>
		typename iterator<T>::difference_type operator-(const iterator<T> &lhs, const iterator<U> &rhs) {
			return lhs.base() - rhs.base();
		}
};

#endif
