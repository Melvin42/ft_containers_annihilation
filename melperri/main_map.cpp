#include <iostream>
#include <climits>
#include <list>
#include <vector>

#if STD
#include <map>
	namespace ft = std;
#else
#include "map.hpp"
#include <map>
#include "iterator_traits.hpp"
#include "pair.hpp"
#include "utils.hpp"
#endif

	/*
static int iter = 0;

template <typename MAP, typename U>
	void	ft_insert(MAP &mp, U param)
	{
		std::pair<std::map<int, std::string>::iterator, bool> tmp;
//		ft::pair<ft::map<int, std::string>::iterator, bool> tmp;
	
		std::cout << "\t-- [" << iter++ << "] --" << std::endl;
		tmp = mp.insert(param);
	//	std::cout << "insert return: " << printPair(tmp.first);
		std::cout << "Created new node: " << tmp.second << std::endl;
		mp.printTree();
	}

template <typename MAP, typename U, typename V>
	void	ft_insert(MAP &mp, U param, V param2)
	{
//		std::map<U, V>::iterator tmp;
		std::pair<std::map<int, std::string>::iterator, bool> tmp;
	
		std::cout << "\t-- [" << iter++ << "] --" << std::endl;
		tmp = mp.insert(param, param2);
	//	std::cout << "insert return: " << printPair(tmp);
		mp.printTree();
	}
	*/
template<class T1, class T2, class T3>
	void printMap(const ft::map<T1, T2, T3> &mp) {
		typename ft::map<T1, T2, T3>::const_iterator it = mp.begin();
		typename ft::map<T1, T2, T3>::const_iterator ite = mp.end();

		std::cout << "\n************PRINT MAP************\n";

		std::cout << "Size = " << mp.size() << '\n';
		while (it != ite) {
			std::cout << "First = " << it->first << " | Second = " << it->second << std::endl;
			++it;
		}
	}

template<class T1, class T2>
	void printMap(const std::map<T1, T2> &mp) {
		typename std::map<T1, T2>::const_iterator it = mp.begin();
		typename std::map<T1, T2>::const_iterator ite = mp.end();

		std::cout << "\n************PRINT MAP************\n";

		std::cout << "Size = " << mp.size() << '\n';
		while (it != ite) {
			std::cout << "First = " << it->first << " | Second = " << it->second << std::endl;
			++it;
		}
	}

template<class T1, class T2>
	void printMap(const ft::map<T1, T2> &mp) {
		typename ft::map<T1, T2>::const_iterator it = mp.begin();
		typename ft::map<T1, T2>::const_iterator ite = mp.end();

		std::cout << "\n************PRINT MAP************\n";

		std::cout << "Size = " << mp.size() << '\n';
		while (it != ite) {
			std::cout << "First = " << it->first << " | Second = " << it->second << std::endl;
			++it;
		}
	}

template<typename MAP, typename U>
void	ft_erase(MAP &mp, U param) {
	mp.erase(param);
	printMap(mp);
}

template<typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2) {
	mp.erase(param, param2);
	printMap(mp);
}

struct ft_more {
	bool	operator()(const int &first, const int &second) const {
		return (first > second);
	}
};

void	test_pair() {
	std::cout << "/******** TESTING PAIR ********/\n" << std::endl;
		ft::pair <int,int> pair1;
//		ft::pair <int,int> pair2;

		pair1 = ft::make_pair(10,20);
//		pair2 = ft::make_pair(10.5,'A'); // ok: implicit conversion from pair<double,char>

		std::cout << "pair1: " << pair1.first << ", " << pair1.second << '\n';
//		std::cout << "pair2: " << pair2.first << ", " << pair2.second << '\n';
}

