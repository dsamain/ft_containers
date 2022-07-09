#include <iostream>
#include "../utils.hpp"

int main(int ac, char **av) {
    int seed = (ac > 1 ? std::stoi(av[1]) : 0);
    srand(seed);
    double time = 0;

    {
        ns::map<int,int> mp;

        std::cout << "Inserting 1000000 random elem : ";
    
        ns::vector<int> v = permutation(1000000);
        for (unsigned int i = 0; i < v.size(); i++)
            mp.insert(ns::make_pair(v[i], 42));

        putTime(time);

        std::cout << "Erasing 1000000 elem in random order : ";

        v = permutation(1000000);
        for (int i = 0; i < v.size(); i++)
            mp.erase(v[i]);

        putTime(time);

    }
    {
        ns::map<int, std::string> mp;

        std::cout << "Inserting from 1 to 5000000 in order : ";
        for (int i = 1; i <= 2000000; i++)
            mp.insert(ns::make_pair(i, "pouet"));

        putTime(time);

        ns::vector<int> v = permutation(2000000);
        std::cout << "Erasing from 1 to 5000000 in random order : ";
        for (unsigned int i =0 ; i < v.size(); i++)
            mp.erase(v[i]);
        
        putTime(time);
    }
    {
        ns::map<int,int> mp;
        ns::vector<int> v = permutation(1000000); 

        std::cout << "Inserting 1000000 elem : "; 
        for (unsigned int i = 0; i < v.size(); i++) 
            mp.insert(ns::make_pair(v[i], 24));
        putTime(time);

        std::cout << "Perform 1000000 find/lower_bound/upper_bound querry : ";
        for (unsigned int i = 0; i < 1000000; i++) {
            mp.find(rand()%v.size());
            mp.lower_bound(rand()%v.size());
            mp.upper_bound(rand()%v.size());
        }
        putTime(time);
    }

    std::cout << std::endl << "TOTAL : ";
    putTime((time = 0));


    
    
}


