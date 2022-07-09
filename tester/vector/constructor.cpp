#include "utils.hpp"

#ifdef STD
	#define ns std
#else
	#define ns ft
#endif

int main() {
	{
		ns::vector<int> v(10);
		ns::vector<int> v1(v);
		ns::vector<int> v2(v.begin(), v.end());
		ns::vector<int> v3(7, 7);

		putVector(v);
		putVector(v1);
		putVector(v2);
		v2 = ns::vector<int>(12);
		putVector(v2);
		putVector(v3);
	}
	{
		ns::vector<std::string> v(10, "oh");
		ns::vector<std::string> v1(v);
		ns::vector<std::string> v2(v.begin(), v.end());
		ns::vector<std::string> v3(7, "eh");

		putVector(v);
		putVector(v1);
		putVector(v2);
		v2 = ns::vector<std::string>(12, "ah");
		putVector(v2);
		putVector(v3);
	}


}