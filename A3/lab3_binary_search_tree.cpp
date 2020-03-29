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

unsigned int BinarySearchTree::height(TaskItem* val) const {
	// Base case: return -1 for empty tree
	if (!val)
		return -1;
	// General case: return 1 + max(height(left), height(right))
	else
		return (1 + std::max(height(val->left), height(val->right)));
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	TaskItem* cur = root;
	height(cur);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	cout << endl << "In_Order" << endl;
	in_order(root);
	cout << endl << "Pre_Order" << endl;
	pre_order(root);
}

void BinarySearchTree::in_order(TaskItem* val) const {
	if (!val) 
		return;
	in_order(val->left);
	cout << "Priority: " << val->priority << endl
		 << "Description: " << val->description << endl;
	in_order(val->right);
}
void BinarySearchTree::pre_order(TaskItem* val) const {
	if (!val) 
		return;
	cout << "Priority: " << val->priority << endl
	 	<< "Description: " << val->description << endl;
	pre_order(val->left);
	pre_order(val->right);
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
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
	if(!exists(val))
		return false;

	//GET parent
	TaskItem* parent = NULL;
	TaskItem* cur = root;
	while (!(*cur==val)) {
		// move left if given key is smaller than cur's key
		parent = cur;
		if (val.priority < cur->priority)
			cur = cur->left;
		// move right if given key is greater than cur's key
		else
			cur = cur->right;
	}
	int children = 0;
	if (cur->left)
		children++;
	if (cur->right)
		children++;
	
	//case 0, val is root
	if(val == *root){
		cout << "case0" << endl;
		if (size==1) {
			delete root;
			root = NULL;
		}
		else {
			//FINDS and STORES largest node from left child's branch 
			TaskItem* cur = root->left;
			TaskItem* right = root->right;
			TaskItem* left = root->left;
			while(cur->right && cur)
				cur = cur->right;
			//REMOVES cur from its original position 
			BinarySearchTree::remove(*cur);
			delete root;
			root = cur;
			root->left = left;
			root->right = right;
		}
			
	}
	//case 1, val is leaf node (no children)
	else if(children == 0){
		std::cout << "case1" << endl;
		if (*(parent->left)==val){
			delete parent->left;
			parent->left = NULL;
		}else{
			delete parent->right;
			parent->right = NULL;
		}
	}
	//case 2, val has single child
	//alternative for xor: if(!A != !B)
	else if(children == 1){
		std::cout << "case2" << endl;
		//create pointer to ONLY child
		TaskItem* child;
		if (cur->left)
			child = cur->left;
		else 
			child = cur->right;
		//create pointer to node being deleted
		TaskItem* temp;
		if (*(parent->left)==val)
			temp = parent->left;
		else
			temp = parent->right;

		//link parent to child
		if (*(parent->left)==val)
			parent->left = child;
		else
			parent->right = child;

		//delete temp node
		delete temp;
		temp = NULL;

	}
	//case 3, val has two children
	else{
		std::cout << "case3" << endl;
		//FINDS and STORES largest node from left child's branch 
		TaskItem* cur = val.left;
		while(cur->right && cur)
			cur = cur->right;
		//REMOVES cur from its original position 
		BinarySearchTree::remove(*cur);
		//REPLACES val with cur
		if (*(parent->left)==val)
			parent->left = cur;
		else
			parent->right = cur;		
		cur->left = val.left;
		cur->right = val.right;
	}

	size--;
	return true;
}

//helper returns true if child is on left node;
bool BinarySearchTree::isChildLeft(BinarySearchTree::TaskItem* child, BinarySearchTree::TaskItem* parent){
	if (parent->left == child)
		return true;
	else
		return false;
}
// deletes all the nodes in the tree
void BinarySearchTree::clean_up(TaskItem* val) {
	if (val == NULL) return;
	clean_up(val->left);
	clean_up(val->right);
	delete val;
}
