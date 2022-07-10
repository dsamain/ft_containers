#pragma once

#include "tree.hpp"


namespace ft {

	template<typename T,
		typename Compare = ft::less<T>,
		typename Alloc = std::allocator<T> >
	class set {
	public:

	/*------------------Member type------------------*/

		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference ;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::pointer const_pointer;
		typedef long difference_type;
		typedef unsigned long size_type;

	private:
		typedef tree<value_type, value_compare, allocator_type> tree_type;
	public:

		typedef typename tree_type::const_iterator iterator;
		typedef typename tree_type::const_iterator const_iterator;
		typedef rev_iterator<iterator> reverse_iterator;
		typedef rev_iterator<const_iterator> const_reverse_iterator;	



	/*------------------Constructor------------------*/

		explicit set(const key_compare &comp = key_compare(),
              const allocator_type &alloc = allocator_type())
		: _alloc(alloc), _keyComp(comp), _comp(comp), _tree(value_compare(comp)) {
		}		

		template <class InputIterator>
  		set (InputIterator first, InputIterator last,
       const key_compare& comp = key_compare(),
       const allocator_type& alloc = allocator_type())
	   : _alloc(alloc), _keyComp(comp), _comp(comp), _tree(value_compare(comp)) {
			insert(first, last);
	   }

		set(const set &cpy)
		: _alloc(cpy._alloc), _keyComp(cpy._keyComp), _comp(cpy._comp), _tree(value_compare(cpy._comp)) {
			this->insert(cpy.begin(), cpy.end());
		}

		~set() {}

		set& operator=(const set& cpy) { 
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
  		void insert (InputIterator first, InputIterator last) {while (first != last) insert(*first++);}

		void erase (iterator position) {erase(*position);}

		size_type erase( const value_type& key ) {
			return _tree.erase(key);
		}

		void erase (iterator first, iterator last) {while (first != last) erase(first++);}

		void swap (set &x) {
			_tree.swap(x._tree);
		}

		friend void swap (set &x, set &y) {x.swap(y);}

		void clear() {
			_tree.clear();
		}


	/*------------------Observers------------------*/

	key_compare key_comp() const {return _keyComp;}
	value_compare value_comp() const {return _comp;}


	/*------------------Finder------------------*/

	iterator find (const value_type& k) {
		return _tree.find(k);
	}

	const_iterator find (const value_type& k) const {
		return _tree.find(k);
	}

	size_type count (const value_type& k) const {return (find(k) != end());}

	iterator lower_bound (const value_type& k) {
		return _tree.lower_bound(k);
	}

	const_iterator lower_bound (const value_type& k) const {
		return _tree.lower_bound(k);
	}

	iterator upper_bound (const value_type& k) {
		return _tree.upper_bound(k);
	}
	const_iterator upper_bound (const value_type& k) const {
		return _tree.upper_bound(k);
	}

	pair<iterator,iterator>             equal_range (const key_type& k) {return ft::pair<iterator,iterator>(lower_bound(k), upper_bound(k));}
	pair<const_iterator,const_iterator> equal_range (const key_type& k) const  {return ft::pair<const_iterator,const_iterator>(lower_bound(k), upper_bound(k));}

	/*------------------Allocator------------------*/

	allocator_type get_allocator() const;

	/*------------------Comparaison------------------*/

	friend bool operator==(const set &l, const set &r) {
		const_iterator it = l.begin();
		const_iterator it2 = r.begin();
		while (it != l.end())
			if (*it++ != *it2++)
				return 0;
		return (it2 == r.end());
	}

	friend bool operator!=(const set &l, const set &r) {return !(l == r);}
	friend bool operator<(const set &l, const set &r) {return ft::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());}
	friend bool operator<=(const set &l, const set &r) {return (l < r || l == r);}
	friend bool operator>(const set &l, const set &r) {return ft::lexicographical_compare(r.begin(), r.end(), l.begin(), l.end());}
	friend bool operator>=(const set &l, const set &r) {return (l > r || l == r);}


	/*------------------DEBUG------------------*/

	#ifdef DEBUG
		void getRoot() {
			_tree.getRoot();
		}

		void getLast() {
			_tree.getLast();
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