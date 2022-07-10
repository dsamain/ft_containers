#include <iostream>
#include "utils.hpp"

int main(int ac, char **av) {
    int seed = (ac > 1 ? std::stoi(av[1]) : 0);
    srand(seed);

	std::cout << "\033[1;35m\ncheckValid() function check if the tree respect the rules of a red black tree\033[0m" << std::endl;

	ft::set<int> st;

	std::cout << "\nInserting 1000000 elem in set and call checkValid() randomly" << std::endl;
	ft::vector<int> v = permutation(1000000);
	for (unsigned int i = 0; i < v.size(); i++) {
		st.insert(v[i]);
		if (rand()%100000 == 0)
			st.checkValid();
	}
	std::cout << "\nErasing 1000000 elem in set and call checkValid() randomly" << std::endl;
	v = permutation(1000000);
	for (unsigned int i = 0; i < v.size(); i++) {
		st.erase(v[i]);
		if (rand()%100000 == 0)
			st.checkValid();
	}

	std::cout << "\nInserting 1000000 elem in order in set and call checkValid() randomly" << std::endl;
	for (unsigned int i = 0; i < 1000000; i++) {
		st.insert(i);
		if (rand()%100000 == 0)
			st.checkValid();
	}
	st.clear();

	std::cout << "\033[;35m\nRED BLACK TREE VISUALIZER\033[0m" << std::endl;
	int x;
	while (1) {
		std::cout << "\n: ";
		std::cin >> x;
		//std::cout << "Tree: " << std::endl;

		st.insert(x);
		st.print();
	}

}


