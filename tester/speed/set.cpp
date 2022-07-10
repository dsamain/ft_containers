#include <iostream>
#include "../utils.hpp"

int main(int ac, char **av) {
    int seed = (ac > 1 ? std::stoi(av[1]) : 0);
	//std::cout << "seed=" << seed << std::endl << std::endl;
    srand(seed);
    double time = 0;

    {
        ns::set<int> st;

        std::cout << "Inserting 1000000 random elem : ";
    
        ns::vector<int> v = permutation(1000000);
        for (unsigned int i = 0; i < v.size(); i++)
            st.insert(v[i]);

        putTime(time);

        std::cout << "Erasing 1000000 elem in random order : ";

        v = permutation(1000000);
        for (unsigned int i = 0; i < v.size(); i++)
            st.erase(v[i]);

        putTime(time);

    }
    {
        ns::set<int> st;

        std::cout << "Inserting from 1 to 5000000 in order : ";
        for (int i = 1; i <= 2000000; i++)
            st.insert(i);

        putTime(time);

        ns::vector<int> v = permutation(2000000);
        std::cout << "Erasing from 1 to 5000000 in random order : ";
        for (unsigned int i =0 ; i < v.size(); i++)
            st.erase(v[i]);
        
        putTime(time);
    }
    {
        ns::set<int> st;
        ns::vector<int> v = permutation(1000000); 

        std::cout << "Inserting 1000000 elem : "; 
        for (unsigned int i = 0; i < v.size(); i++) 
            st.insert(v[i]);
        putTime(time);

        std::cout << "Perform 1000000 find/lower_bound/upper_bound querry : ";
        for (unsigned int i = 0; i < 1000000; i++) {
            st.find(rand()%v.size());
            st.lower_bound(rand()%v.size());
            st.upper_bound(rand()%v.size());
        }
        putTime(time);
    }

    std::cout << std::endl << "TOTAL : ";
    putTime((time = 0));


    
    
}


