#ifndef MYSTACK_H_
#define MYSTACK_H_

#include "Tnode.h"

class MyStackNode {
public:
	TNode* data;
	MyStackNode* next;
	MyStackNode(TNode* d, MyStackNode* n) {
		data = d; next = n;
	}
};

class MyStack {
private:
	MyStackNode* head;
public:
	MyStack();
	void push(TNode* data);
	TNode* pop();
	int isEmpty();
};

#endif 