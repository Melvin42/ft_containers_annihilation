#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft {
	template <class Iterator>
		class reverse_iterator {
				 protected:
					 Iterator _current;
				 public:
					 typedef Iterator													iterator_type;
//					 typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
					 typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
					 typedef typename ft::iterator_traits<Iterator>::difference_type	difference_type;
					 typedef typename ft::iterator_traits<Iterator>::reference			reference;
					 typedef typename ft::iterator_traits<Iterator>::pointer			pointer;

					 reverse_iterator() {};
					 explicit reverse_iterator(Iterator x) : _current(x) {};
					 template <class U> reverse_iterator(const reverse_iterator<U>& u) : _current(u.base()) {};
					 Iterator base() const {return _current;} // explicit
					 reference operator*() const {Iterator tmp(_current); return *--tmp;}
					 pointer operator->() const {return &(operator*());}
					 reverse_iterator& operator++() {--_current; return *this;}
					 reverse_iterator operator++(int) {reverse_iterator tmp(_current); --_current; return tmp;}
					 reverse_iterator& operator--() {++_current; return *this;}
					 reverse_iterator operator--(int) {reverse_iterator tmp(_current); ++_current; return tmp;};
					 reverse_iterator operator+(difference_type n) const {return reverse_iterator(_current - n);};
					 reverse_iterator& operator+=(difference_type n) {_current -= n; return *this;};
					 reverse_iterator operator-(difference_type n) const {return reverse_iterator(_current + n);};
					 reverse_iterator& operator-=(difference_type n) {_current += n; return *this;};
					 reference operator[](difference_type n) const {return _current[-n - 1];};

					template <class InputIterator>
						bool operator==(const reverse_iterator<InputIterator>& y) const {
							return base() == y.base();
						}
					template <class InputIterator>
						bool operator<(const reverse_iterator<InputIterator>& y) const {
							return base() > y.base();
						}
					template <class InputIterator>
						bool operator!=(const reverse_iterator<InputIterator>& y) const {
							return base() != y.base();
						}
					template <class InputIterator>
						bool operator>(const reverse_iterator<InputIterator>& y) const {
							return base() < y.base();
						}
					template <class InputIterator>
						bool operator>=(const reverse_iterator<InputIterator>& y) const {
							return base() <= y.base();
						}
					template <class InputIterator>
						bool operator<=(const reverse_iterator<InputIterator>& y) const {
							return base() >= y.base();
						}
					template <class InputIterator>
						typename reverse_iterator<InputIterator>::difference_type operator-(
								const reverse_iterator<InputIterator> &y) const {
							return y.base() - base();
						}
/*					template <class InputIterator>
						reverse_iterator<Iterator> operator+(
								typename reverse_iterator<Iterator>::difference_type n,
								const reverse_iterator<Iterator>& x) {
							return reverse_iterator<Iterator>(x.base() - n);
						}
*/		 };
	/*
	template <class Iterator>
		bool operator==(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y) {
			return x.base() == y.base();
		}
	template <class Iterator>
		bool operator<(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y) {
			return x.base() > y.base();
		}
	template <class Iterator>
		bool operator!=(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y) {
			return x.base() != y.base();
		}
	template <class Iterator>
		bool operator>(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y) {
			return x.base() < y.base();
		}
	template <class Iterator>
		bool operator>=(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y) {
			return x.base() <= y.base();
		}
	template <class Iterator>
		bool operator<=(
			const reverse_iterator<Iterator>& x,
			const reverse_iterator<Iterator>& y) {
			return x.base() >= y.base();
		}
		*/
	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator-(
				const reverse_iterator<Iterator>& x,
				const reverse_iterator<Iterator>& y) {
			return y.base() - x.base();
		}
	template <class Iterator>
		reverse_iterator<Iterator> operator+(
				typename reverse_iterator<Iterator>::difference_type n,
				const reverse_iterator<Iterator>& x) {
			return reverse_iterator<Iterator>(x.base() - n);
		}
}
#endif
