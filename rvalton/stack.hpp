#include <deque>

namespace ft {
	template <class T, class Container = std::deque<T> >
		class stack {
			public:
				typedef T								value_type;
				typedef Container						container_type;
				typedef typename Container::size_type	size_type;
			
			protected:
				Container	c;

			public:
				explicit stack(const container_type &ctnr = container_type()) : c(ctnr) {}
				bool empty() const {return c.empty();}
				size_type size() {return c.size();}
				value_type &top() {return c.back();}
				const value_type &top() const {return c.back();}
				void push(const value_type &x) {c.push_back(x);}
				void pop() {c.pop_back();}
				template <class U, class C>
					friend bool operator==(const stack<U, C> &x,
									const stack<U, C> &y);
				template <class U, class C>
					friend bool operator<(const stack<U, C> &x,
									const stack<U, C> &y);
				template <class U, class C>
					friend bool operator!=(const stack<U, C> &x,
											const stack<U, C> &y);
				template <class U, class C>
					friend bool operator>(const stack<U, C> &x,
											const stack<U, C> &y);
				template <class U, class C>
					friend bool operator>=(const stack<U, C> &x,
											const stack<U, C> &y);
				template <class U, class C>
					friend bool operator<=(const stack<U, C> &x,
											const stack<U, C> &y);
		};

	template <class T, class Container>
		bool operator==(const stack<T, Container> &x,
						const stack<T, Container> &y) {
			return x.c == y.c;
		}

	template <class T, class Container>
		bool operator<(const stack<T, Container> &x,
						const stack<T, Container> &y) {
			return x.c < y.c;
		}

	template <class T, class Container>
		bool operator!=(const stack<T, Container> &x,
						const stack<T, Container> &y) {
			return x.c != y.c;
		}

	template <class T, class Container>
		bool operator>(const stack<T, Container> &x,
						const stack<T, Container> &y) {
			return x.c > y.c;
		}

	template <class T, class Container>
		bool operator>=(const stack<T, Container> &x,
						const stack<T, Container> &y) {
			return x.c >= y.c;
		}

	template <class T, class Container>
		bool operator<=(const stack<T, Container> &x,
						const stack<T, Container> &y) {
			return x.c <= y.c;
		}

}
