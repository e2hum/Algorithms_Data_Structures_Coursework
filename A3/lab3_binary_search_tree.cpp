#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	//root = new TaskItem*[0];
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	clean_up(root);
	root = NULL;
	size = 0;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	// Base case: empty tree
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
	// General case: non-empty tree
	BinarySearchTree::TaskItem* cur = root;
	while(cur->right && cur)
		cur = cur->right;
	return *cur;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	// Base case: empty tree
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
	// General case: non-empty tree
	BinarySearchTree::TaskItem* cur = root;
	while(cur->left && cur)
		cur = cur->left;
	return *cur;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
		TaskItem* cur = root;
		while (cur) {
			if (cur->priority == val.priority)
				return true;
				// move left if given key is smaller than cur's key
				if (val.priority < cur->priority)
					cur = cur->left;
				// move right if given key is greater than cur's key
				else
					cur = cur->right;
			}
		return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    // set cur to point to the address of root
		TaskItem** cur = &root; // cur -> root -> root value
		
		while (*cur) {
			// check for duplicates; if found, reject them
			if ((*cur)->priority == val.priority)
				return false;
				
				// move left if given key is smaller than cur's key
				if (val.priority < (*cur)->priority)
					cur = &((*cur)->left); // point to the location where
										   // *cur's left pointer is stored
				// move right if given key is greater than cur's key
				else
					cur = &((*cur)->right); // point to the location where
										    // *cur's right pointer is stored
			}
		*cur = new TaskItem(val);
		size++;
		return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	if(!exist(val))
		return false;

	//get pointer to parent node 'parent'

	//case 1, val is leaf node (no children)
	if(!(val->left || val->right )){
		parent->left = NULL;
		parent->right = NULL;
		delete val;
		val = NULL;
	}//case 2 val has single child
	else if(val->left ^ val->right){
		//create pointer to child
		TaskItem* child;
		if (val->left)
			child = val->left;
		else 
			child = val->right;
		//create pointer to node being deleted
		TaskItem* temp = val;
		//link parent to child
		if (parent->left==val)
			parent->left = child;
		else
			parent->right = child
		//delete temp node
		delete temp;
		temp = NULL;
	}

	size--;
	return true;
}

//helper returns true if child is on left node;
bool BinarySearchTree::isChildLeft(BinarySearchTree::TaskItem child, BinarySearchTree::TaskItem parent){
	if (parent->left == child)
		return true;
	else
		return false;
}

void clean_up(TaskItem* T) {
	if (T == NULL) return;
	clean_up(T->left);
	clean_up(T->right);
	delete T;
}
