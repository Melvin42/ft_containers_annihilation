#ifndef VECTOR_HPP
#define VECTOR_HPP

# include <memory>
# include <iostream>
# include "VecIterator.hpp"
# include "reverse_iterator.hpp"

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef value_type									&reference;
			typedef const value_type							&const_reference;
			typedef std::size_t									size_type;
			typedef std::ptrdiff_t								difference_type;
			typedef VecIterator<T>								iterator;
			typedef VecIterator<const T>								const_iterator;
			typedef value_type									*pointer;
			typedef const value_type							*const_pointer;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		protected:
			Allocator	the_allocator;

		private:
			iterator	current_end;
			iterator	buffer_start;
			iterator	end_of_buffer;


		public:

			//
			//construct/copy/destroy
			//
			//
			explicit vector(const allocator_type &alloc = allocator_type()) : current_end(NULL) {
				buffer_start = current_end;
				end_of_buffer = current_end;
				the_allocator = alloc;
			}
			//
			explicit vector(size_type n, const value_type &val = value_type(),
					const allocator_type &alloc = allocator_type()) {
				the_allocator = alloc;
				assign(n, val);
			};
			//
			template<class InputIterator>
				vector(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type()) : current_end(NULL) {
				the_allocator = alloc;
				assign(first, last);
			};
			//
			vector(const vector<T, Allocator> &other) {
				*this = other;
			};
			//
			~vector() {
				for (iterator it = buffer_start; it != current_end; it++) {
					the_allocator.destroy(it.base());
				}
				the_allocator.deallocate(buffer_start.base(), capacity());
			};
			//
			vector &operator=(const vector<T, Allocator> &other) {
				the_allocator = other.get_allocator();
				assign(other.begin(), other.end());
				return *this;
			};
			//
			void assign(size_type n, const value_type &value) {
				reserve(size() + n);
				for (iterator it = buffer_start; it != current_end; ++it) {
					it->~value_type();
				}
				current_end = buffer_start;
				for (size_type i = 0; i < n; i++) {
					the_allocator.construct(current_end.base(), value);
					current_end++;
				}
			};
			//
			template<class InputIt>
				void assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0) {
					size_type	n = 0;
					for (InputIt it = first; it != last; ++it) {++n;}
					reserve(n);
					for (iterator it = buffer_start; it != current_end; it++) {
						it->~value_type();
					}
					current_end = buffer_start;
					for (InputIt it = first; it != last; it++) {
						the_allocator.construct(current_end.base(), *it);
						current_end++;
					}
				};
			//
			allocator_type get_allocator() const {return the_allocator;};
			//
			//iterators//
			//
			
			iterator				begin() {return buffer_start;};
			const_iterator			begin() const {return buffer_start;};
			iterator				end() {return current_end;};
			const_iterator			end() const {return current_end;};

			reverse_iterator		rbegin() {return reverse_iterator(end());};
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());};
			reverse_iterator		rend() {return reverse_iterator(begin());};
			const_reverse_iterator	rend() const {return const_reverse_iterator(begin());};

			//
			//capacity//
			//
			
			size_type	size() const {return current_end - buffer_start;};
			//
			size_type	max_size() const {return the_allocator.max_size();};
			//
			void		resize(size_type sz, T c = T()) {
				if (sz <= size()) {
					for (size_type i = size(); i > sz; --i) {
						--current_end;
						current_end->~value_type();
					}
				} else {
					if (sz > capacity()) {
						reserve(sz);
					}
					for (iterator last = buffer_start + sz; current_end != last; ++current_end) {
						the_allocator.construct(current_end.base(), c);
					}
				}
			};
			//
			size_type capacity() const {return end_of_buffer - buffer_start;}
			//
			bool empty() const {return current_end == buffer_start;}
			//
			void reserve(size_type new_cap) {
				if (new_cap > capacity()) {
					vector<T, Allocator>	p(*this);
					size_type	new_capacity = (capacity() + 1) * 2 + new_cap;
					this->~vector();
					buffer_start = the_allocator.allocate(new_capacity);
					end_of_buffer = buffer_start + new_capacity;
					current_end = buffer_start;
					for (iterator it = p.begin(); it != p.end(); ++it) {
						the_allocator.construct(current_end.base(), *it);
						++current_end;
					}
				}
			};

			//
			//element acces//
			//
			
			reference operator[] (size_type pos) {
				return *(buffer_start + pos);
			};
			//
			const_reference operator[] (size_type pos) const {
				return *(buffer_start + pos);
			};
			//
			reference at(size_type pos) {
				if ((buffer_start + pos).base() - current_end.base() >= 0) {
					throw std::out_of_range("out of range");
				}
				return *(buffer_start + pos);
			};
			//
			const_reference at(size_type pos) const {
				if ((buffer_start + pos).base() - current_end.base() >= 0) {
					throw std::out_of_range("out of range");
				}
				return *(buffer_start + pos);;
			};
			//
			reference	front() {
				return *(buffer_start);
			};
			//
			const_reference	front() const {
				return *(buffer_start);
			};
			//
			reference	back() {
				iterator	tmp = current_end;
				--tmp;
				return *tmp;
			};
			//
			const_reference	back() const {
				iterator	tmp = current_end;
				--tmp;
				return *tmp;
			};

			//
			//element acces//
			//
			
			void	push_back(const T &x) {
				reserve(size() + 1);
				*current_end = x;
				++current_end;
			};
			//
			void	pop_back() {
				--current_end;
				current_end->~value_type();
			};
			//
			iterator	insert(iterator position, const T &x) {
				size_type	pos = position - buffer_start;
				vector<T, Allocator>	p(*this);
				reserve(size() + 1);
				++current_end;
				iterator	tmp = buffer_start + pos;
				tmp->~value_type();
				the_allocator.construct(tmp.base(), x);
				iterator	tpmp = p.buffer_start + pos;
				for (iterator it = ++tmp; it != current_end; ++it) {
					*it = *tpmp;
					++tpmp;
				}
				return buffer_start + pos;
			};
			//
			iterator	insert(iterator position, size_type count, const T &x) {
				vector<T, Allocator>	p(*this);
				size_type	pos = position - buffer_start;
				reserve(size() + count);
				current_end += count;
				iterator	tmp = buffer_start + pos;
				for (size_type i = 0; i < count; ++i) {
					tmp->~value_type();
					the_allocator.construct(tmp.base(), x);
					++tmp;
				}
				iterator	tpmp = p.buffer_start + pos;
				for (iterator it = tmp; it != current_end; ++it) {
					*it = *tpmp;
					++tpmp;
				}
				return buffer_start + pos;
			};
			//
			template<class InputIt>
				void	insert(iterator position, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = 0) {
					size_type	n = 0;

					for (InputIt it = first; it != last; ++it) {++n;}

					vector<T, Allocator>	p(*this);
					size_type	pos = position - buffer_start;

					reserve(size() + n);
					current_end += n;

					iterator	tmp = buffer_start + pos;
					while (tmp != end_of_buffer && first != last) {
//						if (tmp.base())
//							tmp->~value_type();
						the_allocator.construct(tmp.base(), *first);
						++tmp;
						++first;
					}
					iterator	tpmp = p.buffer_start + pos;
					while (tmp != end_of_buffer && tpmp != p.current_end) {
						*tmp = *tpmp;
						++tmp;
						++tpmp;
					}
				};
			//
			iterator	erase(iterator position) {
				position->~value_type();
				--current_end;
				for (iterator it = position; it != current_end; ++it) {
					*it = *(it + 1);
				}
				return position;
			};
			//
			iterator	erase(iterator first, iterator last) {
				if (first == last)
					return last;
				vector<T, Allocator>	p(*this);
				size_type	st_f = last - buffer_start;

				for (iterator it = first; it != last; ++it) {
					it->~value_type();
					--current_end;
				}

				iterator	tpmp = p.buffer_start + st_f;
				for (iterator it = first; tpmp != p.current_end; ++it) {
					*it = *tpmp;
					++tpmp;
				}

				return first;
			};
			//
			void	swap(vector<T, Allocator> &other) {
				iterator	old_begin = buffer_start;
				iterator	old_end = current_end;
				iterator	old_end_of_buf = end_of_buffer;

				buffer_start = other.buffer_start;
				current_end = other.current_end;
				end_of_buffer = other.end_of_buffer;
				other.buffer_start = old_begin;
				other.current_end = old_end;
				other.end_of_buffer = old_end_of_buf;
			};
			//
			void	clear() {
				while (current_end != buffer_start) {
					--current_end;
					current_end->~value_type();
				}
			};
	};

	//
	//non-member operator
	//

	template <class T, class Allocator>
		bool	operator==(const vector<T, Allocator> &lhs,
					const vector<T, Allocator> &rhs) {
			if (lhs.size() == rhs.size()) {
				for (size_t i = 0; i < lhs.size(); ++i) {
					if (lhs[i] != rhs[i])
						return false;
				}
				return true;
			}
			return false;
		};
	//
	template <class T, class Allocator>
		bool	operator<(const vector<T, Allocator> &lhs,
					const vector<T, Allocator> &rhs) {
			size_t i;

			for (i = 0; i < lhs.size() && i < rhs.size(); ++i) {
				if (lhs[i] < rhs[i])
					return true;
				else if (lhs[i] > rhs[i])
					return false;
			}
			if (i == lhs.size() && i < rhs.size())
				return true;
			else
				return false;
		};
	//
	template <class T, class Allocator>
		bool	operator!=(const vector<T, Allocator> &x,
					const vector<T, Allocator> &y) {
			return !(x == y);
		};
	//
	template <class T, class Allocator>
		bool	operator>(const vector<T, Allocator> &x,
					const vector<T, Allocator> &y) {
			return !(x < y) && !(x == y);
		};
	//
	template <class T, class Allocator>
		bool	operator>=(const vector<T, Allocator> &x,
					const vector<T, Allocator> &y) {
			return !(x < y);
		};
	//
	template <class T, class Allocator>
		bool	operator<=(const vector<T, Allocator> &x,
					const vector<T, Allocator> &y) {
			return !(x > y);
		};
}
#endif
