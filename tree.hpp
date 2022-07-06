#pragma once

#include "./iterator/bidirectional_iterator.hpp"
#include "./iterator/reverse_iterator.hpp"
#include "template_utils.hpp"
#include "algorithm.hpp"

#define BLACK 0
#define RED 1

namespace ft {


/*		UTILS		*/


/*		TREE		*/


template<typename T, typename Alloc = std::allocator<T> >
	struct node {
		Alloc	alloc;
		node	*par;
		node	*left;
		node	*right;
		T		*val;
		bool	col;

		// Default constructor (value can be precised)
		node(T fval = T()) : alloc(Alloc()), par(NULL), left(NULL), right(NULL), col(RED) {
			val = alloc.allocate(1);
			alloc.construct(val, fval);
		}

		// Color and value constructor
		node(bool fcol, T fval) : alloc(Alloc()), par(NULL), left(NULL), right(NULL), col(fcol) {
			val = alloc.allocate(1);
			alloc.construct(val, fval);
		}

		~node() {
			alloc.destroy(val);
			alloc.deallocate(val, 1);
		}
	};

	template<typename T, typename Compare, typename Alloc>
	class tree {
	public:
	/*------------------Member type------------------*/

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef Compare value_compare;
		typedef typename allocator_type::reference reference ;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::pointer const_pointer;
		typedef long difference_type;
		typedef unsigned long size_type;

		typedef node<T> node_type;
		typedef node<T>* nodePtr;

		typedef bidirectional_iterator<value_type, Compare, Alloc, node<value_type>, 0> iterator;
		typedef bidirectional_iterator<value_type, Compare, Alloc, node<value_type>, 1> const_iterator;
		typedef rev_iterator<iterator> reverse_iterator;
		typedef rev_iterator<const_iterator> const_reverse_iterator;	


	/*------------------PRINT------------------*/

		//only for map
		void print() {
			printBT("", _root);
		}

		void printBT(const std::string &prefix, nodePtr node, bool isLeft = 0)
		{
			if (!node) return;

			std::cout << prefix;
        	std::cout << (isLeft ? "├──" : "└──" );

        	std::cout << node->val->first <<  (node->col == BLACK ? "(B)" : "(R)") << std::endl;

        	printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
        	printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
		}


	/*------------------Constructor------------------*/

		explicit tree(const value_compare &comp) 
		: _size(0), _alloc(allocator_type()), _nodeAlloc(std::allocator<node<value_type> >()), _last(BLACK, value_type()), _comp(comp) {
			_root = &_last;
		}		

		tree(const tree &cpy)
		: _size(0), _alloc(cpy._alloc), _nodeAlloc(cpy._nodeAlloc), _last(BLACK, value_type()), _comp(cpy._comp) {
			_root = &_last;
			this->insert(cpy.begin(), cpy.end());
		}

		~tree() {destruct(_root);}

		tree& operator=(const tree& cpy) { 
			_comp = cpy._comp;
			this->clear();
			for (iterator &it = cpy.begin(); it != cpy.end(); ++it)
				this->insert(*it);
			return *this;
		}
		

	/*------------------utils---------------------*/

	bool isEqual(const value_type &l, const value_type &r) const {
		return (!_comp(l, r) && !_comp(r, l));
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
			T						data;
			bool					color;
			struct s_node *			left;
			struct s_node *			right;
			struct s_node *			parent;
		} tmp_node;

		size_type max_size() const {
			typename Alloc::template rebind<tmp_node>::other tmp;
			return tmp.max_size();
		}	


	/*------------------Tree utils------------------*/

		nodePtr newNode(const value_type &val) {
			nodePtr ret = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(ret, val);
			return ret;
		}

		void deleteNode(nodePtr nd) {
			_nodeAlloc.destroy(nd);
			_nodeAlloc.deallocate(nd, 1);
		}

		nodePtr insert_child(nodePtr parent, nodePtr node) {
			if (!parent) {
				_root = node;
				_last.par = _root;
				_root->right = &_last;
				node->col = BLACK;
			} else {
				if (_comp(*parent->val, *node->val)) {
					if (parent->right == &_last) {
						_last.par = node;
						node->right = &_last;
					}
					parent->right = node;
				} else
					parent->left = node;
				node->par = parent;
			}
			_size++;
			return node;
		}

	/*------------------Rotation------------------*/

	nodePtr	leftRotate(nodePtr node) {
		if (!node || !node->right)
			return NULL;
		nodePtr	y = node->right;
		node->right = y->left;
		if (y->left)
			y->left->par = node;
		if (node == _root)
			_root = y;
		else if (node == node->par->left)
			node->par->left = y;
		else
			node->par->right = y;
		y->par = node->par;
		node->par = y;
		y->left = node;
		return y;
	}

	nodePtr	rightRotate(nodePtr node) {
		if (!node || !node->left)
			return NULL;
		nodePtr	y = node->left;
		node->left = y->right;
		if (y->right)
			y->right->par = node;
		if (node == _root)
			_root = y;
		else if (node == node->par->left)
			node->par->left = y;
		else
			node->par->right = y;
		y->par = node->par;
		node->par = y;
		y->right = node;
		return y;
	}

