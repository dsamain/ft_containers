#pragma once

#include "node.hpp"

namespace ft {

		template<typename Iter>
	class map_rev_iterator {
	public:

				/*		Member type		*/	
		typedef Iter iterator_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;

				/*		Constructor		*/
		map_rev_iterator(const Iter &it) : _it(it) {--_it;}

		map_rev_iterator(const map_rev_iterator &cpy) : _it(cpy._it) {}

		map_rev_iterator &operator=(const map_rev_iterator &cpy) {
			_it = cpy._it;
			return *this;
		}

		~map_rev_iterator() {}

		// Access
		value_type &operator*() const {return *_it;}
		value_type *operator->() const {return &(*_it);}

		// Increment
		void operator++() {--_it;}

		map_rev_iterator operator++(int) {
            map_rev_iterator out(*this);
            ++(*this);
            return out;
		}

		void operator--() {--_it;}
		
		map_rev_iterator operator--(int) {
            map_rev_iterator out(*this);
            --(*this);
            return out;
		}

		// Comparaison
		friend bool operator==(const map_rev_iterator &x, const map_rev_iterator &y) {return (x._it == y._it);}
		friend bool operator!=(const map_rev_iterator &x, const map_rev_iterator &y) {return (x._it != y._it);}

	private:
		iterator_type _it;
	};

}
