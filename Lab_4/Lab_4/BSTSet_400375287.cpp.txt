#include "BSTSet.h"
#include "MyStack.h"
#include <iostream>
#include <vector>
#include <algorithm> 
#include <cstdlib>
using namespace std;




// ------------------------------------------------------------------------------------------------------
BSTSet::BSTSet()
{
	return;
	// Do nothing
}

BSTSet::BSTSet(const std::vector<int>& input)
{
	// Create a BST with the minimum height
	// Process:
	// 1. Order the list in increasing order
	// 1b. Delete repeats of variables in the list
	// 2. Create a recursive function that returns the middle number as the node, and reruns the
	// function with a split in the list. (See below)
	
	std::vector<int> sortedInputs(input.begin(), input.end());
	std::sort(sortedInputs.begin(), sortedInputs.end());

	for (int i = 0; i < (int) sortedInputs.size() - 1; i += 0) {
		if (sortedInputs[i] == sortedInputs[i + 1]) {
			sortedInputs.erase(sortedInputs.begin() + i);
			// Bring list back down since we don't want to skip a value
		}
		else { i++; }
	}

	root = build(sortedInputs, 0, (int) sortedInputs.size() - 1); // This size parameter has to be passed in to recursive function, as it is dependent on knowing
	// Where the function starts and ends in terms of a subtree
}

TNode* BSTSet::build(const std::vector<int>& input, int lowest, int highest) {
	// Recursive function that returns a root node that can be used as subtree too as necessary.
	if (highest < lowest) { return NULL; }

	int top = (lowest + highest) / 2;
	TNode* newRoot = new TNode(input[top], NULL, NULL);

	newRoot->left = build(input, lowest, top - 1);
	newRoot->right = build(input, top + 1, highest);

	return newRoot;

}

BSTSet::~BSTSet()
{
	// Recurse through each node, and delete their children, before deleting them;
	deleteNode(root);
}

void BSTSet::deleteNode(TNode* input) {
	if (input != NULL) {
		deleteNode(input->left);
		deleteNode(input->right);
		delete input;
	}
}

// ------------------------------------------------------------------------------------------------------
bool isInRecurse(int v, TNode* current); // Implimentation below

bool BSTSet::isIn(int v)
{
	// Go right if value is smaller, go left if value is bigger. If found value, return
	TNode* temp = root;
	// Boundary Case: root is null
	if (temp == NULL) { return false; }
	// Recurse over each value
	return isInRecurse(v, root);
}

bool isInRecurse(int v, TNode* current) {
	if (current == NULL) { return false; }
	if (v == (int) current->element) { return true; }
	if (v < current->element && current->left != NULL) { return isInRecurse(v, current->left); }
	if (v > current->element && current->right != NULL) { return isInRecurse(v, current->right); }
	return false;
}

// ------------------------------------------------------------------------------------------------------
void BSTSet::add(int v)
{
	root = insert(root, v);
}

TNode* BSTSet::insert(TNode* node, int v) {
	// Process: If current node = v, return
	// If current node is null, set current node to the value, and balance if necessary.
	// If not equal, traverse the tree

	if (node == NULL) { return new TNode(v, NULL, NULL); }
	if (node->element == v) { return node; }

	if (v > node->element) { node->right = insert(node->right, v); }
	if (v < node->element) { node->left = insert(node->left , v); }

	

	//if (abs(nodeHeight(node->right) - nodeHeight(node->left)) > 1 && (node->right == NULL || node->left == NULL)) { 
	//	TNode *temp = balance(node); 
	//	delete node;
	//	node = temp;
	//}

	return node;

}

void returnBSTVals(TNode* node, std::vector<int> *appendList) {
	if (node == NULL) { return; }
	returnBSTVals(node->left, appendList);
	appendList->push_back(node->element);
	returnBSTVals(node->right, appendList);

}

TNode* BSTSet::balance(TNode* singleChildNode) {
	std::vector<int> childnodenums{};

	returnBSTVals(root, &childnodenums);
	for (int i = 0; i < childnodenums.size(); i++) {
		std::cout << childnodenums[i] << ", ";
	}
	std::cout << std::endl;
	TNode* subtree = build(childnodenums, 0, (int) childnodenums.size() - 1);
	return subtree;
}

bool BSTSet::remove(int v)
{
	// Process:
	// If the value is found in the tree, remove, and replace with highest value on the left side
	return removeNode(v, root, NULL); //change this after completing this function
}

