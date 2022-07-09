#pragma once

#include "vector.hpp"

namespace ft {

	template <typename T, typename Container = ft::vector<T> >
	class stack {

		/*------------------Member type------------------*/

	protected:
		Container c;
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		/*------------------Constructor------------------*/

		explicit stack(const container_type &cont = Container()) : c(cont) {}

		stack(const stack &cpy) : c(cpy.c) {}

		~stack() {}

		stack &operator=(const stack &cpy) {
			this->c = cpy.c;
			return *this;
		}
	

		/*------------------Element access------------------*/

		reference top() {return this->c.back();}
		const_reference top() const {return this->c.back();}


		/*------------------Capacity------------------*/

		bool empty() const {return this->c.empty();}
		size_type size() const {return this->c.size();}


		/*------------------Modifiers------------------*/

		void push(const value_type &val) {this->c.push_back(val);}
		void pop() {this->c.pop_back();}


		/*------------------Comparator------------------*/

		friend bool operator==(const stack &lhs, const stack &rhs) {return lhs.c == rhs.c;}
		friend bool operator!=(const stack &lhs, const stack &rhs) {return lhs.c != rhs.c;}
		friend bool operator<(const stack &lhs, const stack &rhs) {return lhs.c < rhs.c;}
		friend bool operator<=(const stack &lhs, const stack &rhs) {return lhs.c <= rhs.c;}
		friend bool operator>(const stack &lhs, const stack &rhs) {return lhs.c > rhs.c;}
		friend bool operator>=(const stack &lhs, const stack &rhs) {return lhs.c >= rhs.c;}


	private:
	};

}