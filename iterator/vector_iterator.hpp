#pragma once

namespace ft {


    template<typename T>
    class vector_iterator {
    public:

	/*------------------Member type------------------*/

        typedef T value_type;
        typedef int difference_type;
        typedef T* pointer;
        typedef T&  reference;
        typedef std::random_access_iterator_tag  iterator_category;


	/*------------------Constructor------------------*/

        vector_iterator(pointer ptr=NULL) {_ptr = ptr;}

        vector_iterator(const vector_iterator &cpy) {_ptr = cpy._ptr;}

        vector_iterator &operator=(const vector_iterator &cpy) {
            _ptr = cpy._ptr;
			return *this;
        }


	/*------------------Comparaison------------------*/

        friend bool operator==(const vector_iterator &a, const vector_iterator &b) {return a._ptr == b._ptr;}
        friend bool operator!=(const vector_iterator &a, const vector_iterator &b) {return a._ptr != b._ptr;}
        friend bool operator<(const vector_iterator &a, const vector_iterator &b) {return a._ptr < b._ptr;}
        friend bool operator<=(const vector_iterator &a, const vector_iterator &b) {return a._ptr <= b._ptr;}
        friend bool operator>(const vector_iterator &a, const vector_iterator &b) {return a._ptr > b._ptr;}
        friend bool operator>=(const vector_iterator &a, const vector_iterator &b) {return a._ptr >= b._ptr;}


	/*------------------Access------------------*/

        reference operator*() {return *_ptr;}
        pointer operator->() {return _ptr;}
        reference operator[](difference_type n) {return *(_ptr + n);} 


	/*------------------Increment------------------*/

        vector_iterator &operator++() {
            ++_ptr;
            return (*this);
        }
        vector_iterator &operator--() {
            _ptr--;
            return (*this);
        }
        vector_iterator operator++(int) {
            vector_iterator out(*this);
            ++(*this);
            return out;
        }
        vector_iterator operator--(int) {
            vector_iterator out(*this);
            --(*this);
            return out;
        }


	/*------------------Assignement------------------*/

        vector_iterator &operator +=(const int& n) {
            _ptr += n;
            return *this;
        }
        vector_iterator &operator -=(const int& n) {
            _ptr -= n;
            return *this;
        }


	/*------------------Arithmetic------------------*/

        vector_iterator operator+(const int & n) {
            vector_iterator out(*this);
            out += n;
            return out;
        }
        friend vector_iterator operator+(const int &n, const vector_iterator &op) {
            vector_iterator out(op);
            out += n;
            return out;
        }
        vector_iterator operator-(const int &n) {
            vector_iterator out(*this);
            out -= n;
            return out;
        }

        difference_type operator-(const vector_iterator &op) {
            return _ptr - op._ptr;
        }
		
		friend difference_type operator-(const vector_iterator &a, const vector_iterator &b) {
            return a._ptr - b._ptr;
        }


	/*------------------Conversion------------------*/

		operator vector_iterator<const T>() const {
			vector_iterator<const T> out(_ptr);
			return out;
		}

    private:
        T *_ptr;
    };

}