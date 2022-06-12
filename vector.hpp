#pragma once

#include "type_traits.hpp"
#include "algorithm.hpp"
#include "template_utils.hpp"
#include "vector_iterator.hpp"
#include "vector_rev_iterator.hpp"
#include <exception>

namespace ft {


    template<typename T, typename Alloc = std::allocator<T> >
    class vector {
    public:

	/*------------------Conversion------------------*/
	/*------------------Comparaison------------------*/
	/*------------------Increment------------------*/
	/*------------------Access------------------*/
	/*------------------Constructor------------------*/
	/*------------------Member type------------------*/
        /*      ALIAS       */

        typedef T value_type;
        typedef Alloc allocator_type;
        typedef int difference_type;
        typedef std::size_t size_type;

        typedef typename Alloc::reference reference;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::pointer pointer;
        typedef typename Alloc::const_pointer const_pointer;


        typedef typename ft::vector_iterator<T> iterator;
        typedef typename ft::vector_iterator<const T> const_iterator;
        typedef typename ft::vector_rev_iterator<iterator> reverse_iterator;
        typedef typename ft::vector_rev_iterator<const_iterator> const_reverse_iterator;

        

        		/*      *structor     */
        explicit vector (const allocator_type& alloc = allocator_type()) // Default
        : _alloc(alloc), _capacity(0), _size(0) {_arr = _alloc.allocate(0);}

        explicit vector (size_type n, const value_type& val = value_type(), // Value
                const allocator_type& alloc = allocator_type())
        : _alloc(alloc), _capacity(n), _size(n) {
            _arr = _alloc.allocate(_capacity);
            for (int i = 0; i < (int)_size; i++) {
                _alloc.construct(_arr + i, val);
            }
        }
		
		template <class InputIterator>
        vector (InputIterator first, InputIterator last, // Iterator
                const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type ah = 0) 
        : _alloc(alloc) {
			ah += 1;
			InputIterator tmp(first);
			int cnt = 0;
			while (tmp != last) tmp++, cnt++;
			_size = cnt;
			_capacity = cnt;
			_arr = _alloc.allocate(_capacity);
			for (int i = 0; first != last; i++)
				_alloc.construct(_arr + i, *first++);
		}

		vector(const vector &x) // Copy
		: _alloc(x._alloc), _capacity(x._capacity), _size(x._size) { 
        	_arr = _alloc.allocate(_capacity);
        	for (int i = 0; i < (int)_size; i++)
				_alloc.construct(_arr + i, *(x._arr + i));
		}

		~vector() {
			for (int i = 0 ; i < (int)_size; i++)
				_alloc.destroy(_arr + i);
			if (_capacity) {
				_alloc.deallocate(_arr, _capacity);
			}
		}
				/*		Member operator		*/
		vector &operator=(const vector &x) {
			clear();
			_alloc.deallocate(_arr, _capacity);
			_alloc = x._alloc;
			_capacity = x._capacity;
			_size = x._size;
			_arr = _alloc.allocate(_capacity);
			for (int i = 0; i < (int)_size; i++) {
				_alloc.construct(_arr + i, *(x._arr + i));
			}
			return *this;
		}
				/*		Capacity		*/
		size_type size() const {return _size;}
	
		void resize (size_type n, value_type val = value_type()) {
			while (_size > n)
				_alloc.destroy(_arr + --_size);
			if (n > _capacity) {
				int sz = ft::max(_capacity * 2, n);
				pointer tmp = _alloc.allocate(sz);
				for (int i = 0; i < (int)_size; i++) {
					_alloc.construct(tmp + i, *(_arr + i));
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr,_capacity);
				_capacity = sz;
				_arr = tmp;
			}
			while (_size < n)
				_alloc.construct(_arr + _size++, val);
		}

		size_type capacity() const {return _capacity;}

		size_type max_size() const {return _alloc.max_size();}

		bool empty() const {return !_size;}

		void reserve (size_type n) {
			if (n <= _capacity) return;
			pointer tmp = _alloc.allocate(n);
			for (int i = 0; i < (int)_size; i++) {
				_alloc.construct(tmp + i, *(_arr + i));
				_alloc.destroy(_arr + i);
			}
			_alloc.deallocate(_arr, _capacity);
			_arr = tmp;
			_capacity = n;
		}

        		/*      Element access		*/
        reference operator[] (size_type n) {return _arr[n];}

        const_reference operator[] (size_type n) const {return _arr[n];}

		reference at (size_type n) {
			if (n >= _size) throw std::out_of_range("vector");
			return _arr[n];
		}

		const_reference at (size_type n) const {
			if (n >= _size) throw std::out_of_range("vector");
			return _arr[n];
		}

		reference front() {return _arr[0];}

		const_reference front() const {return _arr[0];}

		reference back() {return _arr[_size-1];}

		const_reference back() const {return _arr[_size-1];}

