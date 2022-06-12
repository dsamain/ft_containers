/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:36:16 by dsamain           #+#    #+#             */
/*   Updated: 2022/06/12 06:39:49 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"
#include "node.hpp"
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
			/*		Member type		*/
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
		typedef long size_type;
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

		/*#######################################################################*/

				/*		*structor		*/
		explicit map(const key_compare &comp = key_compare(),
              const allocator_type &alloc = allocator_type())
		: _size(0), _alloc(alloc), _first(0, value_type()), _last(0, value_type()), _key_comp(comp), _comp(comp) {
			_root = &_last;

		}		

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type())
	   : _size(0), _alloc(alloc), _first(0, value_type()), _last(0, value_type()), _key_comp(comp), _comp(comp) {
			insert(first, last);
	   }

		map(const map &cpy)
		: _size(0), _alloc(cpy._alloc), _first(0, value_type()), _last(0, value_type()), _key_comp(cpy._key_comp), _comp(cpy._comp) {
			_root = &_last;
			this->insert(cpy.begin(), cpy.end());
		}

		~map() {destruct(_root);}

		map& operator=(const map& cpy) { 
			_key_comp = cpy._key_comp;
			_comp = cpy._comp;
			this->clear();
			this->insert(cpy.begin(), cpy.end());
			return *this;
		}

		allocator_type get_allocator() const {return allocator_type();}

		// Iterator	
		iterator end() {return iterator(&_last, &_first, &_last);}
		const_iterator end() const {return const_iterator(&_last, &_first, &_last);}

		iterator begin() {
			nodePtr cur = _root;
			while (cur->left && cur->left != &_first) cur = cur->left;
			return iterator(cur, &_first, &_last);
		}
		
		const_iterator begin() const {
			nodePtr cur = _root;
			while (cur->left && cur->left != &_first) cur = cur->left;
			return const_iterator(cur, &_first, &_last);
		}

		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}

				/*		Capacity		*/
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

				/*		Modifiers		*/
		ft::pair<iterator, bool> insert(const value_type &val) {
			if (!_size) {
				_last.par = _nodeAlloc.allocate(1);
				_nodeAlloc.construct(_last.par, val);
				_root = _last.par;
				_root->right = &_last;
				_root->left = &_first;
				_size++;
				return ft::make_pair(iterator(_root, &_first, &_last), (bool)1);
			}
			nodePtr cur = _root, prev;
			while (cur && cur != &_last && cur != &_first) {
				prev = cur;
				if (val.first == cur->val->first)
					return ft::make_pair(iterator(cur, &_first, &_last), (bool)0);
				if (_comp(val, *cur->val)) cur = cur->left;
				else cur = cur->right;
			}
			nodePtr tmp = _nodeAlloc.allocate(1);		
			_nodeAlloc.construct(tmp, val);
			if (_comp(val, *prev->val)) prev->left = tmp;
			else prev->right = tmp;
			tmp->par = prev;
			if (cur == &_last) {
				_last.par = tmp;
				tmp->right = &_last;
			} else if (cur == &_first) {
				_first.par = tmp;
				tmp->left = &_first;
			}
			_size++;
			return ft::make_pair(iterator(tmp, &_first, &_last), (bool)1);
		}

		iterator insert (iterator position, const value_type& val) {
			ft::pair<iterator, bool> ret; ret.first = position;
			ret = insert(val);
			return ret.first;
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {while (first != last) insert(*first++);}

		/*
			add _begin to insert and keep it like this[X]
			make val a pointer in node so it's value can be swapped
			finish iterator
			test insert
			add rbt recoloring and rotation at the end of insert
			add search operation 
			then ~= done
		*/

		// find node then swap node until it has no more than one child

		void erase (iterator position) {erase(position->first);}

		size_type erase( const Key& key ) {
			if (!_size) return 0;
			nodePtr cur = _root;
			while (cur && cur->val->first != key && cur != &_first && cur != &_last) {
				if (_key_comp(key, cur->val->first)) cur = cur->left;
				else cur = cur->right;
			}
			if (!cur || cur == &_first || cur == &_last) return 0;
			if ((cur->left && cur->left != &_first) && (cur->right && cur->right != &_last)) {
				//std::cout << "case3" << std::endl;
				nodePtr suc = cur->right;
				while (suc->left && suc->left != &_first)
					suc = suc->left;
				ft::swap(suc->val, cur->val);
				cur = suc;
			}

			if ((!cur->left || cur->left == &_first) && (!cur->right || cur->right == &_last)) {
				//std::cout << "case1" << std::endl;
				if (cur->par) {
					if (cur->par->left == cur)
						cur->par->left = cur->left;
					if (cur->par->right == cur)
						cur->par->right = cur->right;
				}
				if (cur->left) cur->left->par = cur->par;
				if (cur->right) cur->right->par = cur->par;
				if (_root == cur) _root = &_last;
				_nodeAlloc.destroy(cur);
				_nodeAlloc.deallocate(cur,1);
			}
			else if ((cur->left && cur->left != &_first) || (cur->right && cur->right != &_last)) {
				//std::cout << "case2\n";
				nodePtr newChild;
				if (cur->left && cur->left != &_first)
					newChild = cur->left;
				else
					newChild = cur->right;
				newChild->par = cur->par;
				if (cur->par) {
					if (cur->par->left == cur) cur->par->left = newChild;
					else cur->par->right = newChild;
				}
				if (_root == cur) _root = newChild;
				//replace _first && _last
				if (_first.par == cur) {
					nodePtr p = _root;
					while (p->left && p->left != &_first) 
						p = p->left;
					_first.par = p;
					p->left = &_first;
				}
				if (_last.par == cur) {
					nodePtr p = _root;
					while (p->right && p->right != &_last)
						p = p->right;
					_last.par = p;
					p->right = &_last;
				}
				_nodeAlloc.destroy(cur);
				_nodeAlloc.deallocate(cur,1);
			} 
			_size--;
			return 1;
		}

		void erase (iterator first, iterator last) {while (first != last) erase(first++);}

		void clear() {
			destruct(_root);
			_last.par = NULL;
			_first.par = NULL;
			_root = &_last;
			_size = 0;
		}


	private:

			/* Private member type */
		typedef node<value_type>* nodePtr;


			/* Private function */
		void destruct(nodePtr cur) {
			if (!cur || cur == &_first || cur == &_last) return;
			destruct(cur->left);
			destruct(cur->right);
			_nodeAlloc.destroy(cur);
			_nodeAlloc.deallocate(cur, 1);
		}

		void nodeValueSwap(nodePtr x, nodePtr y) {
			ft::swap(x->par, y->par);
			ft::swap(x->left, y->left);
			ft::swap(x->right, y->right);
			ft::swap(x->col, y->col);

		}

			/* Atributs */
		size_type _size;
		size_type _max_size;
		Alloc _alloc;
		std::allocator<node<value_type> > _nodeAlloc;
		node<value_type> _first;
		node<value_type> _last;
		node<value_type> *_root;
		key_compare _key_comp;
		value_compare _comp;
		




	};

}