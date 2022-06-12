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
#include "node.hpp"

template<typename T>
class Foo {

};

#define N 20

#define ns std
typedef int key;
typedef std::string value;

#define putv(v) std::cout << "v: "; for(ns::vector<type>::iterator it = v.begin(); it != v.end(); it++) std::cout << *it << " "; std::cout << "(" << v.size() << "," << v.capacity() << ")" << std::endl;
#define putm(mp) std::cout << "map: "; for(ns::map<key,value>::iterator it = mp.begin(); it != mp.end(); it++) std::cout << "[" << it->first << "=" << it->second << "] "; std::cout << "(sz: " << mp.size() << ")" << std::endl;

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

int main() {
	ns::map<key,value> mp;

	ns::vector<int> v(N);

	//ft_insert(mp, T3(42, "lol"));
	//ft_insert(mp, T3(42, "mdr"));
	//ft_insert(mp, T3(50, "mdr"));
	//ft_insert(mp, T3(35, "funny"));
	//ft_insert(mp, T3(45, "bunny"));

	ns::pair<ns::map<key,value>::const_iterator, bool> ret;


	//ret = mp.insert(ns::make_pair(42,"lol"));
	//printPair(ret.first);
	//ret = mp.insert(ns::make_pair(42,"mdr"));
	//printPair(ret.first);
	//ret = mp.insert(ns::make_pair(50,"mdr"));
	//printPair(ret.first);
	//ret = mp.insert(ns::make_pair(35,"funny"));
	//printPair(ret.first);
	//ret = mp.insert(ns::make_pair(45,"bunny"));

	//ret = mp.insert(ns::make_pair(45,"e"));
	//printPair(ret.first);


	putm(mp);

	ns::map<key,value>::const_iterator it = mp.begin(), ite = mp.end();
	while (it != ite) {
		std::cout << "[" << it->first << "," << it->second << "] ";
		++it;
	}
	std::cout << std::endl;

	//std::cout << "it == rend : " << (it == mp.rend()) << std::endl;

} 