bool BSTSet::removeNode(int v, TNode* node, TNode *parentNode) { // direction can be l or r for left or right
	if (node == NULL) { return false; }
	// Continue down tree if value not found
	if (v < node->element) {
		return removeNode(v, node->left, node);
	}
	// Continue down tree if value not found
	else if (v > node->element) {
		return removeNode(v, node->right, node);
	}
	// Delete a node that has two children
	else if (node->left != NULL && node->right != NULL) {
	    TNode* currPtr = node->right;
		while (currPtr->left != NULL) {
			currPtr = currPtr->left;
		}	
		node->element = currPtr->element;
		// Delete the smallest variable after replacement
		return removeNode(node->element, node->right, node);
	}
	else {
		if (node->left != NULL) {
			node->element = node->left->element;
			TNode* delNode = node->left;
			node->left = NULL;
			delete delNode;
		}
		else if (node->right != NULL){
			node->element = node->right->element;
			TNode* delNode = node->right;
			node->right = NULL;
			delete delNode;
		}
		else {
			if (parentNode == NULL) {
				delete root; root = NULL;
			}
			else {
				if (parentNode->right->element == v) {
					delete parentNode->right; parentNode->right = NULL;
				}
				else if (parentNode->left->element == v) {
					delete parentNode->left; parentNode->left = NULL;
				}
			}
		}
	}
	return true;
}

void BSTSet::addToUnion(TNode* node) {
	if (node == NULL) { return; }
	addToUnion(node->left);
	add(node->element);
	addToUnion(node->right);
}

void BSTSet::Union(const BSTSet& s)
{
	addToUnion(s.root);
}

void BSTSet::addIfIntersect(TNode** intersectRoot, TNode* assessNode) {
	if (assessNode == NULL) { return; }
	addIfIntersect(intersectRoot, assessNode->left);
	addIfIntersect(intersectRoot, assessNode->right);
	
	if (isIn(assessNode->element)) {
		*intersectRoot = insert(*(intersectRoot), assessNode->element);
	}

}

void BSTSet::intersection(const BSTSet& s)
{
	// Create a new TNode root
	// Add the values that intersect to this node using the insert function.

	TNode* newRoot = NULL;
	addIfIntersect(&newRoot, s.root);

	deleteNode(root);
	root = newRoot;

}

void BSTSet::returnNotIn(TNode* currNode, TNode* tester, TNode** output) {
	if (currNode == NULL) { return; }
	
	returnNotIn(currNode->left, tester, output);
	returnNotIn(currNode->right, tester, output);
	if (isInRecurse(currNode->element, tester)) {
		return;
	}
	else {
		*output = insert(*(output), currNode->element);
	}
}

void BSTSet::difference(const BSTSet& s)
{
	// Check if the values are in this and s (intersect), if they are, delete
	TNode* newRoot = NULL;
	TNode* replaceNode = NULL;
	addIfIntersect(&newRoot, s.root);
	returnNotIn(root, newRoot, &replaceNode);
	deleteNode(root);
	root = replaceNode;
}

int sizeRecurse(TNode* node) {
	if (node == NULL) { return 0; }
	return 1 + sizeRecurse(node->left) + sizeRecurse(node->right);
}

int BSTSet::size()
{
	
	return sizeRecurse(root); //change this after completing this function
}

int BSTSet::height()
{	
	return nodeHeight(root);
}

int BSTSet::nodeHeight(TNode* node) {
	if (node == NULL) { return -1; }
	if (node->left == NULL && node->right == NULL) {
		return 0;
	}
	int leftHeight = nodeHeight(node->left);
	int rightHeight = nodeHeight(node->right);
	return (((leftHeight > rightHeight) ? leftHeight : rightHeight) + 1);
}

// create and use class MyStack
void BSTSet::printNonRec()
{
	if (root == NULL) {
		return;
	}

	MyStack s = MyStack();

	TNode* curr = root;

	while (curr != NULL || s.isEmpty() == false) {
		while (curr != NULL) {
			s.push(curr);
			curr = curr->left;
		}
		curr = s.pop();
		cout << curr->element << ",";
		curr = curr->right;


	}

 //change this after completing this function
}

// Do not modify following provided methods

void BSTSet::printBSTSet()
{
	if (root == NULL)
		std::cout << "";
	else {
		printBSTSet(root);
	}
}

void BSTSet::printBSTSet(TNode* t)
{
	if (t != NULL) {
		printBSTSet(t->left);
		std::cout << t->element << ",";
		printBSTSet(t->right);
	}
}
