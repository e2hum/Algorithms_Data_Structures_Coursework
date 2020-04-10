#include <iostream>
#include <vector>
#include <queue>
#include <string>

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
	string int2ascii(int val) {
		if (val < 0)
			return "-" + int2ascii(-val);
		else if (val <= 9)
			return string(1, '0' + val);
		else
			return int2ascii(val/10) + char('0' + val % 10);
	}
	
	void find_and_print_sum_of_nodes(BinaryTreeNode* T, int desired_sum, int cur_sum, string buffer) {
		if (!T)
			return;
		int new_sum = cur_sum + T->val;
		string new_buffer = buffer + " " + int2ascii(T->val);
		
		if (new_sum == desired_sum)
			cout << new_buffer << endl;
		cout <<  "NEW SUM: " << new_sum << endl;
		if (new_sum < desired_sum) { 
			if (T->left)
				find_and_print_sum_of_nodes(T->left, desired_sum, new_sum, new_buffer);
			if (T->right) {
				cout << "NEWER SUMM: " << new_sum << endl;
				find_and_print_sum_of_nodes(T->right, desired_sum, new_sum, new_buffer);
				}
			}
		cout << "RESET" << endl;
		if (T->left)
			find_and_print_sum_of_nodes(T->left, desired_sum, 0, "");
		if (T->right)
			find_and_print_sum_of_nodes(T->right, desired_sum, 0, "");
	} 
	
	int find_max_sum_of_nodes(BinaryTreeNode* T, int & temp_max_sum) {
		if (!T)
			return 0;
		
		int left_sum = find_max_sum_of_nodes(T->left, temp_max_sum);
		int right_sum = find_max_sum_of_nodes(T->right, temp_max_sum);
		
		int max1 = std::max(T->val, std::max(left_sum, right_sum) + T->val);
		int max2 = std::max(max1, left_sum + right_sum + T->val);
		
		temp_max_sum = std::max(temp_max_sum, max2);
		
		return max1;
	}
		
				
};

class BinaryTreeTest {
public:
	
	void test_sum_of_nodes(BinaryTree& test_tree) {}
		
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
	
	void test_scenario() {
		BinaryTree test_tree;
		cout << "Find and Print Sum of Nodes:" << endl;
		// TEST CASE 1
		cout << endl << "TEST CASE 1" << endl;
		BinaryTreeNode* root1 = new BinaryTreeNode(5);
		root1->left = new BinaryTreeNode(3);	
		root1->right = new BinaryTreeNode(1);
		root1->left->left = new BinaryTreeNode(-1);
		root1->left->right = new BinaryTreeNode(8);
		root1->right->right = new BinaryTreeNode(11);
		root1->left->left->left = new BinaryTreeNode(18);
		root1->left->right->left = new BinaryTreeNode(6);
		test_tree.find_and_print_sum_of_nodes(root1, 17, 0, "");
		// TEST CASE 2
		cout << endl << "TEST CASE 2" << endl;
		BinaryTreeNode* root2 = new BinaryTreeNode(3);
		root2->left = new BinaryTreeNode(7);	
		root2->right = new BinaryTreeNode(8);
		root2->left->right = new BinaryTreeNode(4);
		root2->right->right = new BinaryTreeNode(12);
		root2->right->left = new BinaryTreeNode(1);
		root2->right->left->right = new BinaryTreeNode(2);
		root2->right->left->right->right = new BinaryTreeNode(9);
		test_tree.find_and_print_sum_of_nodes(root2, 12, 0, "");
	}
	
	void test_scenario0() {
		BinaryTree test_tree;
		cout << endl << "Find Max Sum of Nodes across Subtrees:" << endl;
		BinaryTreeNode* root = new BinaryTreeNode(5);
		root->left = new BinaryTreeNode(6);
		root->left->left = new BinaryTreeNode(15);
		root->left->right = new BinaryTreeNode(10);
		root->left->right->right = new BinaryTreeNode(-5);
		root->right = new BinaryTreeNode(-15);
		root->right->left = new BinaryTreeNode(-12);
		root->right->right = new BinaryTreeNode(9);
		int max_sum = 0;
		test_tree.find_max_sum_of_nodes(root, max_sum);
		cout << "Max sum of the tree is: " << max_sum << endl;
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
	void test_scenario4(){
		BinaryTree test_tree;
		cout << endl << "Find Max Sum of from single branch:" << endl;
		BinaryTreeNode* root = new BinaryTreeNode(6);
		root->left = new BinaryTreeNode(10);
		root->left->right = new BinaryTreeNode(-5);
		root->left->right->right = new BinaryTreeNode(4);
		
		root->right = new BinaryTreeNode(4);
		root->right->right = new BinaryTreeNode(-6);
		root->right->right->right = new BinaryTreeNode(7);
		int max_sum = 0;
		test_tree.find_max_sum_of_nodes(root, max_sum);
		cout << "Max sum of the tree is: " << max_sum << endl;
	}
	void test_scenario5(){
		BinaryTree test_tree;
		cout << endl << "Find Max Sum of symetrical tree" << endl;
		BinaryTreeNode* root = new BinaryTreeNode(6);
		root->left = new BinaryTreeNode(-2);
		root->left->left = new BinaryTreeNode(10);
		root->right = new BinaryTreeNode(-2);
		root->right->right = new BinaryTreeNode(10);
		int max_sum = 0;
		test_tree.find_max_sum_of_nodes(root, max_sum);
		cout << "Max sum of the tree is: " << max_sum << endl;
	}
	void test_scenario6(){
		BinaryTree test_tree;
		cout << endl << "Find Max Sum of a stump (tree with no subtrees)" << endl;
		BinaryTreeNode* root = new BinaryTreeNode(6);
		int max_sum = 0;
		test_tree.find_max_sum_of_nodes(root, max_sum);
		cout << "Max sum of the tree is: " << max_sum << endl;
	}
	
	void test_scenario7(){
		BinaryTree test_tree;
		cout << endl << "Find Max Sum of dirt (empty tree)" << endl;
		BinaryTreeNode* root = NULL;
		int max_sum = 0;
		test_tree.find_max_sum_of_nodes(root, max_sum);
		cout << "Max sum of the tree is: " << max_sum << endl;
	}

	void run_tests() {
		test_scenario0();
		test_scenario4();	
		test_scenario5();
		test_scenario6();
		test_scenario7();
	}
};

int main() {	
	BinaryTreeTest test1;
	test1.run_tests();
}
