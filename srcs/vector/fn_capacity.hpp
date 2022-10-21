void	fn_capacity() {
	ft::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);

	std::cout << "size: " << (int) myvector.size() << '\n';
	std::cout << "capacity: " << (myvector.capacity() >= myvector.size()) << '\n';
	std::cout << "max_size: " << (int) myvector.max_size() << '\n';
}
