#pragma once

namespace ft {

		template<typename Iter>
	class rev_iterator {
	public:

	/*------------------Member type------------------*/

		typedef Iter iterator_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;


	/*------------------Constructor------------------*/

		rev_iterator() : _it() {}

		rev_iterator(const Iter &it) : _it(it) {}

		template<typename U>
		rev_iterator(const rev_iterator<U> &cpy) : _it(cpy.base()) {}

		rev_iterator &operator=(const rev_iterator &cpy) {
			_it = cpy._it;
			return *this;
		}

		~rev_iterator() {}

		iterator_type base() const {
			return _it;
		}


	/*------------------Access------------------*/

		reference operator*() const {return *(--iterator_type(_it));}

		pointer operator->() const {return &(this->operator*());}

        reference operator[](difference_type n) {return base()[-n-1];} 


	/*------------------Increment------------------*/

		rev_iterator &operator++() {--_it; return *this;}

		rev_iterator operator++(int) {
            rev_iterator out(*this);
            ++(*this);
            return out;
		}

		rev_iterator &operator--() {++_it; return *this;}
		
		rev_iterator operator--(int) {
            rev_iterator out(*this);
            --(*this);
            return out;
		}
	

	/*------------------Assigment------------------*/

        rev_iterator &operator +=(const int& n) {
            _it -= n;
            return *this;
        }
        rev_iterator &operator -=(const int& n) {
            _it += n;
            return *this;
        }


	/*------------------Arithmetic------------------*/

  		rev_iterator operator+(const int & n) {
			return rev_iterator(base() - n);
        }

		template<typename It>
        friend rev_iterator operator+(const int &n, const rev_iterator<It> &op) {
			return rev_iterator(op.base() - n);
        }

        rev_iterator operator-(const int &n) {
			return rev_iterator(base() + n);
        }

		template<typename It>
        friend rev_iterator operator-(const int &n, const rev_iterator<It> &op) {
			return rev_iterator(op.base() + n);
        }

        //difference_type operator-(const rev_iterator &op) {
        	//return op._it - _it;
        //}

		template<typename It1, typename It2>
        friend typename rev_iterator<It1>::difference_type operator-(const rev_iterator<It1> &x, const rev_iterator<It2> &y) {
			return y._it - x._it;
        }

	/*------------------Comparaison------------------*/

		//template <typename It1, typename It2> bool operator== (const rev_iterator<It1>& lhs,
				//const rev_iterator<It2>& rhs) {return (lhs.base() == rhs.base());}

		//template <typename It1, typename It2> bool operator!= (const rev_iterator<It1>& lhs,
				//const rev_iterator<It2>& rhs) {return (lhs.base() != rhs.base());}

		//template <typename It1, typename It2> bool operator< (const rev_iterator<It1>& lhs,
				//const rev_iterator<It2>& rhs) {return (lhs.base() < rhs.base());}

		//template <typename It1, typename It2> bool operator<= (const rev_iterator<It1>& lhs,
				//const rev_iterator<It2>& rhs) {return (lhs.base() <= rhs.base());}

		//template <typename It1, typename It2> bool operator> (const rev_iterator<It1>& lhs,
				//const rev_iterator<It2>& rhs) {return (lhs.base() > rhs.base());}

		//template <typename It1, typename It2> bool operator>= (const rev_iterator<It1>& lhs,
				//const rev_iterator<It2>& rhs) {return (lhs.base() >= rhs.base());}

	private:
		iterator_type _it;
	};

		template <typename It1, typename It2> bool operator==(const rev_iterator<It1>& lhs,
				const rev_iterator<It2>& rhs) {return (lhs.base() == rhs.base());}

		template <typename It1, typename It2> bool operator!=(const rev_iterator<It1>& lhs,
				const rev_iterator<It2>& rhs) {return (lhs.base() != rhs.base());}

		template <typename It1, typename It2> bool operator<(const rev_iterator<It1>& lhs,
				const rev_iterator<It2>& rhs) {return (lhs.base() > rhs.base());}

		template <typename It1, typename It2> bool operator<=(const rev_iterator<It1>& lhs,
				const rev_iterator<It2>& rhs) {return (lhs.base() >= rhs.base());}

		template <typename It1, typename It2> bool operator>(const rev_iterator<It1>& lhs,
				const rev_iterator<It2>& rhs) {return (lhs.base() < rhs.base());}

		template <typename It1, typename It2> bool operator>=(const rev_iterator<It1>& lhs,
				const rev_iterator<It2>& rhs) {return (lhs.base() <= rhs.base());}

}
