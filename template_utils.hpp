#pragma once

namespace ft {

    template<bool b, typename F, typename T>
    struct isConst {};

    template<typename T, typename F>
    struct isConst<0, F, T> {
        typedef F type;
    };

    template<typename T, typename F>
    struct isConst<1, F, T> {
        typedef T type;
    };

	template<typename T>
	void swap(T &a, T &b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<typename T>
	T max(const T &a, const T &b) {
		if (a >= b) return a;
		return b;
	}

    template<typename T>
	T min(const T &a, const T &b) {
		if (a <= b) return a;
		return b;
	}

	template<typename T>
	int distance(T first, T end) {
		int cnt=0;
		while (first != end) {
			first++;
			cnt++;
		}
		return cnt;
	}

}