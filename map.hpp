/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsamain <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:36:16 by dsamain           #+#    #+#             */
/*   Updated: 2022/07/10 08:29:38 by dsamain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "tree.hpp"


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
			value_compare(const key_compare &c = Compare()) : comp(c) {}
			value_compare(const value_compare &cpy) : comp(cpy.comp) {}
		protected:
			Compare comp;
		};

	private:
		typedef tree<value_type, value_compare, allocator_type> tree_type;
	public:
		typedef typename tree_type::iterator iterator;
		typedef typename tree_type::const_iterator const_iterator;
		typedef rev_iterator<iterator> reverse_iterator;
		typedef rev_iterator<const_iterator> const_reverse_iterator;	


	/*------------------Constructor------------------*/

		explicit map(const key_compare &comp = key_compare(),
              const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _keyComp(comp), _comp(comp), _tree(value_compare(comp)) {}		

		template <class InputIterator>
  		map (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type())
	   : _alloc(alloc), _keyComp(comp), _comp(comp), _tree(value_compare(comp)) {
			insert(first, last);
	   }

		map(const map &cpy)
		: _alloc(cpy._alloc), _keyComp(cpy._keyComp), _comp(cpy._comp), _tree(value_compare(cpy._comp)) {
			this->insert(cpy.begin(), cpy.end());
		}

		~map() {}

		map& operator=(const map& cpy) { 
			_keyComp = cpy._keyComp;
			_comp = cpy._comp;
			this->clear();
			this->insert(cpy.begin(), cpy.end());
			return *this;
		}


	/*------------------Iterator------------------*/

		iterator end() {return _tree.end();}
		const_iterator end() const {return _tree.end();}

		iterator begin() {return _tree.begin();}
		const_iterator begin() const {return _tree.begin();}
		
		reverse_iterator rbegin() {return reverse_iterator(end());}
		const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
		reverse_iterator rend() {return reverse_iterator(begin());}
		const_reverse_iterator rend() const {return const_reverse_iterator(begin());}


	/*------------------Capacity------------------*/

		bool empty() const {return _tree.empty();}

		size_type size() const {return _tree.size();}

		size_type max_size() const {return _tree.max_size();}


	/*------------------Element Acces------------------*/

	mapped_type& operator[] (const key_type& k) {
		return (*((insert(ft::make_pair(k,mapped_type()))).first)).second ;
	}

	/*------------------Modifiers------------------*/

		ft::pair<iterator, bool> insert(const value_type &val) {
			ft::pair<typename tree_type::nodePtr, bool> ret = _tree.insert(val);
			return ft::make_pair(iterator(ret.first, _tree.getLast()), ret.second);
		}

		iterator insert (iterator position, const value_type& val) {
			ft::pair<iterator, bool> ret; ret.first = position;
			ret = insert(val);
			return ret.first;
		}

		template <class InputIterator>
  		void insert (InputIterator first, InputIterator last) {
			  while (first != last) insert(*first++);
		}

		void erase (iterator position) {
			erase(position->first);
		}

		size_type erase( const Key& key ) {
			return _tree.erase(ft::make_pair(key, mapped_type()));
		}

		void erase (iterator first, iterator last) {
			while (first != last) erase(first++);
		}

		void swap (map &x) {
			_tree.swap(x._tree);
		}

		friend void swap (map &x, map &y) {
			x.swap(y);
		}

		void clear() {
			_tree.clear();
		}


	/*------------------Observers------------------*/

	key_compare key_comp() const {return _keyComp;}
	value_compare value_comp() const {return _comp;}


	/*------------------Finder------------------*/

	iterator find (const key_type& k) {
		return _tree.find(ft::make_pair(k, mapped_type()));
	}

	const_iterator find (const key_type& k) const {
		return _tree.find(ft::make_pair(k, mapped_type()));
	}

	size_type count (const key_type& k) const {
		return (find(k) != end());
	}

	iterator lower_bound (const key_type& k) {
		return _tree.lower_bound(ft::make_pair(k, mapped_type()));
	}

	const_iterator lower_bound (const key_type& k) const {
		return _tree.lower_bound(ft::make_pair(k, mapped_type()));
	}

	iterator upper_bound (const key_type& k) {
		return _tree.upper_bound(ft::make_pair(k, mapped_type()));
	}
	const_iterator upper_bound (const key_type& k) const {
		return _tree.upper_bound(ft::make_pair(k, mapped_type()));
	}

	pair<iterator,iterator> equal_range (const key_type& k) {
		return ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k));
	}
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const  {
		return ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));
	}


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


	/*------------------DEBUG------------------*/

	#ifdef DEBUG
		void getRoot() {
			_tree.getRoot();
		}

		void print() {
			_tree.print("", _tree.getRoot(), 0);
		}

		void checkValid() {
			_tree.checkValid();
		}

	#endif

	private:
		Alloc _alloc;
		key_compare _keyComp;
		value_compare _comp;
		tree_type _tree;

	};

}