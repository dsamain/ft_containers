
#include "utils.hpp"

ns::vector<int> permutation(int n) {
	ns::vector<int> v(n), ret;
	for (int i = 0; i < n; i++) v[i] = i+1;
	while (v.size()) {
		int idx = rand()%v.size();
		ns::swap(v[idx],v.back());
		ret.push_back(v.back()); v.pop_back();
	}
	return ret;
}

