#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "node.hpp"
#include "type_traits.hpp"
#include "algorithm.hpp"
#include "vector.hpp"
#include "template_utils.hpp"
#include <random>
#include <time.h>
#include "pair.hpp"

template<typename T>
class Foo {

};

#define N 20

#define ns ft
typedef int key;
typedef int value;

#define putv(v) std::cout << "v: "; for(ns::vector<type>::iterator it = v.begin(); it != v.end(); it++) std::cout << *it << " "; std::cout << "(" << v.size() << "," << v.capacity() << ")" << std::endl;
#define putm(mp) std::cout << "map: "; for(ns::map<key,value>::iterator it = mp.begin(); it != mp.end(); it++) std::cout << "[" << it->first << "=" << it->second << "] "; std::cout << "(sz: " << mp.size() << ")" << std::endl;
#define putit(it) std::cout << "it->val: " << it->first << " " << it->second << std::endl;

std::vector<int> permutation(int n) {
	std::vector<int> v(n), ret;
	for (int i = 0; i < n; i++) v[i] = i+1;
	srand(time(NULL));
	while (v.size()) {
		int idx = rand()%v.size();
		std::swap(v[idx],v.back());
		ret.push_back(v.back()); v.pop_back();
	}
	return ret;
}

typedef ft::tree<int, std::less<int>, std::allocator<int>> tree_type;

int main() {

	tree_type tree;


	tree.insert(1);
	tree.insert(2);
	tree.insert(3);

} 