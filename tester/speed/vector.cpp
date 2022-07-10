#include "../utils.hpp"

int main(int ac, char **av) {
    int seed = (ac > 1 ? std::stoi(av[1]) : 0);
    srand(seed);
    double time = 0;

    std::cout << "construct with 100000000 elem : ";
    ns::vector<int> v(10000000, 1);
    putTime(time);

	std::cout << "inserting 5 at random places: ";
	for (int i = 0; i < 5; i++)
		v.insert(v.begin() + rand() % v.size(), 42);
    putTime(time);

    std::cout << "inserting 100000000 more elem in the middle: ";
    v.insert(v.begin() + 50000, 100000000, 42);
    putTime(time);

    std::cout << "pop_back() everything() : ";
    while (!v.empty()) v.pop_back();
    putTime(time);

    std::cout << "push_back() 10000000 elem : ";
    for (int i = 0; i < 10000000; i++) v.push_back(rand());
    putTime(time);

    std::cout << "Assign 30000000 elem : ";
    v.assign(30000000, 42);
    putTime(time);

    std::cout << "Resize v.size() * 10 : ";
    v.resize(v.size() * 10);
    putTime(time);

    std::cout << "clear() : ";
    v.clear();
    putTime(time);

    std::cout << std::endl << "TOTAL : ";
    putTime((time = 0));


}