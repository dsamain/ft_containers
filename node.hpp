#pragma once

namespace ft {

template<typename T, typename Alloc = std::allocator<T> >
	struct node {
		Alloc	alloc;
		node	*par;
		node	*left;
		node	*right;
		T		*val;
		bool	col;

		// Default constructor (value can be precised)
		node(T fval = T()) : alloc(Alloc()), par(NULL), left(NULL), right(NULL), col(1) {
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
}