void	test_iterator() {
	std::cout << "TESTING ITERATOR\n" << std::endl;
	std::list<ft::pair<int, int> > lst;
	unsigned int lst_size = 7;
	ft::pair<int, int> pair_tmp;
	for (unsigned int i = 0; i < lst_size; ++i) {
		pair_tmp = ft::make_pair(lst_size - i, i);
		lst.push_back(pair_tmp);
	}

//	ft::map<int, int> mp(lst.begin(), lst.end());
//
//	ft::map<int, int>::iterator it = mp.begin(), ite = mp.end();
//
//	std::cout << "size = " << mp.size() << '\n';
//	std::cout << "\t-- PART ONE --" << std::endl;
////	ft::map<int, int> mp_range(it, --(--ite));
//	std::cout << "\t-- PART ONE --" << std::endl;
//	for (int i = 0; it != ite; ++it)
//		it->second = ++i * 5;
//
//
//	std::cout << "\t-- PART ONE --" << std::endl;
//	it = mp.begin(); ite = --(--mp.end());
//	ft::map<int, int> mp_copy(mp);
//	for (int i = 0; it != ite; ++it)
//		it->second = ++i * 7;
//
////	std::cout << "\t-- PART ONE --" << std::endl;
////	printSize(mp);
////	printSize(mp_range);
////	printSize(mp_copy);
//
//	mp = mp_copy;
//	mp_copy = mp_range;
//	mp_range.clear();
//	std::cout << "\t-- PART TWO --" << std::endl;
//	printSize(mp);
//	printSize(mp_range);
//	printSize(mp_copy);
//	std::cout << "TESTING REVERSE_ITERATOR\n" << std::endl;
//	std::cout << "TESTING BIDIR_ITERATOR\n" << std::endl;
//	std::cout << "TESTING ITERATOR_TRAITS\n" << std::endl;
}