	nodePtr leftRightRotate(nodePtr node) {
		if (!node || !node->left || !node->left->right)
			return NULL;
		leftRotate(node->left);
		return rightRotate(node);
	}

	nodePtr rightLeftRotate(nodePtr node) {
		if (!node || !node->right || !node->right->left)
			return NULL;
		rightRotate(node->right);
		return leftRoate(node);
	}

	/*------------------Insertion------------------*/

		ft::pair<iterator, bool> insert(const value_type &val) {
			nodePtr cur = _root, parent = NULL, node;

			while (cur && cur != &_last) {
				parent = cur;
				if (_comp(val, *cur->val)) cur = cur->left;
				else if (_comp(*cur->val, val)) cur = cur->right;
				else return ft::make_pair(iterator(cur, &_last), false);
			}
			node = insert_child(parent, newNode(val));

			InsertFix(node);

			return ft::make_pair(iterator(node, &_last), true);
		}

		// Red-Black tree insertFix
		void InsertFix(nodePtr node) {
			if (!node->par || !node->par->par) 
				return;
			while (node->par && node->par->col == RED) {
				nodePtr p = node->par, gp = node->par->par;
				if (p == gp->left)
			 		//Case 1
					if (gp->right && gp->right->col == RED) {
						gp->right->col = BLACK;
						gp->left->col = BLACK;
						gp->col = RED;
						node = gp;
					} else {
						if (node == p->right) {
							node = p;
							leftRotate(node);
						}
						if (node->par->par) { 
							node->par->col = BLACK;
							node->par->par->col = RED;
							rightRotate(node->par->par);
						}
					} else {
						if (gp->left && gp->left->col == RED) {
							gp->left->col = BLACK;
							gp->right->col = BLACK;
							gp->col = RED;
							node = gp;
						} else {
							if (node == p->left) {
								node = p;
								rightRotate(node);
							}
							if (node->par->par) {
								node->par->col = BLACK;
								node->par->par->col = RED;
								leftRotate(node->par->par);
							}
						}
					}
					if (node == _root)
						break;
			}
			_root->col = BLACK;
		}


	/*------------------Erase------------------*/

		size_type erase( const value_type &val) {
			nodePtr cur = _root;

			while (cur && !isEqual(*cur->val, val) && cur != &_last)
				cur = (_comp(val, *cur->val) ? cur->left : cur->right);

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

		void eraseNode(nodePtr nd) {
			nodePtr newChild = NULL;

			if (nd->left)
				newChild = nd->left;
			else if (nd->right && nd->right != &_last)
				newChild = nd->right;

			if (nd->par) {
				if (nd->par->left == nd)
					nd->par->left = newChild;
				else
					nd->par->right = newChild;
			}

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

		void swap (tree &x) {
			ft::swap(_size, x._size);
			ft::swap(_root, x._root);
			ft::swap(_last.par, x._last.par);	
			_last.par->right = &_last;
			x._last.par->right = &x._last;
		}

		friend void swap (tree &x, tree &y) {x.swap(y);}

		void clear() {
			destruct(_root);
			_last.par = NULL;
			_root = &_last;
			_size = 0;
		}


		void destruct(nodePtr cur) {
			if (!cur || cur == &_last) return;
			destruct(cur->left);
			destruct(cur->right);
			deleteNode(cur);
		}
	
	/*------------------Finder------------------*/

	iterator find (const value_type& v) {
		iterator ret = lower_bound(v);
		return (ret == end() || !isEqual(*ret, v) ? end() : ret);
	}

	const_iterator find (const value_type& v) const {
		const_iterator ret = lower_bound(v);
		return (ret == end() || !isEqual(*ret, v) ? end() : ret);
	}

	iterator lower_bound (const value_type& v) {
		nodePtr cur = _root, res = NULL;
		while (cur && cur != &_last) {
			if (_comp(*cur->val, v))
				cur = cur->right;
			else
				res = cur, cur = cur->left;
		}
		return ((res && res != &_last) ? iterator(res, &_last) : end());
	}

	const_iterator lower_bound (const value_type& v) const {
		nodePtr cur = _root, res = NULL;
		while (cur && cur != &_last) {
			if (_comp(*cur->val, v))
				cur = cur->right;
			else
				res = cur, cur = cur->left;
		}
		return ((res && res != &_last) ? const_iterator(res, &_last) : end());
	}

	iterator upper_bound (const value_type& v) {
		iterator ret = lower_bound(v);
		if (ret != end() && isEqual(*ret, v)) ++ret;
		return ret;
	}

	const_iterator upper_bound (const value_type& v) const {
		const_iterator ret = lower_bound(v);
		if (ret != end() && isEqual(*ret, v)) ++ret;
		return ret;
	}


	/*------------------Guetter------------------*/

	nodePtr lastNode() {return &_last;};

	private:
		size_type _size;
		Alloc _alloc;
		std::allocator<node_type> _nodeAlloc;
		node_type _last;
	public:
		node<value_type> *_root;
		value_compare _comp;

	};


}