        		/*      Modifiers		*/
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type tmp = 0) { // if is_integer<InputIt>::val == 0 , if_is::exist will not exist :)
			tmp += 1; // for the flag
			clear();
			int sz = ft::distance(first, last);
			if (sz > (int)_capacity)
				reserve(sz);
			while (first != last)
				_alloc.construct(_arr + _size++, *first++);
		}

		void assign (size_type n, const value_type &val) {clear(), resize(n, val);}

		void push_back (const value_type& val) {
				if (_size == _capacity) {
					pointer _tmp = _arr;
					_arr = _alloc.allocate(_capacity ? _capacity *= 2 : _capacity = 1);
					for (int i = 0 ; i < (int)_size; i++) {
						_alloc.construct(_arr + i, _tmp[i]);
						_alloc.destroy(_tmp + i);
					}
					if (_size)
						_alloc.deallocate(_tmp, _size);
				}
				_arr[_size++] = val;
		}

		void pop_back() {
			if (_size) {
				_alloc.destroy(_arr + _size - 1);
				_size--;
			}
		}

		iterator insert (iterator position, const value_type &val) {
			int gap = distance(begin(), position);
			insert(position, 1, val);
			return begin() + gap;
		}

    	void insert (iterator position, size_type n, const value_type& val) {
			if (_size + n > _capacity) {
				iterator it = begin();
				int sz = ft::max(_capacity * 2, _size + n), i=0;
				pointer tmp = _alloc.allocate(sz);

				for (; it != position; ++i, ++it) {
					_alloc.construct(tmp+i, *(_arr + i));
					_alloc.destroy(_arr + i);
				}
				for (size_type _=0; _ < n; ++_, ++i)
					_alloc.construct(tmp+i, val);
				while (position != end()) {
					_alloc.construct(tmp + i++, *position++);
					_alloc.destroy(_arr + i);
				}
				_alloc.deallocate(_arr, _capacity);
				_arr = tmp;
				_capacity = sz;
				_size += n;
			} else {
				iterator it = end()-1;
				int i = _size-1;

				for (; it >= position; i--, --it) {
					_alloc.construct(_arr+i+n, *(_arr+i));
					_alloc.destroy(_arr+i);
				}
				for (int j = i + n; j > i; j--) {
					_alloc.destroy(_arr+j);
					_alloc.construct(_arr+j, val);
				}
				_size += n;
			}
		}

		template <class InputIterator>
  		void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, bool>::type tmp = 0) {
			tmp += 1; // for flag
			int gap = distance(begin(), position);
			while (first != last)
				insert(iterator(begin()+gap++), *first), ++first;
  		}

		iterator erase (iterator first, iterator last) { // undefined when last < first;
			int gap = last - first;
			int beg = first - iterator(_arr);

			for (int i = beg; first < last || i < (int)_size; i++) {
				_alloc.destroy(&(*first++));
				if (i + gap < (int)_size)
					_alloc.construct(_arr + i, *(_arr + i + gap));
				first++;
			}
			_size -= gap;
			return iterator(_arr + beg);
		}			

		iterator erase (iterator position) {return erase(position, position + 1);}

		void swap (vector& x) {\
			ft::swap(_arr, x._arr);
			ft::swap(_alloc, x._alloc);
			ft::swap(_capacity, x._capacity);
			ft::swap(_size, x._size);
		}

		void clear() {
			for (int i = 0; i < (int)_size; i++)
				_alloc.destroy(_arr + i);
			_size = 0;	
		}

        		/*      Iterator        */
		iterator begin() {return iterator(_arr);}

		const_iterator begin() const {return const_iterator(_arr);}

		iterator end() {return iterator(_arr + _size);}

		const_iterator end() const {return const_iterator(_arr + _size);}

		reverse_iterator rbegin() {return reverse_iterator(iterator(_arr + _size));}

		const_reverse_iterator rbegin() const {return const_reverse_iterator(const_iterator(_arr + _size));}

		reverse_iterator rend() {return reverse_iterator(_arr - 1);}

		const_reverse_iterator rend() const {return const_reverse_iterator(_arr - 1);}

				/*		Non member overload		*/
  		friend bool operator==(const vector& lhs, const vector& rhs) {
			if (lhs.size() != rhs.size()) return 0;
			for (size_type i = 0; i < lhs.size(); i++)
				if (lhs[i] != rhs[i]) return 0;
			return 1;
		} 

  		friend bool operator!=(const vector& lhs, const vector& rhs) {
			return !(lhs == rhs);
		}

  		friend bool operator<(const vector& lhs, const vector& rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

  		friend bool operator<=(const vector& lhs, const vector& rhs) {
			return (lhs == rhs || lhs < rhs);
		}

  		friend bool operator>(const vector& lhs, const vector& rhs) {
			return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
		}

  		friend bool operator>=(const vector& lhs, const vector& rhs) {
			return (lhs == rhs || lhs > rhs);
		}
		
    private:
        pointer _arr;
        Alloc _alloc;
       	size_type _capacity;
        size_type _size;
    };

	template<typename T, typename Alloc>
  	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y) {x.swap(y);}

}