void	test_map() {
	std::cout << "/******** TESTING MAP ********/\n" << std::endl;

//	ft::map<int, int>	ftMap;
///	std::list<ft::pair<int, std::string>>	lst;
//	std::list<std::pair<int, std::string>>	stdlst;

//	unsigned int lst_size = 6;
//	for (unsigned int i = 0; i < lst_size; ++i) {
//		lst.push_back(ft::make_pair(i, std::string((lst_size - i), i + 65)));
//		stdlst.push_back(std::make_pair(i, std::string((lst_size - i), i + 65)));
//	}

	/*
	lst.push_back(ft::make_pair(1, "coucou"));
	lst.push_back(ft::make_pair(2,"yeah"));
	lst.push_back(ft::make_pair(3,"oula"));
	lst.push_back(ft::make_pair(4,"ping"));
	lst.push_back(ft::make_pair(5,"bipboop"));
	lst.push_back(ft::make_pair(6,"bang"));
	lst.push_back(ft::make_pair(7,"ooh"));
	lst.push_back(ft::make_pair(8,"man"));
	lst.push_back(ft::make_pair(9,"boost"));
	lst.push_back(ft::make_pair(10,"pim"));
	*/

//	ft::map<int, std::string>	ftMap(lst.begin(), lst.end());
	ft::map<int, std::string, ft_more>	ftMap2;

	ftMap2[42] = "fxsdxgsfg";
	ftMap2[25] = "funny";
	ftMap2[80] = "hey";
	ftMap2[12] = "no";
	ftMap2[27] = "bee";
	ftMap2[90] = "8";
	printMap(ftMap2);
//	std::map<int, std::string>	stdMap;
//	std::map<int, std::string>	stdMap(stdlst.begin(), stdlst.end());

//	ftMap.printTree();
//	for (int i = 2; i < 4; ++i) {
//		std::cout << "i = " << i << std::endl;
//		ft_erase(ftMap, i);
//	}
//	std::cout << "After While \n";
//	ft_erase(ftMap, ftMap.begin()->first);
//	ftMap.printTree();
///	ft_erase(ftMap, (--ftMap.end())->first);

	//	ftMap.insert(ft::make_pair(10,1));
	//	ftMap.insert(ft::make_pair(9,1));
	//	ftMap.insert(ft::make_pair(8,1));
	//	ftMap.insert(ft::make_pair(7,1));
	//	ftMap.insert(ft::make_pair(6,6));
	//	ftMap.insert(ft::make_pair(5,5));
	//	ftMap.insert(ft::make_pair(4,4));
	//	ftMap.insert(ft::make_pair(3,3));
	//	ftMap.insert(ft::make_pair(2,2));
	//	ftMap.insert(ft::make_pair(1,1));

//	std::cout << "ft ------ = " << (--(--(--ftMap.end())))->first << std::endl;
//	std::cout << "FT:\n" << std::endl;
//	printMap(ftMap);
//	printMap(stdMap);

//	std::cout << "FT:\n" << std::endl;
//	std::cout << (++ftMap.begin())->first << std::endl;
//	std::cout << (++stdMap.begin())->first << std::endl;
//	ft_erase(ftMap, ++ftMap.begin());
//	ft_erase(stdMap, ++stdMap.begin());

//	std::cout << "FT:\n" << std::endl;
//	ft_erase(ftMap, ftMap.begin());
//	ft_erase(stdMap, stdMap.begin());
//	std::cout << "FT:\n" << std::endl;
//	ft_erase(ftMap, --ftMap.end());
//	ft_erase(stdMap, --stdMap.end());

//	std::cout << "FT:\n" << std::endl;
//	ft_erase(ftMap, ftMap.begin(), ++(++(++ftMap.begin())));
//	ft_erase(stdMap, stdMap.begin(), ++(++(++stdMap.begin())));
//	std::cout << "FT:\n" << std::endl;
//	std::cout << "laaa = " << (--(--(--ftMap.end())))->first << std::endl;
//	std::cout << "laaa = " << (--(--(--stdMap.end())))->first << std::endl;
//	std::cout << "laaa = " << (--ftMap.end())->first << std::endl;
//	std::cout << "laaa = " << (--stdMap.end())->first << std::endl;
//	ft_erase(ftMap, --(--(--ftMap.end())), --ftMap.end());
//	ft_erase(stdMap, --(--(--stdMap.end())), --stdMap.end());

//	std::cout << "FT:\n" << std::endl;
//	printMap(ftMap);
//	printMap(stdMap);
//	ftMap2.insert(ft::make_pair(0, "hey"));
//	ftMap2.insert(ft::make_pair(1, "hey"));
//	ftMap2.insert(ft::make_pair(4, "hey"));
//	ftMap2.insert(ft::make_pair(5, "wouh"));
//	ftMap2.insert(ft::make_pair(12, "wouh"));
//	ftMap2.insert(ft::make_pair(13, "wouh"));

//	stdMap.insert(std::make_pair(5, "hey"));
//	stdMap.insert(std::make_pair(8, "hey"));
//	stdMap.insert(std::make_pair(10, "hey"));
//	stdMap.insert(std::make_pair(11, "wouh"));
//	stdMap.insert(std::make_pair(12, "wouh"));
//	stdMap.insert(std::make_pair(13, "wouh"));

//	ftMap2.printTree();
//	std::cout << "LAST ERASE\n";
//	ft::map<int, std::string>::iterator	it = --(--(--ftMap2.end()));
//	ft::map<int, std::string>::iterator	it = ++(ftMap2.begin());
//	std::cout << "val = " << it->first << std::endl;
//	std::map<int, std::string>::iterator	stdit = --(--(--stdMap.end()));;
//	std::cout << "val = " << stdit->first << std::endl;
//	ft_erase(ftMap2, --(--ftMap2.end()), ftMap2.end());
//	ft_erase(ftMap2, --(--(--ftMap2.end())), ftMap2.end());
//	std::cout << ftMap2.size() << std::endl;
//	ft_erase(ftMap2, --(--(--ftMap2.end())));
//	ft_erase(ftMap2, ftMap2.begin());
//	ftMap2.printTree();
//	ftMap2.printTree();
//	ft_erase(ftMap2, (--(--ftMap2.end()))->first);
//	ft_erase(ftMap2, 10);
//	ft_erase(ftMap2, 5);
//	ft_erase(ftMap2, 11);
//	ft_erase(ftMap2, ftMap2.begin()->first);
//	ft_erase(ftMap2, (--ftMap2.end())->first);
//	ft_erase(ftMap2, ftMap2.begin());
//	ft_erase(ftMap2, ftMap2.begin());
//	ftMap2.printTree();
//	ft_erase(ftMap2, ftMap2.begin());
//	ft_erase(ftMap2, ftMap2.begin());

//	ft_erase(ftMap2, --(ftMap2.end()));
//	ft_erase(ftMap2, --(ftMap2.end()));
//	ft_erase(ftMap2, --(ftMap2.end()));
//	ft_erase(ftMap2, 10);
//	ft_erase(ftMap2, 11);
//	ft_erase(ftMap2, ftMap2.begin()->first);
//	ft_erase(ftMap2, (--ftMap2.end())->first);
//	ft_erase(ftMap2, ftMap2.begin(), ftMap2.end());
//	ft_erase(ftMap2, ftMap2.begin(), ftMap2.end());
//	ftMap.insert(ft::make_pair(10, "hey"));
//	ftMap.insert(ft::make_pair(11, "wouh"));
//	ftMap.insert(ft::make_pair(12, "wouh"));
//	ftMap[10] = "hey";
//	ftMap[11] = "wouh";
//	stdMap[10] = "hey";
//	stdMap[11] = "wouh";
//	stdMap[12] = "wouh";

//	std::cout << "FT:\n" << std::endl;
//	printMap(ftMap);
//	printMap(stdMap);
//	ft::map<int, std::string>::iterator	it = --(--(--ftMap2.end()));
//	std::cout << "val = " << it->first << std::endl;
//	while (it != ftMap2.end()) {
//		if (it == ftMap2.end())
//			std::cout << "YES\n";
//		std::cout << "val = " << it->first << std::endl;
//		ftMap2.erase(it->first);
//		++it;
//	}


//	std::cout << "val = " << it->first << std::endl;
//	it++;
//	std::cout << "val = " << it->first << std::endl;
//	it++;
//	if (it == ftMap.end())
//		std::cout << "YES\n";
//	std::cout << "ft ------ = " << (--(--(--ftMap.end())))->first << std::endl;
//	std::cout << "std ------ = " << (--(--(--stdMap.end())))->first << std::endl;
//	std::cout << "ft ------ = " << (--ftMap.end())->first << std::endl;
//	std::cout << "std ------ = " << (--stdMap.end())->first << std::endl;
//	printMap(stdMap);
//	ftMap.printTree();
//	ft_erase(stdMap, --(--(--stdMap.end())), stdMap.end());
//	ft_erase(stdMap, --(--(--stdMap.end())), stdMap.end());
//	printMap(ftMap);
//	ftMap.printTree();
//	ftMap2.printTree();
//	std::cout << "LAST ERASE\n";
//	ft_erase(ftMap, --(--(--ftMap.end())), ftMap.end());
//	ft_erase(ftMap, --(--ftMap.end()), ftMap.end());
//	ft_erase(ftMap2, --(--ftMap2.end()), ftMap2.end());
////	ft_erase(ftMap, ftMap.begin(), ftMap.end());

//	ftMap[12] = "un";
//	ftMap[13] = "deux";
//	ftMap[14] = "trois";
//	ftMap[15] = "quatre";

//	printMap(ftMap);
//	ft::map<int, std::string>::iterator it = --ftMap.end();
//	ft_erase(ftMap, ftMap.begin(), ftMap.end());
//	for (; it != ftMap.begin(); it--) {
//		std::cout << "val = " << it->first << std::endl;
//	}
//	printMap(ftMap);


//	ft::map<int, int>	mp_range(it, --(--ite));

//	for (int i = 0; it != ite; ++it)
//		it->second = ++i * 5;

//	it = ftMap.begin();
//	ite = --(--ftMap.end());

//	ft::map<int, int>	ftMapCpy(ftMap);

//	for (int i = 0; it != ite; ++it)
//		it->second = ++i * 7;

//	printMap(ftMap);
//	printMap(mp_range);
//	printMap(ftMapCpy);

//	ftMap.printTree();
//	ftMap = ftMapCpy;

//	std::cout << "PAR ICI\n";
//	ftMap.printTree();
//	printMap(ftMap);
//	printMap(ftMapCpy);

//	ftMap[-1] = 23458;
//	ftMap[10] = 123;
//	ftMap[10] = 348765;

//	printMap(ftMap);
	
//	std::cout << "ERAAAAASE" << std::endl;
//	ftMap.erase(4);
//	ftMap.erase(2);
//	ftMap.printTree();
//	printMap(ftMap);
//	std::cout << "ERAAAAASE" << std::endl;
//	ftMap.erase(9);
//	printMap(ftMap);
//	std::cout << "ERAAAAASE" << std::endl;
//	ftMap.erase(10);
//	printMap(ftMap);
//	std::cout << "ERAAAAASE" << std::endl;
//	ftMap.erase(-1);
//	printMap(ftMap);
//	std::cout << "ERAAAAASE\n";
//	ftMap.erase(ftMap.begin());
//	std::cout << "ERAAAAASE\n";
//	ftMap.erase(--ftMap.end());

//	printMap(ftMap);
//	ft::map<int, std::string>	ftMapTest;

//	ftMapTest.insert(ft::make_pair(42, "coucou"));
//	ftMapTest.insert(ft::make_pair(80, "boop"));
//	ftMapTest.insert(ft::make_pair(12, "paf"));
/*
	ftMapTest[42] = "coucou";
	ftMapTest[25] = "bip";
	ftMapTest[80] = "boop";
	ftMapTest[12] = "paf";
	ftMapTest[27] = "pouuuf";
	ftMapTest[90] = "X";

	ftMapTest.printTree();
	printMap(ftMapTest);

	std::cout << "Find " << ftMapTest.find(12)->first << " = " << ftMapTest.find(12)->second << std::endl;
	ft::map<int, std::string>::iterator	itend = ftMapTest.end();
	ft::map<int, std::string>::iterator	ret;

	ret = ftMapTest.find(3);
	if (ret == itend)
		std::cout << "Find 3 = END() " << std::endl;
	else
		std::cout << "Find " << ftMapTest.find(3)->first << " = " << ftMapTest.find(3)->second << std::endl;
		*/






//	ftMap.erase(4);
	
//	std::cout << "ftMap[10] !!!\n";
//	ftMap[-1] = 81;
//	ftMap[10] = 81;
//	ftMap[8] = 81;
//	ftMap[1] = 81;
//	ftMap.printTree();
//	std::cout << "bizar\n";
//	stdMap[-2] = 81;
//	ftMap.erase(4);
//	ftMap.printTree();
//	std::cout << "FIRST CLEAR!!!\n";
//	ftMapCpy.clear();
//	std::cout << "END CLEAR!!!\n";
//	ftMap.printTree();
//	ftMapCpy.printTree();
	/*
//	ft::map<int, int>::const_iterator		c_ftIt = ftMap.begin();;

	ft::map<int, int>::iterator		ftIt;
	ftIt = ftMap.begin();

	ft::map<int, int>::iterator		ftIte = ftMap.end();
	ft::map<int, int> mp_range(ftIt, --(--ftIte));
	ftIt = mp_range.begin();
	for (; ftIt != mp_range.end(); ftIt++) {
		std::cout << "first  = " << ftIt->first << '\n';
		std::cout << "second = " << ftIt->second << '\n';
		ftIt->second = 4;
	}
	ftIt = mp_range.begin();
	ftIte = --(--mp_range.end());
	for (; ftIt != ftIte; ftIt++) {
		std::cout << "first  = " << ftIt->first << '\n';
		std::cout << "second = " << ftIt->second << '\n';
	}
	std::list<ft::pair<int, int> > lst;
	unsigned int lst_size = 7;
	for (unsigned int i = 0; i < lst_size; ++i) {
		lst.push_back(ft::pair<int, int>((lst_size - i), i));
		std::cout << lst_size - i << '\n';
	}

	ft::map<int, int> mplst(lst.begin(), lst.end());

	std::cout << "\t-- TEEEEST --" << std::endl;
	mplst.printTree();
//	std::cout << (--mplst.end())->first << '\n';
//	ft::map<int, int>::iterator itlst(mplst.begin()), itelst(mplst.end());
	ft::map<int, int>::iterator itlst = mplst.begin(), itelst = mplst.end();

	ft::map<int, int> mp_rangelst(itlst, --(--itelst));
	for (int i = 0; itlst != itelst; ++itlst)
		itlst->second = ++i * 5;

	mp_rangelst.printTree();
	std::cout << "\t-- TEEEEST222222--" << std::endl;
	itlst = mplst.begin();
	itelst = --(--mplst.end());

	ft::map<int, int> mp_cpy(mplst);

	for (int i = 0; itlst != itelst; ++itlst)
		itlst->second = ++i * 7;
	mp_cpy.printTree();

	mplst = mp_cpy;
	printTree();
	*/
//	mp_cpy = mp_range;
	// REPRENDRE ICIIIII

//	itlst = mplst.begin();
//	itelst = --(--mplst.end());
//	mp_rangelst.printTree();

//	for (int i = 0; itlst != itelst; itlst++)
//		itlst->second = ++i * 5;


//	std::map<int, int>::iterator	stdIt;

//	ftMap.erase(ftMap.begin());
//	ftMap.erase(2);
//	ftMap.erase(3);
//	ftMap.erase(4);
//	ftMap.erase(5);
//	ftMap.erase(6);
//	ftMap.erase(7);
//	ftMap.erase(8);
//	ftMap.erase(9);
//	ftMap.erase(10);
//	ftMap.erase(11);
//	ftMap.erase(12);
//	ftMap.erase(ftMap.end() - 1);
//	ftMap.erase(ftMap.end() - 1);
//	ftMap.printTree();

/*	

	stdIt = stdMap.begin();
	std::cout << "std-print\n";
//	std::cout << "stdMap[" << 0 << "]  = " << stdMap[0] << '\n';
	std::cout << "stdMap[" << 10 << "]  = " << stdMap[10] << '\n';
	std::cout << "stdMap[" << 11 << "]  = " << stdMap[11] << '\n';
	std::cout << "stdMap[" << 12 << "]  = " << stdMap[12] << '\n';
	std::cout << "Size = " << stdMap.size() << '\n';
	std::cout << "find 10 = " << stdMap.find(10)->second << '\n';
	std::cout << "find 1000 = " << stdMap.find(1000)->second << '\n';
	for (size_t i = 0; i < stdMap.size(); i++, stdIt++) {
//		std::cout << "stdMap[" << i << "]  = " << stdMap[i] << '\n';
		std::cout << "first  = " << stdIt->first << '\n';
		std::cout << "second = " << stdIt->second << '\n';
	}

	std::cout << "ft-print\n";
	ftIt = ftMap.begin();
//	std::cout << "ftMap[" << 0 << "]  = " << ftMap[0] << '\n';
	std::cout << "ftMap[" << 10 << "]  = " << ftMap[10] << '\n';
	std::cout << "ftMap[" << 11 << "]  = " << ftMap[11] << '\n';
//	std::cout << "ftMap[" << 12 << "]  = " << ftMap[12] << '\n';
	std::cout << "Size = " << ftMap.size() << '\n';
	std::cout << "find 10 = " << ftMap.find(10)->second << '\n';
//	std::cout << "find 10 = " << ftMap.find(1000)->_pair.second << '\n';
//	for (size_t i = 0; i < ftMap.size(); i++, ftIt++) {
//		std::cout << "ftMap[" << i << "]  = " << ftMap[i] << '\n';

	std::cout << "MAP2 ITERATOR CONSTRUCTOR\n";
	ft::map<int, int>	map2(ftMap.begin(), ftMap.end());

//	map2.printTree();

	std::cout << "MAP3 INSERTING BY RANGE\n";
	ft::map<int, int>	map3;
	map3.insert(ftMap.begin(), ftMap.end());

//	std::map<char,int>::iterator it = ftmap.begin();
//	mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
//	mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

//	map3.printTree();
	std::cout << "operator++\n";
	ftIt = ftMap.begin();
	for (size_t i = 1; ftIt != ftMap.end(); ftIt++, i++) {
		std::cout << i << " first  = " << ftIt->first << '\n';
		std::cout << "second = " << ftIt->second << '\n';
	}
	std::cout << "++operator\n";
	ftIt = ftMap.begin();
	for (size_t i = 1; ftIt != ftMap.end(); ++ftIt, i++) {
		std::cout << i << " first  = " << ftIt->first << '\n';
		std::cout << "second = " << ftIt->second << '\n';
	}
	std::cout << "operator--\n";
	ftIt = ftMap.end();
	for (size_t i = 1; ftIt != ftMap.begin(); ftIt--, i++) {
		std::cout << i << " first  = " << ftIt->first << '\n';
		std::cout << "second = " << ftIt->second << '\n';
	}
	std::cout << " first  = " << ftIt->first << '\n';
	std::cout << "second = " << ftIt->second << '\n';
	std::cout << "--operator\n";
	ftIt = ftMap.end();
	for (size_t i = 1; ftIt != ftMap.begin(); --ftIt, i++) {
		std::cout << i << " first  = " << ftIt->first << '\n';
		std::cout << "second = " << ftIt->second << '\n';
	}
	std::cout << " first  = " << ftIt->first << '\n';
	std::cout << "second = " << ftIt->second << '\n';

//	ftMap.printTree();

	std::cout << "stdCount: " << stdMap.count(4) << '\n';
	std::cout << "ftCount: " << ftMap.count(4) << '\n';
	std::cout << "stdCount: " << stdMap.count(10) << '\n';
	std::cout << "ftCount: " << ftMap.count(10) << '\n';

	std::cout << "std_lower_bound: " << stdMap.lower_bound(10)->first << '\n';
	std::cout << "ft_lower_bound: " << ftMap.lower_bound(10)->first << '\n';
	std::cout << "std_lower_bound: " << stdMap.lower_bound(11)->first << '\n';
	std::cout << "ft_lower_bound: " << ftMap.lower_bound(11)->first << '\n';
	std::cout << "std_lower_bound: " << stdMap.lower_bound(8)->first << '\n';
	std::cout << "ft_lower_bound: " << ftMap.lower_bound(8)->first << '\n';

	std::cout << "std_upper_bound: " << stdMap.upper_bound(10)->first << '\n';
	std::cout << "ft_upper_bound: " << ftMap.upper_bound(10)->first << '\n';
	std::cout << "std_upper_bound: " << stdMap.upper_bound(11)->first << '\n';
	std::cout << "ft_upper_bound: " << ftMap.upper_bound(11)->first << '\n';
	std::cout << "std_upper_bound: " << stdMap.upper_bound(8)->first << '\n';
	std::cout << "ft_upper_bound: " << ftMap.upper_bound(8)->first << '\n';

	ft::map<int, std::string>	strMap;

	strMap.insert(ft::make_pair(3, "ocuudou"));
	strMap.insert(ft::make_pair(2, "oou"));
	strMap.insert(ft::make_pair(1, "oudou"));
	strMap.insert(ft::make_pair(4, "cdasdaoudou"));
	strMap.insert(ft::make_pair(5, "oudouaasfsgsdfgsgd"));

	ft::map<int, std::string>	strMap2(strMap.begin(), strMap.end());

	for (ft::map<int, std::string>::iterator ftIt = strMap.begin(); ftIt != strMap.end(); ftIt++) {
		std::cout << " first  = " << ftIt->first << ' '
		<< "second = " << ftIt->second << '\n';
	}
	std::cout << " first  = " << strMap.end()->first;
	std::cout << " second = " << strMap.end()->second<< '\n';
	bool res[2];

	for (ft::map<int, std::string>::const_iterator it1 = strMap.begin(); it1 != strMap.end(); ++it1) {
		for (ft::map<int, std::string>::const_iterator it2 = strMap.begin(); it2 != strMap.end(); ++it2) {
			res[0] = strMap.key_comp()(it1->first, it2->first);
			res[1] = strMap.value_comp()(*it1, *it2);
			std::cout << "with [" << it1->first << " and " << it2->first << "]: ";
			std::cout << "key_comp: " << res[0] << " | " << "value_comp: " << res[1] << std::endl;
		}
	}
	*/
	
//	ft_insert(strMap, ft::map<int, std::string>::value_type(42, "lol"));
//	ft_insert(strMap, ft::map<int, std::string>::value_type(42, "lol"));
//	ft_insert(mp, T3(42, "mdr"));
//	
//	ft_insert(mp, T3(50, "mdr"));
//	ft_insert(mp, T3(35, "funny"));
//	
//	ft_insert(mp, T3(45, "bunny"));
//	ft_insert(mp, T3(21, "fizz"));
//	ft_insert(mp, T3(38, "buzz"));
//	
//	ft_insert(mp, mp.begin(), ft::pair<int, std::string>(55, "fuzzy"));
//	
//	ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
//	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
//	ft_insert(mp2, mp2.end(), T3(1500, "World"));

	/*
	std::cout << "TESTING RESIZE\n" << std::endl;
	std::cout << "TESTING ERASE\n" << std::endl;
	std::cout << "TESTING OPERATOR[]\n" << std::endl;

	try {
	} catch (std::exception &e) {
		e.what();
	}
	std::cout << "TESTING MAX_SIZE\n";
	std::cout << "TESTING SWAP\n";
	std::cout << "CLEAR\n";
	*/
}

