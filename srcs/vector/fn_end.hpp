void	fn_end() {
	ft::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}
