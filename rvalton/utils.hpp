#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft {
	template <bool cond, typename result=void>
		struct	enable_if {
		};

	template <typename result>
		struct enable_if<true, result> {
			typedef result	type;// = result;
		};

	template <typename T, T val> struct is_integral_base {
		static const T	value = val;
	};

	typedef is_integral_base<bool, true>	true_type;
	typedef is_integral_base<bool, false>	false_type;

	template <typename T> struct is_integral : public false_type {};
	template <> struct is_integral<bool> : true_type {};
	template <> struct is_integral<char> : true_type {};
	template <> struct is_integral<wchar_t> : true_type {};
	template <> struct is_integral<signed char> : true_type {};
	template <> struct is_integral<short int> : true_type {};
	template <> struct is_integral<int> : true_type {};
	template <> struct is_integral<long int> : true_type {};
	template <> struct is_integral<long long int > : true_type {};
	template <> struct is_integral<unsigned char> : true_type {};
	template <> struct is_integral<unsigned short int> : true_type {};
	template <> struct is_integral<unsigned int> : true_type {};
	template <> struct is_integral<unsigned long int> : true_type {};
	template <> struct is_integral<unsigned long long int> : true_type {};

	template <class InputIterator1, class InputIterator2>
		bool equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2) {
			while (first1 != last1) {
				if (!(*first1 == *first2))
					return false;
				++first1;
				++first2;
			}
			return true;
		};

	/*
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
		bool equal(InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred) {
			while (first1 != last1) {
				if (!pred(*first1, *first2))
					return false;
				++first1;
				++first2;
			}
			return true;
		};
	*/

	template <class InputIterator1, class InputIterator2>
		bool	lexicographical_compare(InputIterator1 first1,
										InputIterator1 last1,
										InputIterator2 first2,
										InputIterator2 last2) {
			for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
				if (*first1 < *first2)
					return true;
				if (*first2 < *first1)
					return false;
			}
			return (first1 == last1) && (first2 != last2);
		}
			/*while (first1 != last1) {
				if (first2 == last2 || *first2 < *first1)
					return false;
				else if (*first1 < *first2)
					return true;
				++first1;
				++first2;
			}
			return (first2 != last2);*/

	template <class InputIterator1, class InputIterator2, class Compare>
		bool	lexicographical_compare(InputIterator1 first1,
										InputIterator1 last1,
										InputIterator2 first2,
										InputIterator2 last2,
										Compare comp) {
			for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) {
				if (comp(*first1, *first2))
					return true;
				if (comp(*first2, *first1))
					return false;
			}
			return (first1 == last1) && (first2 != last2);
		}
	/*
			while (first1 != last1) {
				if (first2 == last2 || comp(*first2, *first1))
					return false;
				else if (comp(*first1, *first2))
					return true;
				++first1;
				++first2;
			}
			return (first2 != last2);
			*/
};

#endif
