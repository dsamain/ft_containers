#include <iostream>
#include <time.h>
#include "../vector.hpp"
#include <vector>
#include "../map.hpp"
#include <map>
#include "../set.hpp"
#include <set>
#include "../pair.hpp"
#include <stack>
#include "../stack.hpp"

#ifdef STD
	#define ns std
#else
	#define ns ft
#endif

#define putVector(v) \
	std::cout << "vector : (size  " << v.size() << ")" << std::endl; \
	for (unsigned int i = 0; i < v.size(); i++) \
		std::cout << v[i] << " "; \
	std::cout << std::endl;


#define putTime(time) \
	std::cout << "\033[1;32m" << (double)(clock() - time) / CLOCKS_PER_SEC << "s" << "\033[0m\n"; \
    time = clock();

template<typename T, typename U>
void putMap(ns::map<T, U> &mp) {
	std::cout << "mp : (size : " << mp.size() << ")" << std::endl;
	for (typename ns::map<T, U>::iterator it = mp.begin(); it != mp.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}


ns::vector<int> permutation(int n); 