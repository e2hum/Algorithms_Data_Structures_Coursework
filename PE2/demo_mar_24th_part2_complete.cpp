#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class BinaryTreeNode {
	int val;
	BinaryTreeNode* left, * right;
public:
	BinaryTreeNode(int new_val) : val(new_val), left(NULL), right(NULL) {}
	void print() { cout << val << " "; }

	friend class BinaryTree;
	friend class BinaryTreeTest;	
};

class BinaryTree {
	BinaryTreeNode* root;
	int size;
public:
	BinaryTree() : root(NULL), size(0) {}
	~BinaryTree() { clean_up(root); size = 0; root = NULL; }
	
	int min(BinaryTreeNode* T) {
		if (!T) return -1;

		BinaryTreeNode* cur = T;
		while (cur && cur->left) 
			cur = cur->left;		

		return cur->val;
	}
	
	int min() {
		return min(root);
	}
	
	int max(BinaryTreeNode* T) {
		if (!T) return -1;

		BinaryTreeNode* cur = T;
		while (cur && cur->right) 
			cur = cur->right;		

		return cur->val;
	}

	int max() {
		return max(root);
	}
	
	bool exists(BinaryTreeNode* T, int key) {
		BinaryTreeNode* cur = T;
		while (cur) {
			if (cur->val == key) 
				return true;
			
			if (cur->val > key)
				cur = cur->left;	
			else
				cur = cur->right;	
		} 

		return false;
	}

	bool exists(int key) {
		return exists(root, key);
	}

	//inserts in BST manner
	bool insert(BinaryTreeNode new_node) {
		BinaryTreeNode** cur = &root;
		while (*cur) {
			if ((*cur)->val == new_node.val) 
				return false;
			
			if ((*cur)->val > new_node.val)
				cur = &((*cur)->left);	
			else
				cur = &((*cur)->right);	
		} 

		*cur = new BinaryTreeNode(new_node);
		++size;
		
		return true;		
	}

	void pre_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		T->print();
		pre_order(T->left);
		pre_order(T->right);
	}

	void pre_order() {
		pre_order(root);
	}

	void in_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		in_order(T->left);
		T->print();
		in_order(T->right);
	}

	void in_order() {
		in_order(root);
	}

	void post_order(BinaryTreeNode* T) {
		if (T == NULL) return;
		post_order(T->left);
		post_order(T->right);
		T->print();
	}

	void post_order() {
		post_order(root);
	}

	void BFT(BinaryTreeNode* T) {
		if (T == NULL) return;
		
		queue<BinaryTreeNode*> bft_queue;
		bft_queue.push(T);

		while(!bft_queue.empty()) {
			BinaryTreeNode* cur = bft_queue.front();
			bft_queue.pop();

			cur->print();
			if (cur->left) bft_queue.push(cur->left);
			if (cur->right) bft_queue.push(cur->right);
		}
	}

	void BFT() {
		BFT(root);
	}
	
	void clean_up(BinaryTreeNode* T) {
		if (T == NULL) return;
		clean_up(T->left);
		clean_up(T->right);
		delete T;
	}
};

class BinaryTreeTest {
public:
	void test_traversals(BinaryTree& test_tree) {
		
		cout << endl << "Test PreOrder Traversal" << endl;		
		test_tree.pre_order();	

		cout << endl << "Test InOrder Traversal" << endl;		
		test_tree.in_order();	
		
		cout << endl << "Test PostOrder Traversal" << endl;		
		test_tree.post_order();	
		
		cout << endl << "Test Breadth First Traversal" << endl;
		test_tree.BFT();
	}
	
	void test_scenario1() {
		BinaryTree test_tree;

		BinaryTreeNode* root = new BinaryTreeNode(14);
		root->left = new BinaryTreeNode(12);
		root->right = new BinaryTreeNode(25);
		root->right->left = new BinaryTreeNode(21);
		root->right->right = new BinaryTreeNode(36);

		cout << "Min value is " << test_tree.min(root) << endl;
		cout << "Max value is " << test_tree.max(root) << endl;

		cout << (test_tree.exists(root, 25) ? "25 exists" : "25 does not exist") << endl;
		cout << (test_tree.exists(root, 32) ? "32 exists" : "32 does not exist") << endl;
		
		test_tree.clean_up(root);	
	}	
	
	void test_scenario2() {
		BinaryTree test_tree;

		test_tree.insert(BinaryTreeNode(15));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(11));
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(14));
		test_tree.insert(BinaryTreeNode(10));
		test_tree.insert(BinaryTreeNode(9));
		test_tree.insert(BinaryTreeNode(8));
		test_tree.insert(BinaryTreeNode(7));

		test_traversals(test_tree);
	}	

	void test_scenario3() {
		BinaryTree test_tree;

		test_tree.insert(BinaryTreeNode(15));
		test_tree.insert(BinaryTreeNode(12));
		test_tree.insert(BinaryTreeNode(14));
		test_tree.insert(BinaryTreeNode(16));
		test_tree.insert(BinaryTreeNode(11));
		test_tree.insert(BinaryTreeNode(18));
		test_tree.insert(BinaryTreeNode(13));
		test_tree.insert(BinaryTreeNode(17));
		test_tree.insert(BinaryTreeNode(19));

		cout << endl << "Min value is " << test_tree.min() << endl;
		cout << "Max value is " << test_tree.max() << endl;

		cout << (test_tree.exists(16) ? "16 exists" : "16 does not exist") << endl;
		cout << (test_tree.exists(42) ? "42 exists" : "42 does not exist") << endl;
		
		test_traversals(test_tree);	
	}	

	void run_tests() {
		test_scenario1();
		test_scenario2();	
		test_scenario3();	
	}
};

int main() {	
	BinaryTreeTest test1;
	test1.run_tests();
}
