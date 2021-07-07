#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>


class TreeNode
{
public:
	int element;  // value in node
	TreeNode *left;  // left child
	TreeNode *right; // right child
	TreeNode *parent; // parent of node
	TreeNode(int e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) :
		element(e), left(l), right(r), parent(p) { }
};

class BinaryTree
{
public:
	TreeNode *root;  // root of tree
	bool insert(int & x, TreeNode * & t, TreeNode*  p);

	BinaryTree() {
		root = NULL;
	}

	//Insert item x into the tree using BST ordering
	virtual bool insert(int &x) { 
		return insert(x, root, NULL); 
	}

	// checks if the node is a leaf
	bool isLeaf(TreeNode *leaf) {
		if (leaf == NULL) { // Makes sure the node exists
			return false;
		}
		if (leaf->left == NULL && leaf->right == NULL) { // It is a leaf if there are no nodes attached to it
			return true;
		}
		return false;
	}

	void deleteNode(TreeNode *node) {
		TreeNode* parent = node->parent;
		if (node->left == NULL && node->right == NULL) { //no children
			if (parent->right == node) {
				parent->right = NULL;
			} else {
				parent->left = NULL;
			}
			node->element = NULL;
			node = NULL;
		} else if(node->left == NULL && node->right != NULL) { // only right child
			if (parent->right == node) {
				parent->right = node->right;
			} else {
				parent->left = node->right;
			}
			node->right->parent = parent;
			delete node;
		} else if (node->left != NULL && node->right == NULL) { // only left child
			if (parent->right == node) {
				parent->right = node->left;
			}
			else {
				parent->left = node->left;
			}
			node->left->parent = parent;
			delete node;
		}
		else if (node->left != NULL && node->right != NULL) { // two children
			TreeNode* successor = this->successor(node);
			successor->parent = parent;
			successor->left = node->left;
			successor->right = node->right;
			delete node;
		}
	}

	// function needed to set the initial rucusion value
	void fall() {
		fall(root);
	}
	// Deletes the tree through recurrsion
	void fall(TreeNode* temp) {
		if (temp == NULL) {
			return;
		}
		if (isLeaf(temp->right) || isLeaf(temp->left)) { //checks is right or left is a leaf
			// Deletes the leafs if they exist
			if (isLeaf(temp->right) && isLeaf(temp->left)) {
				delete temp->left;
				temp->left = NULL;

				delete temp->right;
				temp->right = NULL;
			} else if (isLeaf(temp->right)) {
				delete temp->right;
				temp->right = NULL;
			} else if (isLeaf(temp->left)) {
				delete temp->left;
				temp->left = NULL;
			}
		}
		// If there wasn't a leaf, jump to the left leaf
		if (temp->left != NULL) {
			fall(temp->left);
		}
		// Once you have recursed down to the end, start moving right
		if (temp->right != NULL) {
			fall(temp->right);
		}
		return;
	}
	// Find the given element in the tree that starts at nnode
	TreeNode* find(TreeNode *node, int i){
		if (node == NULL) {
			return NULL;
		}
		if (node->element == i) {
			return node;
		}

		TreeNode* found = find(node->left, i);
		if (found != NULL && found->element == i) {
			return found;
		}
		found = find(node->right, i);
		return found;

	}

	TreeNode *Right(TreeNode *node){
		if (node->left == NULL) {
			return node;
		}
		return Right(node->left);
	}

	TreeNode* parent(TreeNode *node) {
		if (node->parent == NULL) {
			return NULL;
		}
		if (node->parent->element > node->element) {
			return node->parent;
		}
		return parent(node->parent);
	}

	TreeNode *successor(TreeNode* node) {
		if (node->right != NULL) {
			return Right(node->right);
		} else {
			return parent(node);
		}
	}

	std::vector<int> printOrder(TreeNode* cur, int type, std::vector<int> &list) {
		if (cur == NULL) {
			return list;
		}
		if (type == 1) {
			list.push_back(cur->element);
		} 
		printOrder(cur->left, type, list);
		if (type == 2) {
			list.push_back(cur->element);
		}
		printOrder(cur->right, type, list);
		if (type == 3) {
			list.push_back(cur->element);
		}
		return list;
	}
	int getHeight( TreeNode *node) {
		int h = 0;
		if (node != NULL) {
			int l_height = getHeight(node->left);
			int r_height = getHeight(node->right);
			int max_height = std::max(l_height, r_height);
			h = max_height + 1;
		}
		return h;
	}
	int findBalanceFactor(TreeNode *node) {
		int right = getHeight(node->right);
		int left = getHeight(node->left);
		return std::abs(left - right);
	}

	void storeNodes(TreeNode* root, std::vector<TreeNode*>& nodes) {
		// Base case 
		if (root == NULL) {
			return;
		}
		// Store nodes in Inorder in a vector
		storeNodes(root->left, nodes);
		nodes.push_back(root);
		storeNodes(root->right, nodes);
	}

	// Construct the balanced tree
	TreeNode* buildTreeUtil(std::vector<TreeNode*>& nodes, int start, int end)
	{
		// base case 
		if (start > end) {
			return NULL;
		}
		// Get the middle element and make it root
		int mid = (start + end) / 2;
		TreeNode* newRoot = nodes[mid];

		newRoot->left = buildTreeUtil(nodes, start, mid - 1);
		newRoot->right = buildTreeUtil(nodes, mid + 1, end);

		return newRoot;
	}

	// Balances a tree
	TreeNode* balanceTree(TreeNode* root)
	{
		// Store all nodes
		std::vector<TreeNode*> nodes;
		storeNodes(root, nodes);

		// Constucts the tree from the vector
		int n = nodes.size();
		return buildTreeUtil(nodes, 0, n - 1);
	}
	bool insert(int& data, TreeNode*& node, TreeNode* parent) {
		if (node == NULL) {  // cout << "inserting " << data << endl;
			node = new TreeNode(data, NULL, NULL, parent);
			if (node == NULL) return false;
			return true;
		}
		if (data < node->element) return insert(data, node->left, node);
		return insert(data, node->right, node);
	}

};