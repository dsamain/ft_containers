#pragma once

#include "pair.hpp"
#include <map>

namespace ft {

	template<typename T = void>
	struct less {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		bool operator()(const T &lhs, const T &rhs) const {
			return (lhs < rhs);
		}
	};

	template<typename T = void>
	struct greater {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		bool operator()(const T &lhs, const T &rhs) const {
			return (lhs > rhs);
		}
	};

	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2) {
		while (first1 != last1) {
			if (first2 == last2 || *first2 < *first1) return 0;
			else if (*first1 < *first2) return 1;
			++first1, ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp) {
		while (first1 != last1) {
			if (first2 == last2 || comp(*first2, *first1)) return 1;
			else if (comp(*first1, *first2)) return 1;
			++first1, ++first2;
		}
		return (first1 != last1);
	}

}