void	test_is_integral() {
	std::cout << "TESTING IS_INTEGRAL\n"
		<< "\nbool: " << ft::is_integral<bool>::value
		<< "\nchar: " << ft::is_integral<char>::value
		<< "\nwchar_t: " << ft::is_integral<wchar_t>::value
		<< "\nsigned char: " << ft::is_integral<signed char>::value
		<< "\nshort int: " << ft::is_integral<short int>::value
		<< "\nint: " << ft::is_integral<int>::value
		<< "\nlong int: " << ft::is_integral<long int>::value
		<< "\nlong long int: " << ft::is_integral<long long int>::value
		<< "\nunsigned char: " << ft::is_integral<unsigned char>::value
		<< "\nunsigned short int: "
		<< ft::is_integral<unsigned short int>::value
		<< "\nunsigned long int: " << ft::is_integral<unsigned long int>::value
		<< "\nunsigned long long int: "
		<< ft::is_integral<unsigned long long int>::value << std::endl;
}

void	test_equal() {
	std::cout << "TESTING EQUAL\n" << std::endl;

	int				myints[] = {20, 40, 60, 80, 100};//  myints: 20 40 60 80 100
	std::vector<int>	myvector(myints, myints + 5);   // myvector: 20 40 60 80 100

	// using default comparison:
	if (ft::equal(myvector.begin(), myvector.end(), myints))
		std::cout << "The contents of both sequences are equal.\n";
	else
		std::cout << "The contents of both sequences differ.\n";

//	myvector[3] = 81;                               // myvector: 20 40 60 81 100
}

