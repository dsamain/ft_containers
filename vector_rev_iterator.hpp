#pragma once

namespace ft {

    //template<typename T, typename Alloc> class vector;

    template<typename Iterator>
    class vector_rev_iterator {
    public:
        /*      ALIAS       */

		typedef Iterator iterator_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;

        		/*      Constructor     */

        vector_rev_iterator(const pointer ptr=NULL) : _ptr(ptr) {}

		explicit vector_rev_iterator(Iterator it) {
			_ptr = &(*it)-1;
		}

		//template <class T> friend class	reverse_iterator;
  		vector_rev_iterator (const vector_rev_iterator<Iterator> &cpy) {
			_ptr = cpy._ptr;
		}

		template <typename T> 
  		vector_rev_iterator(vector_rev_iterator<T> &cpy) {
			_ptr = &(*cpy);
		}

		//template <class Iterator>

        vector_rev_iterator &operator=(const vector_rev_iterator &cpy) {
            _ptr = cpy._ptr;
			return *this;
        }

		Iterator base() {
			return Iterator(_ptr + 1);
		}

                            /*      Operator        */
        // Comparaison
        //bool operator==(const vector_rev_iterator &op) const {return _ptr == op._ptr;}
        template<typename T> bool operator==(vector_rev_iterator<T> &op) {return _ptr == &(*op);}
        template<typename T> bool operator!=(vector_rev_iterator<T> &op) {return _ptr != &(*op);}
        template<typename T> bool operator<(vector_rev_iterator<T> &op) {return _ptr > &(*op);}
        template<typename T> bool operator<=(vector_rev_iterator<T> &op) {return _ptr >= &(*op);}
        template<typename T> bool operator>(vector_rev_iterator<T> &op) {return _ptr < &(*op);}
        template<typename T> bool operator>=(vector_rev_iterator<T> &op) {return _ptr <= &(*op);}
        friend bool operator==(const vector_rev_iterator &a, const vector_rev_iterator &b) {return a._ptr == b._ptr;}
        friend bool operator!=(const vector_rev_iterator &a, const vector_rev_iterator &b) {return a._ptr != b._ptr;}
        friend bool operator<(const vector_rev_iterator &a, const vector_rev_iterator &b) {return a._ptr > b._ptr;}
        friend bool operator<=(const vector_rev_iterator &a, const vector_rev_iterator &b) {return a._ptr >= b._ptr;}
        friend bool operator>(const vector_rev_iterator &a, const vector_rev_iterator &b) {return a._ptr < b._ptr;}
        friend bool operator>=(const vector_rev_iterator &a, const vector_rev_iterator &b) {return a._ptr <= b._ptr;}

        // Member access
        reference operator*() {return *_ptr;}
        pointer operator->() {return _ptr;}
        reference operator[](difference_type n) {return *(_ptr - n);} 

        // Increment
        vector_rev_iterator &operator++() {
            _ptr--;
            return (*this);
        }
        vector_rev_iterator &operator--() {
            _ptr++;
            return (*this);
        }
        vector_rev_iterator operator++(int) {
            vector_rev_iterator out(*this);
            ++(*this);
            return out;
        }
        vector_rev_iterator operator--(int) {
            vector_rev_iterator out(*this);
            --(*this);
            return out;
        }

        // Assignement
        vector_rev_iterator &operator +=(const int& n) {
            _ptr -= n;
            return *this;
        }
        vector_rev_iterator &operator -=(const int& n) {
            _ptr += n;
            return *this;
        }

        // Arithmetic
        vector_rev_iterator operator+(const int & n) {
            vector_rev_iterator out(*this);
            out += n;
            return out;
        }
        friend vector_rev_iterator operator+(const int &n, const vector_rev_iterator &op) {
            vector_rev_iterator out(op);
            out += n;
            return out;
        }
        vector_rev_iterator operator-(const int &n) {
            vector_rev_iterator out(*this);
            out -= n;
            return out;
        }

        difference_type operator-(const vector_rev_iterator &op) {
        	return op._ptr -_ptr;
        }
		

		// Conversion
		operator vector_rev_iterator<vector_iterator<const value_type> >() const {
			vector_rev_iterator<vector_iterator<const value_type> > out(_ptr);
			return out;
		}

    private:
        pointer _ptr;

    };

}