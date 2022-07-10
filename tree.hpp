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
		node	*par;
		node	*left;
		node	*right;
		T		val;
		bool	col;

		node(T v = T(), bool c = RED) : par(NULL), left(NULL), right(NULL), val(v), col(c) {}
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



	/*------------------Constructor------------------*/

		explicit tree(const value_compare &comp) 
		: _size(0), _alloc(allocator_type()), _nodeAlloc(std::allocator<node<value_type> >()), _last(value_type(), BLACK), _comp(comp) {
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

		size_type max_size() const {

			typename Alloc::template rebind<node_type>::other tmp;
			return tmp.max_size();
		}	


	/*------------------Tree utils------------------*/

		nodePtr newNode(const value_type &val) {
			nodePtr ret = _nodeAlloc.allocate(1);
			_nodeAlloc.construct(ret, val);
			return ret;
		}

		void deleteNode(nodePtr node) {
			_nodeAlloc.destroy(node);
			_nodeAlloc.deallocate(node, 1);
		}

		nodePtr successor(nodePtr node) {
			if (!node || !node->right)
				return (NULL);
			node = node->right;
			while (node->left)
				node = node->left;
			return node;
		}

		nodePtr predecessor(nodePtr node) {
			if (!node || !node->left)
				return (NULL);
			node = node->left;
			while (node->right)
				node = node->right;
			return node;
		}

		void transplant(nodePtr u, nodePtr v) {
			if (!u->par)
				_root = v;
			else if (u == u->par->left)
				u->par->left = v;
			else
				u->par->right = v;
			if (v)
				v->par = u->par;
		}


		nodePtr insert_child(nodePtr parent, nodePtr node) {
			if (!parent) {
				_root = node;
				_last.par = _root;
				_root->right = &_last;
				node->col = BLACK;
			} else {
				if (_comp(parent->val, node->val)) {
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

		ft::pair<nodePtr, bool> insert(const value_type &val) {
			nodePtr cur = _root, parent = NULL, node;

			while (cur && cur != &_last) {
				parent = cur;
				if (_comp(val, cur->val)) cur = cur->left;
				else if (_comp(cur->val, val)) cur = cur->right;
				else return ft::make_pair(cur, false);
			}
			node = insert_child(parent, newNode(val));

			insertFix(node);

			return ft::make_pair(node, true);
		}

		void insertFix(nodePtr node) {
			if (!node->par || !node->par->par) 
				return;
			while (node->par && node->par->col == RED) {
				nodePtr p = node->par, gp = node->par->par;
				if (p == gp->left)
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
			nodePtr node = _root;

			while (node && !isEqual(node->val, val))
				node = (_comp(val, node->val) ? node->left : node->right);

			if (!node || node == &_last)
				return 0;

			nodePtr x, y, dummy = NULL;
			bool original_col = node->col;

			if (!node->left && !node->right) {
				dummy = newNode(val);
				dummy->col = BLACK;
				transplant(node, dummy);
				x = dummy;
			} else if (!node->left) {
				transplant(node, node->right);
				x = node->right;
			} else if (!node->right || node->right == &_last) {
				transplant(node, node->left);
				if (node->right == &_last) {
					nodePtr tmp = node->left;
					while (tmp->right)
						tmp = tmp->right;
					tmp->right = &_last;
					_last.par = tmp;
				}
				x = node->left;
			} else {
				y = predecessor(node);
				x = y->left;
				if (!x) {
					dummy = newNode(val);
					dummy->col = BLACK;
					dummy->par = y;
					y->left = dummy;
					x = dummy;
				}
				original_col = y->col;
				if (y->par != node) {
					transplant(y, x);
					y->left = node->left;
					if (y->left)
						y->left->par = y;
				}
				transplant(node, y);
				y->col = node->col;
				y->right = node->right;
				if (y->right)
					y->right->par = y;
			}

			if (x && original_col == BLACK)
				deleteFix(x);

			if (dummy) {
				transplant(dummy, NULL);
				deleteNode(dummy);
			}

			deleteNode(node);

			_size--;

			return 1;
		}

		void deleteFix(nodePtr node) {
			while (node != _root && node->col == BLACK) {
				if (node == node->par->left) {
					nodePtr s = node->par->right;
					if (s && s->col == RED) {
						s->col = BLACK;
						node->par->col = RED;
						leftRotate(node->par);
						s = node->par->right;
					}
					if (s && (!s->left || s->left->col == BLACK) && (!s->right || s->right->col == BLACK)) {
						s->col = RED;
						node = node->par;
					} else {
						if (s && (!s->right || s->right->col == BLACK)) {
							if (s->left)
								s->left->col = BLACK;
							s->col = RED;
							rightRotate(s);
							s = node->par->right;
						}
						if (s) {
							s->col = node->par->col;
							s->right->col = BLACK;
						}
						node->par->col = BLACK;
						leftRotate(node->par);
						node = _root;
					}
				} else {
					nodePtr s = node->par->left;
					if (s && s->col == RED) {
						s->col = BLACK;
						node->par->col = RED;
						rightRotate(node->par);
						s = node->par->left;
					}
					if (s && (!s->right || s->right->col == BLACK) && (!s->left || s->left->col == BLACK)) {
						s->col = RED;
						node = node->par;
					} else {
						if (s && (!s->left || s->left->col == BLACK)) {
							if (s->right)
								s->right->col = BLACK;
							s->col = RED;
							leftRotate(s);
							s = node->par->left;
						}
						if (s) {
							s->col = node->par->col;
							s->left->col = BLACK;
						}
						node->par->col = BLACK;
						rightRotate(node->par);
						node = _root;
					}
				}
			}
			node->col = 0;
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
				if (_comp(cur->val, v))
					cur = cur->right;
				else
					res = cur, cur = cur->left;
			}
			return ((res && res != &_last) ? iterator(res, &_last) : end());
		}

		const_iterator lower_bound (const value_type& v) const {
			nodePtr cur = _root, res = NULL;
			while (cur && cur != &_last) {
				if (_comp(cur->val, v))
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

		nodePtr getLast() {return &_last;};
		nodePtr getRoot() {return _root;};


	/*------------------DEBUG------------------*/

		void print(const std::string &prefix, nodePtr node, bool isLeft = 0)
		{
			if (!node || node == &_last) return;

			std::cout << prefix;
        	std::cout << (isLeft ? "├──" : "└──" );

			std::cout << (node->col == BLACK ? "\033[1;90m" : "\033[1;31m") << node->val << "\033[0m" << std::endl;

        	print(prefix + (isLeft ? "│   " : "    "), node->left, true);
        	print(prefix + (isLeft ? "│   " : "    "), node->right, false);
		}

		void checkValid() {
			std::cout << "Check valid called : ";
			int minDepth = 2147483647, maxDepth = 0;
			if (!checkValidDfs(_root, 0, minDepth, maxDepth))
				return;

			if (maxDepth != minDepth)
				std::cout << "BLACK depth rule violoated" << std::endl;
			else
				std::cout << "\033[1;32mOK\033[0m\n";
		}

		int checkValidDfs(nodePtr node, int depth, int &minDepth, int &maxDepth) {
			depth += (!node || node->col == BLACK);
			if (!node || node == &_last) {
				minDepth = ft::min(minDepth, depth);
				maxDepth = ft::max(maxDepth, depth);
				return 1;
			}

			if (node->col == RED) {
				if ((node->left && node->left->col== RED)
					|| (node->right && node->right->col== RED)) {
					std::cout << "RED rule violated" << std::endl;
					return 0;
				}
			}

			if (!checkValidDfs(node->left, depth , minDepth, maxDepth)
				|| !checkValidDfs(node->right, depth , minDepth, maxDepth))
				return 0;
			return 1;
		}


	private:
		size_type _size;
		Alloc _alloc;
		std::allocator<node_type> _nodeAlloc;
		node_type _last;
		node<value_type> *_root;
		value_compare _comp;

	};


}