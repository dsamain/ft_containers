#pragma once

#include "node.hpp"
#include "template_utils.hpp"

namespace ft {

	template<typename Key, typename T, typename Compare, typename Alloc, typename Node, bool b>
	class map_iterator {
	public:

	/*------------------Member type------------------*/

		typedef std::bidirectional_iterator_tag iterator_category;
		typedef ft::pair<const Key, T> value_type;
		typedef long difference_type;
		typedef typename ft::isConst<b, value_type&, const value_type&>::type reference;
		typedef typename ft::isConst<b, value_type*, const value_type*>::type pointer;
	private:
		typedef typename ft::isConst<b, Node*, const Node*>::type nodePtr;
	public:


	/*------------------Constructor------------------*/

		map_iterator(const nodePtr ptr=NULL, const nodePtr last=NULL)
		: _ptr(ptr), _last(last), _comp(Compare()) {}

		map_iterator(const map_iterator &cpy)
		: _ptr(cpy._ptr), _last(cpy._last), _comp(cpy._comp) {}

		map_iterator &operator=(const map_iterator &cpy) {
			_ptr = cpy._ptr;
			_last = cpy._last;
			_comp = cpy._comp;
			return *this;
		}

		~map_iterator() {}

		
	/*------------------Access------------------*/

		reference operator*() const {return *_ptr->val;}
		pointer operator->() const {return &(**this);}


	/*------------------Increment------------------*/

		map_iterator &operator++() {
			if (_ptr->right) {
				_ptr = _ptr->right;
				while (_ptr->left) _ptr = _ptr->left;
			} else {
				value_type cur_val = *_ptr->val;	
				while (!_comp(cur_val.first, _ptr->val->first))
					_ptr = _ptr->par;
			}
			return *this;
		}

		map_iterator operator++(int) {
            map_iterator out(*this);
            ++(*this);
            return out;
		}

		map_iterator &operator--() {
			if (_ptr == _last)
				_ptr = _ptr->par;
			else if (_ptr->left) {
				_ptr = _ptr->left;
				while (_ptr->right) _ptr = _ptr->right;
			} else {
				value_type cur_val = *_ptr->val;	
				while (!_comp(_ptr->val->first, cur_val.first))
					_ptr = _ptr->par;
			}
			return *this;
		}
		
		map_iterator operator--(int) {
            map_iterator out(*this);
            --(*this);
            return out;
		}


	/*------------------Comparaison------------------*/

		friend bool operator==(const map_iterator &x, const map_iterator &y) {return (x._ptr == y._ptr);}
		friend bool operator!=(const map_iterator &x, const map_iterator &y) {return (x._ptr != y._ptr);}


	/*------------------Conversion------------------*/

		operator map_iterator<Key, T, Compare, Alloc, Node, 1> () {
			map_iterator<Key, T, Compare, Alloc, Node, 1> ret(_ptr, _last);
			return ret;
		}

	private:
		nodePtr _ptr;
		nodePtr _last;
		Compare _comp;
	};

}