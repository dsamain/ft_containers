#include "../utils.hpp"

#ifdef STD
	#define ns std
#else
	#define ns ft
#endif

int main() {
	ns::stack<int> st;
	
	for (int i = 0; i < 10; i++)
		st.push(i);

	ns::stack<int> st2(st);
	ns::stack<int> st3;
	st3 = st2;

	std::cout << st.size() << std::endl;
	std::cout << st2.size() << std::endl;
	std::cout << st3.size() << std::endl;


	while (!st.empty()) {
		std::cout << st.top() << std::endl;
		st.pop();
	}

	std::cout << "st.empty() : " << st.empty() << std::endl;
	std::cout << "st.size() : " << st.size() << std::endl;
}