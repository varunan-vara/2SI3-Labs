#ifndef BSTSET_H_
#define BSTSET_H_

#include "TNode.h"
#include <vector>

class BSTSet
{
private:
	// must contain only one private field
	TNode* root = NULL;

public:
	// required constructors/destructor
	BSTSet();
	BSTSet(const std::vector<int>& input);
	~BSTSet();

	// required methods
	TNode* build(const std::vector<int>& input, int lowest, int highest);
	void deleteNode(TNode* input);
	bool isIn(int v);
	void add(int v);
	TNode* insert(TNode* node, int v);
	TNode* balance(TNode* singleChildNode);
	bool remove(int v);
	bool removeNode(int v, TNode* node, TNode* parentNodem);
	void addToUnion(TNode* node);
	void Union(const BSTSet& s);
	void addIfIntersect(TNode** intersectRoot, TNode* assessNode);
	void intersection(const BSTSet& s);
	void returnNotIn(TNode* currNode, TNode* tester, TNode** output);
	void difference(const BSTSet& s);
	int size();
	int height();
	int nodeHeight(TNode* node);
	void printNonRec(); // create and use class MyStack

	// provided recursive print method
	void printBSTSet();

	// Used for testing
	TNode* getRoot()
	{
		return root;
	}

private:
	// provided helper methods
	void printBSTSet(TNode* t);
};

#endif /* BSTSET_H_ */
