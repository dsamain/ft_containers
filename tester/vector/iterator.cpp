#include "../utils.hpp"

#ifdef STD
	#define ns std
#else
	#define ns ft
#endif

int main() {
	ns::vector<int> v(100);
	for (unsigned int i = 0; i < v.size(); i++) v[i] = i;

	ns::vector<int>::iterator it = v.begin();
	ns::vector<int>::const_iterator cit = v.begin();
	ns::vector<int>::const_iterator cit1(it);
	ns::vector<int>::reverse_iterator rit = v.rbegin();
	ns::vector<int>::const_reverse_iterator crit = v.rbegin() + 8;

	it += 5;
	--it;
	it--;
	while (cit < 2 + it) {
		std::cout << *cit++ << " ";
	}
	std::cout << std::endl;
	std::cout << (it - cit1) << std::endl;
	while (rit != crit) {
		std::cout << *rit << " ";
		++rit;
	}

	std::cout << (it < it + 3) << std::endl;
	std::cout << (it <= it) << std::endl;
	std::cout << (it > it - 3) << std::endl;
	std::cout << (it >= it + 1) << std::endl;
	std::cout << (it == cit) << std::endl;
	std::cout << (it != it + 3) << std::endl;



}