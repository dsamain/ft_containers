#include "utils.hpp"

#ifdef STD
	#define ns std
#else
	#define ns ft
#endif

int main() {
	{
		ns::vector<int> v(10);
		v.resize(14, 7);
		putVector(v);
		v.resize(7, -1);
		putVector(v);
		v.reserve(100);
		std::cout << v.capacity() << std::endl;
		putVector(v);
		v.reserve(0);
		putVector(v);
	}
	{
		ns::vector<std::string> v;
		ns::vector<std::string> v1;

		for (int i = 0; i < 10; i++)
			v1.push_back(std::to_string(i));

		v.assign(5, "pouet");
		putVector(v);
		v.assign(v1.begin(), v1.end());
		putVector(v);
		while (!v1.empty()) v1.pop_back();
		putVector(v1);
	}
	{
		ns::vector<int> v;
		ns::vector<int> v1;
		for (int i = 0; i < 100; i++) v.push_back(i);
		v.insert(12 + v.begin(), 42);
		v.insert(v.end() - 12, 24);
		v.insert(v.begin() + 34, 20, 7);
		std::cout << v.back() << " " << v.front() << std::endl;
		putVector(v);
		v1 = ns::vector<int>(12, -1);
		v1.insert(v1.begin() + 3, v.begin(), v.end());
		putVector(v);
		v1.erase(v1.begin());
		putVector(v1);
		v1.erase(v1.begin()+1, v1.end());
		putVector(v1);
		swap(v1, v);
		putVector(v);
		putVector(v1);
		v.clear();
		v1.clear();
		putVector(v);
		putVector(v1);
	}
	{
		ns::vector<int> v;
		for (int i = 0; i < 12; i++) v.push_back(i);
		try {
			v.at(12) = 42;
		} catch (std::out_of_range& e) {
			std::cout << "out of range" << std::endl;
		}
		try {
			v.at(-1) = 42;
		} catch (std::out_of_range& e) {
			std::cout << "out of range" << std::endl;
		}
		try {
			v.at(0) = 42;
		} catch (std::out_of_range& e) {
			std::cout << "out of range" << std::endl;
		}
	}
	{
		ns::vector<int> v;
		ns::vector<int> v1;
		for (int i = 0; i < 32; i++) v.push_back(i);
		for (int i = 0; i < 32; i++) v.push_back(32 - i);
		std::cout << (v == v1) << std::endl;
		std::cout << (v != v1) << std::endl;
		std::cout << (v <= v1) << std::endl;
		std::cout << (v >= v1) << std::endl;
		std::cout << (v < v1) << std::endl;
		std::cout << (v > v1) << std::endl;
	}
}