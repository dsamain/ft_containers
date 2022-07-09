#include <iostream>
#include "../../vector.hpp"
#include <vector>

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