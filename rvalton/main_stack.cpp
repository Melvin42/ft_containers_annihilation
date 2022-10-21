#include <utility>
#include <string>
#include <iostream>
#include <deque>

#if STD

#include <stack>
#include <vector>
#include <map>

namespace ft = std;

#else

#include "stack.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "pair.hpp"

#endif


int main () {
	std::cout << "Construct stack\n";
	try {
		std::deque<int>	mydeque(3,100);          // deque with 3 elements
		ft::vector<int>	myvector(2,200);        // vector with 2 elements

		ft::stack<int> first;                    // empty stack
		ft::stack<int> second(mydeque);         // stack initialized to copy of deque

		ft::stack<int,ft::vector<int>> third;  // empty stack using vector
		ft::stack<int,ft::vector<int>> fourth(myvector);

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	} catch(const std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Empty stack\n";
	try {
		ft::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}

		std::cout << "total: " << sum << '\n';
	} catch(const std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Size stack\n";
	try {
		ft::stack<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i=0; i<5; i++) myints.push(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
	} catch(const std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}

	try {
		std::cout << "Top stack\n";
		ft::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	} catch(const std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "Push && Pop stack\n";
	try {
		ft::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << '\n';
	} catch(const std::exception &e ) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
