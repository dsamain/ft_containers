#pragma once

#include "../tree.hpp"
#include "../template_utils.hpp"

namespace ft {

	template<typename T, typename Compare, typename Alloc, typename Node, bool b>
	class bidirectional_iterator {
	public:

	/*------------------Member type------------------*/

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef long difference_type;
		typedef typename ft::isConst<b, value_type&, const value_type&>::type reference;
		typedef typename ft::isConst<b, value_type*, const value_type*>::type pointer;
	private:
		typedef typename ft::isConst<b, Node*, const Node*>::type nodePtr;
	public:


	/*------------------Constructor------------------*/

		bidirectional_iterator(const nodePtr ptr=NULL, const nodePtr last=NULL)
		: _ptr(ptr), _last(last), _comp(Compare()) {}

		bidirectional_iterator(const bidirectional_iterator &cpy)
		: _ptr(cpy._ptr), _last(cpy._last), _comp(cpy._comp) {}

		bidirectional_iterator &operator=(const bidirectional_iterator &cpy) {
			_ptr = cpy._ptr;
			_last = cpy._last;
			_comp = cpy._comp;
			return *this;
		}

		~bidirectional_iterator() {}

		
	/*------------------Access------------------*/

		reference operator*() const {return  _ptr->val;}
		pointer operator->() const {return &(**this);}


	/*------------------Increment------------------*/

		bidirectional_iterator &operator++() {
			if (_ptr->right) {
				_ptr = _ptr->right;
				while (_ptr->left) _ptr = _ptr->left;
			} else {
				value_type cur_val = _ptr->val;	
				while (!_comp(cur_val, _ptr->val))
					_ptr = _ptr->par;
			}
			return *this;
		}

		bidirectional_iterator operator++(int) {
            bidirectional_iterator out(*this);
            ++(*this);
            return out;
		}

		bidirectional_iterator &operator--() {
			if (_ptr == _last)
				_ptr = _ptr->par;
			else if (_ptr->left) {
				_ptr = _ptr->left;
				while (_ptr->right) _ptr = _ptr->right;
			} else {
				value_type cur_val =  _ptr->val;	
				while (!_comp( _ptr->val, cur_val))
					_ptr = _ptr->par;
			}
			return *this;
		}
		
		bidirectional_iterator operator--(int) {
            bidirectional_iterator out(*this);
            --(*this);
            return out;
		}


	/*------------------Comparaison------------------*/

		friend bool operator==(const bidirectional_iterator &x, const bidirectional_iterator &y) {return (x._ptr == y._ptr);}
		friend bool operator!=(const bidirectional_iterator &x, const bidirectional_iterator &y) {return (x._ptr != y._ptr);}


	/*------------------Conversion------------------*/

		operator bidirectional_iterator<T, Compare, Alloc, Node, true> () {
			return bidirectional_iterator<T, Compare, Alloc, Node, true> (_ptr, _last);
		}

	private:
		nodePtr _ptr;
		nodePtr _last;
		Compare _comp;
	};



}
