#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <string>

using namespace std;

int	main() {

	list<pair<int, string> > lst;

	unsigned int lst_size = 7;

	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(pair<int, string>((lst_size - i), "coucou"));

	map<int, string> mplst(lst.begin(), lst.end());
	map<int, string>::iterator itlst = mplst.begin(), itelst = mplst.end();

	cout << "\t-- TEEEEST --" << endl;
	map<int, string> mp_rangelst(itlst, --(--itelst));
	cout << "\t-- TEEEEST --" << endl;
	for (int i = 0; itlst != itelst; ++itlst) {
		itlst->second = "biboop";
	}

	return 0;
}
