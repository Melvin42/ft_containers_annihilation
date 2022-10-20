#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {
	template <class Iterator>
			class	reverse_iterator {
				public:
					typedef Iterator												iterator_type;
					typedef typename ft::iterator_traits<Iterator>::value_type		value_type;
					typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
					typedef typename ft::iterator_traits<Iterator>::pointer			pointer;
					typedef typename ft::iterator_traits<Iterator>::reference		reference;

				protected:
					iterator_type	_pos;

				public:

					reverse_iterator() : _pos() {}

					explicit reverse_iterator(iterator_type it) : _pos(it) {}

					template <class U>
						reverse_iterator(const reverse_iterator<U> &it) : _pos(it.base()) {}

//					virtual ~reverse_iterator() {}

//					iterator_type	base() {
//						return _pos;
//					}

					iterator_type	base() const {
						return _pos;
					}

					reference	operator*() const {
						iterator_type	tmp = _pos;

						return *--tmp;
					}

					pointer		operator->() const { return &(operator*()); }

					reverse_iterator	operator-=(difference_type n) {
						_pos += n;
						return *this;
					}

					reverse_iterator	operator+=(difference_type n) {
						_pos -= n;
						return *this;
					}

					reverse_iterator	operator++(int) {
						reverse_iterator	tmp(*this);

						--_pos;
						return tmp;
					}

					reverse_iterator	&operator++() {
						--_pos;
						return *this;
					}

					reverse_iterator	operator--(int) {
						reverse_iterator	tmp = *this;

						++_pos;
						return tmp;
					}

					reverse_iterator	&operator--() {
						++_pos;
						return *this;
					}

					reverse_iterator	operator+(difference_type v) const {
						reverse_iterator	tmp(*this);

						tmp -= v;
						return tmp;
					}

					reverse_iterator	operator-(difference_type v) const {
						reverse_iterator	tmp(*this);

						tmp += v;
						return tmp;
					}

					difference_type	operator-(const reverse_iterator<Iterator> &it) {
						return it.base() - base();
					}


					reference	operator[](difference_type v) const {
						return _pos[-v - 1];
//						return *(_pos + v);
					}

					template <class T>
						bool	operator==(const reverse_iterator<T> &it) const {
						return base() == it.base();
					}

					template <class T>
						bool	operator!=(const reverse_iterator<T> &it) const {
							return base() != it.base();
						}

					template <class T>
						bool	operator<=(const reverse_iterator<T> &it) const {
							return base() <= it.base();
						}

					template <class T>
						bool	operator>=(const reverse_iterator<T> &it) const {
							return base() >= it.base();
						}

					template <class T>
						bool	operator<(const reverse_iterator<T> &it) const {
							return base() < it.base();
						}

					template <class T>
						bool	operator>(const reverse_iterator<T> &it) const {
							return base() > it.base();
						}

			};

	template <class Iterator>
		reverse_iterator<Iterator> operator+(
				typename reverse_iterator<Iterator>::difference_type v,
				reverse_iterator<Iterator> &it) {
			return reverse_iterator<Iterator>(it.base() + v);
		}

	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type	operator-(
				const reverse_iterator<Iterator> &lhs,
				const reverse_iterator<Iterator> &rhs) {
			return rhs.base() - lhs.base();
		}

};

#endif
