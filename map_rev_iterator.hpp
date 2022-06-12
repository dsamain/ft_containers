#pragma once

#include "node.hpp"

namespace ft {

		template<typename Iter>
	class map_rev_iterator {
	public:

	/*------------------Member type------------------*/

		typedef Iter iterator_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;


	/*------------------Constructor------------------*/

		map_rev_iterator() : _it() {}

		map_rev_iterator(const Iter &it) : _it(it) {}

		template<typename U>
		map_rev_iterator(const map_rev_iterator<U> &cpy) : _it(cpy.base()) {}

		map_rev_iterator &operator=(const map_rev_iterator &cpy) {
			_it = cpy._it;
			return *this;
		}

		~map_rev_iterator() {}

		iterator_type base() const {
			iterator_type ret(_it);
			//++ret;
			return ret;
		}


	/*------------------Access------------------*/

		reference operator*() const {return *(--iterator_type(_it));}
		pointer operator->() const {return &(this->operator*());}


	/*------------------Increment------------------*/

		map_rev_iterator &operator++() {--_it; return *this;}

		map_rev_iterator operator++(int) {
            map_rev_iterator out(*this);
            ++(*this);
            return out;
		}

		map_rev_iterator &operator--() {++_it; return *this;}
		
		map_rev_iterator operator--(int) {
            map_rev_iterator out(*this);
            --(*this);
            return out;
		}


	/*------------------Comparaison------------------*/

		friend bool operator==(const map_rev_iterator &x, const map_rev_iterator &y) {return (x._it == y._it);}
		friend bool operator!=(const map_rev_iterator &x, const map_rev_iterator &y) {return (x._it != y._it);}

	private:
		iterator_type _it;
	};

}
