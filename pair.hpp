#pragma once

namespace ft {

	template<typename T1, typename T2>
	struct pair {

		typedef T1 first_type;
		typedef T2 second_type;

		pair() : first(first_type()), second(second_type()) {}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		template<typename U1, typename U2>
		pair(const pair<U1,U2> &cpy) : first(first_type(cpy.first)), second(second_type(cpy.second)) {}

		pair &operator=(const pair &cpy) {
			first = cpy.first;
			second = cpy.second;
			return *this;
		}

		operator pair<const T1, const T2>() const {
			pair<const T1,const T2> ret(ret.first, ret.second);
			return ret;
		}

		~pair() {}

		void swap(pair &pr) {
			swap(first, pr.first);
			swap(second, pr.second);
		}


		T1 first;
		T2 second;
	};

	// Non member overload
	template<typename T1, typename T2>
	bool operator==(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) {
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template<typename T1, typename T2>
	bool operator!=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) {
		return (!(lhs == rhs));
	}

	template<typename T1, typename T2>
	bool operator<(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) {
		if (lhs.first == rhs.first)
			return (lhs.second < rhs.second);	
		return (lhs.first < rhs.first);
	}

	template<typename T1, typename T2>
	bool operator<=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) {
		if (lhs.first == rhs.first)
			return (lhs.second <= rhs.second);	
		return (lhs.first < rhs.first);
	}

	template<typename T1, typename T2>
	bool operator>(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) {
		if (lhs.first == rhs.first)
			return (lhs.second > rhs.second);	
		return (lhs.first > rhs.first);
	}

	template<typename T1, typename T2>
	bool operator>=(const pair<T1,T2> &lhs, const pair<T1,T2> &rhs) {
		if (lhs.first == rhs.first)
			return (lhs.second >= rhs.second);	
		return (lhs.first > rhs.first);
	}

	template<typename T1, typename T2>
	void swap(pair<T1,T2> &x, pair<T1,T2> &y) {
		std::swap(x.first, y.first);
		std::swap(x.second, y.second);
	}

	// GET 

}