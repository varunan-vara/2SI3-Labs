#include "MyStack.h"
#include <vector>
#include <iostream>

MyStack::MyStack() { 
	// Dummy Node
	head = new MyStackNode(NULL, NULL);
}
void MyStack::push(TNode* data) {
	// Replace the next data node at each push
	MyStackNode* n = new MyStackNode(data, head->next);
	head->next = n;
}
TNode* MyStack::pop() {
	// if empty, return -1, else, delete head next node and return its value
	if (isEmpty()) {
		return NULL;
	}
	else {
		TNode* returnval = head->next->data;
		MyStackNode* delNode = head->next;
		head->next = head->next->next;
		delete delNode;
		return returnval;
	}
}
int MyStack::isEmpty() { return (head->next == NULL); }