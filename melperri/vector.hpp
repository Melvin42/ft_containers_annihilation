#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <limits>
#include <cstddef>
#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"
#include "iterator_traits.hpp"

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
		class vector {
			public:
				/* TYPES */

				typedef T													value_type;
				typedef Alloc												allocator_type;
				typedef typename allocator_type::reference					reference;
				typedef typename allocator_type::const_reference			const_reference;
				typedef typename allocator_type::pointer					pointer;
				typedef typename allocator_type::const_pointer				const_pointer;
				typedef ft::iterator<value_type>								iterator;
				typedef ft::iterator<const value_type>						const_iterator;
				typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
				typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;
				typedef typename iterator_traits<iterator>::difference_type	difference_type;
				typedef std::size_t											size_type;

			private:
				Alloc		_alloc;
				pointer		_p;
				pointer		_p_end;
				size_type	_capacity;

			public:
				/* CONSTRUCT/COPY/DESTROY */

				vector	&operator=(const vector<T, Alloc> &vector) {
					if (this != &vector) {
						if (_p)
							_alloc.deallocate(_p, _p_end - _p);
						_alloc = vector.get_allocator();//_alloc;
						_capacity = vector._capacity;
						_p = _alloc.allocate(_capacity);
						size_t	i = 0;

						_p_end = _p;
						for (const_iterator it = vector.begin(); it != vector.end(); it++, i++) {
							_alloc.construct(_p + i, *it);
							++_p_end;
						}
					}
					return *this;
				}

				//default (1)
				explicit vector(const allocator_type &alloc = allocator_type())
					: _alloc(alloc), _p(NULL), _p_end(NULL), _capacity(0) {};

				//fill (2)
				explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
					: _alloc(alloc), _p(NULL), _p_end(NULL), _capacity(n) {
						_p = _alloc.allocate(_capacity);
						_p_end = _p;
						for (size_t i = 0; i < n; i++) {
							_alloc.construct(_p + i, val);
							++_p_end;
						}
				}

				//range (3)
				template <class InputIterator>
					vector(InputIterator first, InputIterator last,
							const allocator_type &alloc = allocator_type(),
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
							: _alloc(alloc), _p(NULL), _p_end(NULL), _capacity(0) {
						int	n = 0;

						for (InputIterator it = first; it != last; ++it, ++n);

						if (n > 0) {
							_capacity = n;
							_p = _alloc.allocate(_capacity);
							_p_end = _p;
							for (size_t i = 0; first != last; i++) {
								_alloc.construct(_p + i, *first);
								++first;
								++_p_end;
							}
						}
//						else
//							throw std::length_error("cannot create std::vector larger than max_size()");
					}

				//copy (4)
//				IteratorMap(const IteratorMap<typename std::remove_const<U>::type> &it)
//				vector(const vector<typename std::remove_const<T>::type, Alloc> &vector) {
				vector(const vector<T, Alloc> &vector) {
					*this = vector;
				}

				~vector() {
					if (_capacity > 0)
						_alloc.deallocate(_p, _capacity);
				}

				template <class InputIterator>
					void	assign(InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
						int	n = 0;

						for (InputIterator it = first; it != last; ++it, ++n);
						if (n > 0) {
							_capacity = n;
							_p = _alloc.allocate(_capacity);
							_p_end = _p;
							for (size_t i = 0; first != last; i++) {
								_alloc.construct(_p + i, *first);
								++first;
								++_p_end;
							}
						}
					}

				void			assign(size_type n, const T& u) {
					reserve(n);
					for (size_t i = 0; i < n; i++) {
						_alloc.construct(_p + i, u);
						if (size() <= i)
							++_p_end;
					}
					for (size_t i = size(); i > n; i--) {
						--_p_end;
					}
				}

				allocator_type	get_allocator() const {
					return _alloc;
				}

				/* ITERATORS */
				iterator				begin() {
					return iterator(_p);
				}

				const_iterator			begin() const {
					return const_iterator(_p);
				}

				iterator				end() {
					return iterator(_p_end);
				}

				const_iterator			end() const {
					return const_iterator(_p_end);
				}

				reverse_iterator		rbegin() {
					return reverse_iterator(end());
				}

				const_reverse_iterator	rbegin() const {
					return const_reverse_iterator(end());
				}

				reverse_iterator		rend() {
					return reverse_iterator(begin());
				}

				const_reverse_iterator	rend() const {
					return const_reverse_iterator(begin());
				}

				/* CAPACITY */
				size_type	size() const { return _p_end - _p; }

				size_type	capacity() const { return _capacity; }

				size_type	max_size() const {
//					return std::numeric_limits<size_type>::max() / sizeof(difference_type); }
					return _alloc.max_size(); }

				bool		empty() const { return (size() == 0); }

				void		resize(size_type sz, value_type val = value_type()) {
					size_t	i = 0;

					if (sz < size()) {
						_p_end = _p;
						for (i = 0; i < sz; i++) { ++_p_end; }
					} else {
						size_t	tmp = size();

						for (i = 0; i < sz; i++) {
							if (i >= tmp)
								push_back(val);
						}
					}
				}

				void		reserve(size_type n) {
					size_t		size_tmp = size();
					value_type	tmp[size_tmp];

					for (size_t i = 0; i < size(); i++) {
						tmp[i] = *(_p + i);
					}
					if (_capacity > 0)
						_alloc.deallocate(_p, _capacity);
					if (_capacity <= n)
						_capacity = n;
					else
						_capacity += n;
					_p = _alloc.allocate(_capacity);
					_p_end = _p;
					for (size_t i = 0; i < size_tmp; i++) {
						_alloc.construct(_p + i, tmp[i]);
						++_p_end;
					}
				}

				/* ELEMENT ACCES */

				reference		operator[](size_type n) {
//					if (n >= size())
//						throw std::out_of_range("");
					return *(_p + n);
				}

				const_reference	operator[](size_type n) const {
//					if (n >= size())
//						throw std::out_of_range("");
					return *(_p + n);
				}

				reference		at(size_type n) {
					if (n >= size() || size() == 0)
						throw std::out_of_range("");
					return *(_p + n);
				}

				const_reference	at(size_type n) const {
					if (n >= size() || size() == 0)
						throw std::out_of_range("");
					return *(_p + n);
				}

				reference		front() { return *_p; }
				const_reference	front() const { return *_p; }
				reference		back() {
//					std::cout << *(_p_end - 1) << '\n';
					return *(_p_end - 1);
				}
				const_reference	back() const {
//					std::cout << *(_p_end - 1) << '\n';
					return *(_p_end - 1);
				}

				/* MODIFIERS */

				void	push_back(const value_type& val) {
					if (size() + 1 > _capacity)
						reserve(_capacity + 1);
					_alloc.construct(_p + size(), val);
					++_p_end;
				}

				void	pop_back() {
					if (_p + size()) {
						_alloc.destroy(_p + size());
						_p_end--;
					}
				}

				//INSERT

				//single element (1)
				iterator	insert(iterator pos, const value_type& val) {
					insert(pos, 1, val);
					return pos;
				}

				//fill (2)
				void	insert(iterator pos, size_type n,
								const value_type& val) {
					size_t		count = 0;
					size_t		i = 0;
					size_t		j = 0;
					value_type	tmp[size()];
					iterator	it = begin();
					size_t		size_tmp = size();

					for (i = 0; it != end(); it++, i++) {
						tmp[i] = *it;
					}
					it = begin();
					if (pos < it)
						return ;
					for (iterator it = begin(); it != pos; it++, count++) ;

					if (n + size() > _capacity)
						reserve(n + size());

					i = 0;
					while (i < size()) {
						_alloc.destroy(_p + i);
						i++;
					}
					i = 0;
					if (!count) {
						while (i < n) {
							_alloc.construct(_p + i, val);
							++i;
							++_p_end;
						}
					}
					while (j < count) {
						_alloc.construct(_p + j, tmp[j]);
						++j;
					}
					while (i < n) {
						_alloc.construct(_p + count + i, val);
						++_p_end;
						++i;
					}
					while (j < size_tmp) {
						_alloc.construct(_p + j + i, tmp[j]);
						++j;
					}
				}

				//range (3)
				template <class InputIterator>
					void	insert(iterator pos,
							InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
						size_t		i = 0;
						size_t		j = 0;
						size_t		count = 0;
						size_t		n = 0;
						value_type	tmp[size()];
						iterator	it = begin();
						size_t		size_tmp = size();

						for (i = 0; it != end(); it++, i++) {
							tmp[i] = *it;
						}
						it = begin();
						if (pos < it)
							return ;
						for (iterator it = begin(); it != pos; it++, count++) ;

						i = 0;
						for (InputIterator it = first; it != last; ++it, ++n);

//						if (last - first > 0)
//							n = last - first;
						if (n + size() > _capacity)
							reserve(n + size());

						if (!count) {
							while (i < n) {
								_alloc.construct(_p + i, *first);
								++i;
								++_p_end;
								++first;
							}
						}
						while (j < count) {
							_alloc.construct(_p + j, tmp[j]);
							++j;
						}
						while (i < n) {
							_alloc.construct(_p + count + i, *first);
							++_p_end;
							++i;
							++first;
						}
						while (j < size_tmp) {
							_alloc.construct(_p + j + i, tmp[j]);
							++j;
						}
					}

				iterator	erase(iterator pos) {
					value_type	tmp[size() - 1];
					iterator	it = begin();
					size_t		i = 0;
					size_t		len = size();
					size_t		ret;

					while (it != pos) {
						tmp[i] = *it;
						++it;
						++i;
					}
					ret = i;
					while (++it != end()) {
						tmp[i] = *it;
						++i;
					}
					i = 0;
					for (i = 0; i < size(); i++) {
						_alloc.destroy(_p + i);
					}
					_p_end = _p;
					for (i = 0; i + 1 < len; i++) {
						_alloc.construct(_p + i, tmp[i]);
						++_p_end;
					}
					return iterator(_p + ret);
//					return _p + ret;
				}

				iterator	erase(iterator first, iterator last) {
					size_t	i = 0;
					size_t	n = 0;
					size_t	len = size();
					size_t	ret = 0;

//					if (last - first > 0)
//						n = last - first;
					for (iterator it = first; it != last; ++it, ++n);
					if (n > len)
						n = len;
					if (len - n <= 0)
						len = 0;
					else
						len -= n;

					value_type	tmp[len + 1];

					if (len > 0) {
						iterator	it = begin();

						while (it != first && i < len) {
							tmp[i] = *it;
							++it;
							++i;
						}
						ret = i;
						while (it != last) {
							++it;
						}
						while (it != end() && i < len) {
							tmp[i] = *it;
							++it;
							++i;
						}
					}
					for (i = 0; i < size(); i++) {
						_alloc.destroy(_p + i);
					}
					_p_end = _p;
					for (i = 0; i < len; i++) {
						_alloc.construct(_p + i, tmp[i]);
						++_p_end;
					}
					return iterator(_p + ret);
				}

				void	swap(vector<T, Alloc> &x) {
					pointer		p_tmp;
					value_type	cap_tmp;

					p_tmp = _p;
					_p = x._p;
					x._p = p_tmp;

					p_tmp = _p_end;
					_p_end = x._p_end;
					x._p_end = p_tmp;

					cap_tmp = _capacity;
					_capacity = x._capacity;
					x._capacity = cap_tmp;
				}

				void	clear() {
					size_t	len = size();

					for (size_t i = 0; i < len; i++) {
						_alloc.destroy(_p + i);
					}
					_p_end = _p;
				}

//				friend typename iterator::difference_type operator-(const_iterator &lhs, const_iterator &rhs) {;;;
//					return lhs - rhs;
//				}
		};

	template<class T, class Alloc>
		bool	operator==(const vector<T, Alloc> &lhs,
							const vector<T, Alloc> &rhs)
		{
			if (lhs.size() == rhs.size()) {
				for (size_t i = 0; i < lhs.size(); i++) {
					if (lhs[i] != rhs[i])
						return false;
				}
				return true;
			}
			return false;
		}

	template<class T, class Alloc>
		bool	operator!=(const vector<T, Alloc> &lhs,
							const vector<T, Alloc> &rhs) {
			return (!(lhs == rhs));
		}

	template<class T, class Alloc>
		bool	operator<(const vector<T, Alloc> &lhs,
							const vector<T, Alloc> &rhs) {
			size_t i;

			for (i = 0; i < lhs.size() && i < rhs.size(); i++) {
				if (lhs[i] < rhs[i])
					return true;
				else if (lhs[i] > rhs[i])
					return false;
			}
			if (i == lhs.size() && i < rhs.size())
				return true;
			else
				return false;
		}

	template<class T, class Alloc>
		bool	operator<=(const vector<T, Alloc> &lhs,
							const vector<T, Alloc> &rhs) {
			return (!(rhs < lhs));
		}

	template<class T, class Alloc>
		bool	operator>(const vector<T, Alloc> &lhs,
							const vector<T, Alloc> &rhs) {
			return (rhs < lhs);
		}

	template<class T, class Alloc>
		bool	operator>=(const vector<T, Alloc> &lhs,
							const vector<T, Alloc> &rhs) {
			return (!(lhs < rhs));
		}

	template<class T, class Alloc>
		void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {
			x.swap(y);
		}

};

#endif
