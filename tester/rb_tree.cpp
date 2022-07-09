#include <iostream>
#include "utils.hpp"

int main(int ac, char **av) {
    int seed = (ac > 1 ? std::stoi(av[1]) : 0);
    srand(seed);
    double time = 0;

}