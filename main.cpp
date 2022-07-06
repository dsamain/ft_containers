#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "map.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "vector.hpp"
#include "template_utils.hpp"
#include <random>
#include <time.h>
//#include "node.hpp"
#include "pair.hpp"

template<typename T>
class Foo {

};

#define N 20

#ifdef STD
 #define ns std
#else
# define ns ft
#endif

typedef int key;
typedef int value;

#define putv(v) std::cout << "v: "; for(ns::vector<type>::iterator it = v.begin(); it != v.end(); it++) std::cout << *it << " "; std::cout << "(" << v.size() << "," << v.capacity() << ")" << std::endl;
#define putm(mp) std::cout << "map: "; for(ns::map<key,value>::iterator it = mp.begin(); it != mp.end(); it++) std::cout << "[" << it->first << "=" << it->second << "] "; std::cout << "(sz: " << mp.size() << ")" << std::endl;
#define putmit(it) std::cout << "it->val: " << it->first << " " << it->second << std::endl;
#define putrite(rit) std::cout << "rite : " << *rit << std::endl;

ns::vector<int> permutation(int n) {
	ns::vector<int> v(n), ret;
	for (int i = 0; i < n; i++) v[i] = i+1;
	srand(time(NULL));
	while (v.size()) {
		int idx = rand()%v.size();
		ns::swap(v[idx],v.back());
		ret.push_back(v.back()); v.pop_back();
	}
	return ret;
}

void put_eq(ns::vector<value>::reverse_iterator rit1, ns::vector<value>::reverse_iterator rit2) {
	printf("%d == %d : %d\n", *rit1, *rit2, rit1 == rit2);
	printf("%d != %d : %d\n", *rit1, *rit2, rit1 != rit2);
	printf("%d < %d : %d\n", *rit1, *rit2, rit1 < rit2);
	printf("%d <= %d : %d\n", *rit1, *rit2, rit1 <= rit2);
	printf("%d > %d : %d\n", *rit1, *rit2, rit1 > rit2);
	printf("%d >= %d : %d\n", *rit1, *rit2, rit1 >= rit2);
}

int main() {
	
	ns::vector<key> v = permutation(N);
	ns::map<key,value> mp;
	
	//std::sort(v.begin(), v.end(), std::greater<key>());
	//std::sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		mp[v[i]] = 0;
	}

	mp._tree.print();
} 