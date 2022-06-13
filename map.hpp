/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:36:16 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/12 11:43:35 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "node.hpp"
#include "pair.hpp"
#include "map_iterator.hpp"
#include "map_rev_iterator.hpp"
#include "template_utils.hpp"
#include "algorithm.hpp"
#include <math.h>

namespace ft {

	template<typename Key,
		typename T,
		typename Compare = ft::less<Key>,
		typename Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:

	/*------------------Member type------------------*/

		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference ;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::pointer const_pointer;
		typedef long difference_type;
		typedef unsigned long size_type;
		class value_compare {
			friend class map;
		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type &x, const value_type &y) const {return comp(x.first, y.first);}
		protected:
			value_compare(Compare c) : comp(c) {}
			Compare comp;
		};

		typedef map_iterator<const Key, T, Compare, Alloc, node<value_type>, 0> iterator;
		typedef map_iterator<const Key, T, Compare, Alloc, node<value_type>, 1> const_iterator;
		typedef map_rev_iterator<iterator> reverse_iterator;
		typedef map_rev_iterator<const_iterator> const_reverse_iterator;


	/*------------------Constructor------------------*/

		explicit map(const key_compare &comp = key_compare(),
              const allocator_type &alloc = allocator_type())
		: _size(0), _alloc(alloc), _last(0, value_type()), _keyComp(comp), _comp(comp) {
			_root = &_last;

		}		

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type())
	   : _size(0), _alloc(alloc), _last(0, value_type()), _keyComp(comp), _comp(comp) {
			insert(first, last);
	   }

		map(const map &cpy)
		: _size(0), _alloc(cpy._alloc), _last(0, value_type()), _keyComp(cpy._keyComp), _comp(cpy._comp) {
			_root = &_last;
			this->insert(cpy.begin(), cpy.end());
		}

		~map() {destruct(_root);}

		map& operator=(const map& cpy) { 
			_keyComp = cpy._keyComp;
			_comp = cpy._comp;
			this->clear();
			this->insert(cpy.begin(), cpy.end());
			return *this;
		}

	/*------------------Iterator------------------*/

		iterator end() {return iterator(&_last, &_last);}
		const_iterator end() const {return const_iterator(&_last, &_last);}

		iterator begin() {
			nodePtr cur = _root;
			while (cur->left) cur = cur->left;
			return iterator(cur, &_last);
		}
		
		const_iterator begin() const {
			nodePtr cur = _root;
			while (cur->left) cur = cur->left;
			return const_iterator(cur, &_last);
		}

		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}


	/*------------------Capacity------------------*/

		bool empty() const {return (!_size);}

		size_type size() const {return _size;}

		typedef struct				s_node
		{
			ft::pair<const Key, T>	data;
			bool					color;
			struct s_node *			left;
			struct s_node *			right;
			struct s_node *			parent;
		} tmp_node;

		size_type max_size() const {
			typename Alloc::template rebind<tmp_node>::other tmp;
			return tmp.max_size();
		}


	/*------------------Element Acces------------------*/

	mapped_type& operator[] (const key_type& k) {
		return (*((insert(ft::make_pair(k,mapped_type()))).first)).second ;
	}

	/*------------------Modifiers------------------*/

		ft::pair<iterator, bool> insert(const value_type &val) {
			if (!_size)
				return ft::make_pair(iterator(insertLeafNode(NULL, val), &_last), (bool)1);
			nodePtr cur = _root, prev;
			while (cur && cur != &_last) {
				prev = cur;
				if (val.first == cur->val->first)
					return ft::make_pair(iterator(cur, &_last), (bool)0);
				if (_comp(val, *cur->val)) cur = cur->left;
				else cur = cur->right;
			}
			return ft::make_pair(iterator(insertLeafNode(prev, val), &_last), (bool)1);
		}

		iterator insert (iterator position, const value_type& val) {
			ft::pair<iterator, bool> ret; ret.first = position;
			ret = insert(val);
			return ret.first;
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {while (first != last) insert(*first++);}

		void erase (iterator position) {erase(position->first);}

		size_type erase( const Key& key ) {
			nodePtr cur = _root;

			while (cur && cur->val->first != key && cur != &_last)
				cur = (_keyComp(key, cur->val->first) ? cur->left : cur->right);

			if (!cur || cur == &_last) return 0;

			if (cur->left && (cur->right && cur->right != &_last)) { // if node have two children, find successor and swap (should not affect nodes color)
				nodePtr successor = cur->right;
				while (successor->left)
					successor = successor->left;
				ft::swap(successor->val, cur->val);
				cur = successor;
			}
			eraseNode(cur);
			return 1;
		}

		void erase (iterator first, iterator last) {while (first != last) erase(first++);}

		void swap (map &x) {
			ft::swap(_size, x._size);
			ft::swap(_root, x._root);
			ft::swap(_last.par, x._last.par);	
			_last.par->right = &_last;
			x._last.par->right = &x._last;
		}

		friend void swap (map &x, map &y) {x.swap(y);}

		void clear() {
			destruct(_root);
			_last.par = NULL;
			_root = &_last;
			_size = 0;
		}


	/*------------------Observers------------------*/

	key_compare key_comp() const {return _keyComp;}
	value_compare value_comp() const {return _comp;}


	/*------------------Finder------------------*/

	iterator find (const key_type& k) {
		iterator ret = lower_bound(k);
		return (ret == end() || ret->first != k ? end() : ret);
	}

	const_iterator find (const key_type& k) const {
		const_iterator ret = lower_bound(k);
		return (ret == end() || ret->first != k ? end() : ret);
	}

	size_type count (const key_type& k) const {return (find(k) != end());}

	iterator lower_bound (const key_type& k) {
		nodePtr cur = _root, res = NULL;
		while (cur && cur != &_last)
			if (_keyComp(cur->val->first, k))
				cur = cur->right;
			else
				res = cur, cur = cur->left;
		return ((res && res != &_last) ? iterator(res, &_last) : end());
	}

	const_iterator lower_bound (const key_type& k) const {
		nodePtr cur = _root, res = NULL;
		while (cur && cur != &_last)
			if (_keyComp(cur->val->first, k))
				cur = cur->right;
			else
				res = cur, cur = cur->left;
		return (res ? const_iterator(res, &_last) : end());
	}

	iterator upper_bound (const key_type& k) {
		iterator ret = lower_bound(k);
		if (ret != end() && ret->first == k) ++ret;
		return ret;
	}
	const_iterator upper_bound (const key_type& k) const {
		const_iterator ret = lower_bound(k);
		if (ret != end() && ret->first == k) ++ret;
		return ret;
	}

	pair<iterator,iterator>             equal_range (const key_type& k) {return ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k));}
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const  {return ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));}

	/*------------------Allocator------------------*/

	allocator_type get_allocator() const;

	/*------------------Comparaison------------------*/

	friend bool operator==(const map &l, const map &r) {
		const_iterator it = l.begin();
		const_iterator it2 = r.begin();
		while (it != l.end())
			if (*it++ != *it2++)
				return 0;
		return (it2 == r.end());
	}

	friend bool operator!=(const map &l, const map &r) {return !(l == r);}
	friend bool operator<(const map &l, const map &r) {return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());}
	friend bool operator<=(const map &l, const map &r) {return (l < r || l == r);}
	friend bool operator>(const map &l, const map &r) {return ft::lexicographical_compare(r.begin(), r.end(), l.begin(), l.end());}
	friend bool operator>=(const map &l, const map &r) {return (l > r || l == r);}

	private:
		size_type _size;
		Alloc _alloc;
		std::allocator<node<value_type> > _nodeAlloc;
		node<value_type> _last;
		node<value_type> *_root;
		key_compare _keyComp;
		value_compare _comp;

		// Private member type
		typedef node<value_type>* nodePtr;


		// Private function
		nodePtr newNode(const value_type &val) {
			nodePtr ret = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(ret, val);
			return ret;
		}

		void deleteNode(nodePtr nd) {
			_nodeAlloc.destroy(nd);
			_nodeAlloc.deallocate(nd, 1);
		}

		nodePtr insertLeafNode(nodePtr par, const value_type &val) {
			if (par && ((par->left) && (par->right && par->right != &_last))) return NULL; // should be ok if remove (check if node will be leaf)
			nodePtr nd = newNode(val);
			if (!par) {
				_root = nd;
				_last.par = _root;
				_root->right = &_last;
				_size++;
				return _root;
			} else {
				if (_comp(*par->val, *nd->val)) {
					if (par->right == &_last) {
						_last.par = nd;
						nd->right = &_last;
					}
					par->right = nd;
				} else {
					par->left = nd;
				}
				nd->par = par;
			}
			_size++;
			return nd;
		}

		void eraseNode(nodePtr nd) {
			nodePtr newChild = NULL;

			if (nd->left)
				newChild = nd->left;
			else if (nd->right && nd->right != &_last)
				newChild = nd->right;

			if (nd->par)
				if (nd->par->left == nd)
					nd->par->left = newChild;
				else
					nd->par->right = newChild;

			if (newChild) newChild->par = nd->par;

			if (_root == nd)  _root = (newChild ? newChild : &_last);

			if (_last.par == nd) {
				nodePtr p = _root;
				while (p->right && p->right != &_last)
					p = p->right;
				_last.par = p;
				p->right = &_last;
			}

			deleteNode(nd);
			_size--;
		}

		void destruct(nodePtr cur) {
			if (!cur || cur == &_last) return;
			destruct(cur->left);
			destruct(cur->right);
			deleteNode(cur);
		}
	};

}