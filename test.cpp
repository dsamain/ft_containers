#include <memory>
#include <iostream>

struct node {
	node *par;
	node *left;
	node *right;
	int val;
};

int main() {
	std::allocator<node> alloc;

	node *root = alloc.allocate(1);
	root->val = 5;
	std::cout << root->val << std::endl;
}