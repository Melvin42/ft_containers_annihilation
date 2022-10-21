#ifndef VECITERATOR_HPP
#define VECITERATOR_HPP

# include <memory>
# include "utils.hpp"
# include "iterator_traits.hpp"

namespace ft {
	template<class T>
	class VecIterator {
		public:
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef std::random_access_iterator_tag						iterator_category;

		private:
			pointer	p;

		public:
			VecIterator() : p(0) {};
			explicit VecIterator(pointer x) : p(x) {};
			~VecIterator() {};

			VecIterator &operator=(const pointer it) {p = it; return *this;};
			VecIterator &operator=(const VecIterator &mit) {
				p = mit.base();
				return *this;
			};
			VecIterator(const VecIterator<typename std::remove_const<T>::type> &mit) : p(mit.base()) {};
//			VecIterator(const VecIterator<const value_type> &mit) {*this = mit.base();};

			reference operator*() {return *p;};
			reference operator*() const {return *p;};
			pointer operator->() {return p;};
			pointer operator->() const {return p;};
			pointer base() {return p;};
			pointer base() const {return p;};


			VecIterator &operator++() {++p; return *this;};
			VecIterator &operator--() {--p; return *this;};
			VecIterator operator++(int) {VecIterator tmp(*this); ++p; return tmp;};
			VecIterator operator--(int) {VecIterator tmp(*this); --p; return tmp;};

			VecIterator &operator+=(difference_type n) {
				for (int i = 0; i < n; i++) {
					++p;
				}
				return *this;
			};
			VecIterator &operator-=(difference_type n) {
				for (int i = 0; i < n; i++) {
					--p;
				}
				return *this;
			};

			reference operator[](difference_type n) {return *(p + n);};
			reference operator[](difference_type n) const {return *(p + n);};

			VecIterator operator+(difference_type n) const {VecIterator r(*this); r+=n; return r;};
			VecIterator operator-(difference_type n) const {VecIterator r(*this); r-=n; return r;};

			template <class Iterator>
			difference_type operator-(const VecIterator<Iterator> &second) const {
				return (base() - second.base());
			};

			template <class Iterator>
				bool operator==(const VecIterator<Iterator> &other) const {return base() == other.base();};

			template <class Iterator>
				bool operator<(const VecIterator<Iterator> &other) const {return base() < other.base();};

			template <class Iterator>
				bool operator!=(const VecIterator<Iterator> &other) const {return base() != other.base();};

			template<class Iterator>
				bool operator>(const VecIterator<Iterator> &other) const {return base() > other.base();};

			template<class Iterator>
				bool operator<=(const VecIterator<Iterator> &other) const {return base() <= other.base();};

			template<class Iterator>
				bool operator>=(const VecIterator<Iterator> &other) const {return base() >= other.base();};

	};

	template<class Iterator>
		Iterator operator+(const typename Iterator::difference_type &n, const Iterator &it) {
			Iterator r(it);
			r+=n;
			return r;
		};

	template<class Iterator>
		Iterator operator-(const typename Iterator::difference_type &n, const Iterator &it) {
			Iterator r(it);
			r-=n;
			return r;
		};

}
#endif
