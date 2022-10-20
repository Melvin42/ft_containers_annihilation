#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
	template <class T1, class T2>
		class	pair {
			public:
				typedef T1		first_type;
				typedef T2		second_type;
				first_type		first;
				second_type		second;

				//default (1)
				pair() : first(T1()), second(T2()) {}

				//copy (2)
				template <class U, class V>
					pair(const pair<U, V> &pr)
					: first(pr.first), second(pr.second) {}

//				operator pair<const T1, const T2>() const { return pair<const T1, const T2>(first, second); }

				//initialization (3)
				pair(const first_type &a, const second_type &b)
					: first(a), second(b) {}

				~pair() {}

				pair	&operator=(const pair &pair) {
					first = pair.first;
					second = pair.second;
					return *this;
				}

				/*
				void	swap(pair &pair) noexcept ( noexcept(swap(first, pair.first))
							&& noexcept(swap(second, pair.second)) ) {
					first_type	tmp_first = first;
					first = pair.first;
					pair.first = tmp.first;

					second_type	tmp_second = second;
					second = pair.second;
					pair.second = tmp_second;
				}
				*/
				bool	operator==(const pair &pr) {
					return first == pr.first && second == pr.second;
				}

				bool	operator!=(const pair &pr) {
					return first != pr.first && second != pr.second;
				}

				bool	operator<=(const pair &pr) {
					return first <= pr.first && second <= pr.second;
				}

				bool	operator>=(const pair &pr) {
					return first >= pr.first && second >= pr.second;
				}

				bool	operator<(const pair &pr) {
					return first < pr.first && second < pr.second;
				}

				bool	operator>(const pair &pr) {
					return first > pr.first && second > pr.second;
				}
		};

		template <class T1, class T2>
			pair<T1, T2> make_pair(T1 first, T2 second) {
				return (pair<T1, T2>(first, second));
			}

	template <class T1, class T2>
		bool	operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return lhs.first == rhs.first && lhs.second == rhs.second;
		}

	template <class T1, class T2>
		bool	operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return lhs.first != rhs.first && lhs.second != rhs.second;
		}

	template <class T1, class T2>
		bool	operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return lhs.first <= rhs.first && lhs.second <= rhs.second;
		}

	template <class T1, class T2>
		bool	operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return lhs.first >= rhs.first && lhs.second >= rhs.second;
		}

	template <class T1, class T2>
		bool	operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return lhs.first < rhs.first && lhs.second < rhs.second;
		}

	template <class T1, class T2>
		bool	operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
			return lhs.first > rhs.first && lhs.second > rhs.second;
		}

};
#endif