void	test_enable_if() {
	std::cout << "TESTING ENABLE_IF\n" << std::endl;
}

void	test_relational_operator() {
	std::cout << "TESTING RELATIONAL_OPERATOR\n" << std::endl;

	ft::map<int, int> mp1;
	ft::map<int, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;

	std::cout << "==: " << (mp1 == mp2) << std::endl;
	std::cout << "!=: " << (mp1 != mp2) << std::endl;
	std::cout << "< : " << (mp1 <  mp2) << std::endl;
	std::cout << "<=: " << (mp1 <= mp2) << std::endl;
	std::cout << "> : " << (mp1 >  mp2) << std::endl;
	std::cout << ">=: " << (mp1 >= mp2) << std::endl;

	mp2['a'] = 3;

	std::cout << "==: " << (mp1 == mp2) << std::endl;
	std::cout << "!=: " << (mp1 != mp2) << std::endl;
	std::cout << "< : " << (mp1 <  mp2) << std::endl;
	std::cout << "<=: " << (mp1 <= mp2) << std::endl;
	std::cout << "> : " << (mp1 >  mp2) << std::endl;
	std::cout << ">=: " << (mp1 >= mp2) << std::endl;

//	std::cout << "== " << (vect1 == vect2) << '\n';
//	std::cout << "!= " << (vect1 != vect2) << '\n';
//	std::cout << "< " << (vect1 < vect2) << '\n';
//	std::cout << "<= " << (vect1 <= vect2) << '\n';
//	std::cout << "> " << (vect1 > vect2) << '\n';
//	std::cout << ">= " << (vect1 >= vect2) << '\n';
}

void	test_lexicographical_compare() {
	std::cout << "TESTING LEXICOGRAPHICAL_COMPARE\n" << std::endl;

	char	foo[]="Apple";
	char	bar[]="apartment";

//	std::cout << std::boolalpha;

	std::cout << "Comparing foo and bar lexicographically (foo<bar):\n";

	std::cout << "Using default comparison (operator<): ";
	std::cout << ft::lexicographical_compare(foo,foo+5,bar,bar+9);
	std::cout << '\n';
}

//void	test_map() {
//	std::cout << "/******** TESTING MAP ********/\n" << std::endl;
//}

int	main() {
//	test_pair();
//	test_iterator();
//	test_map();
//	test_is_integral();
//	test_equal();
	test_relational_operator();
//	test_lexicographical_compare();
//	test_enable_if();
	return 0;
}
