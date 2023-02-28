#include "Poly.h"
#include <iostream>
#include <math.h>

Poly::Poly()
{
	// Process: Create a dummy header
	// No need to define additional items
	head = new PolyNode(-1,0,NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)  // O(n) where n = deg.size()
{
	// Test:
	if ((int)deg.size() != (int)coeff.size()) { throw std::invalid_argument("Coeffs and degs vectors are not the same size!"); }
	// Process:
	// 1. Set the lastmost node with tail to NULL
	// 2. Create Nodes from lower pos in the list, until hit 0. Set last to curr next
	// 3. Set to dummyheader next
	//
	PolyNode* currNode = NULL, * tempNode;
	if ((int)deg.size() == 0) { head = new PolyNode(-1, 0, currNode); return; }
	currNode = new PolyNode(deg[(int)deg.size() - 1], coeff[(int)deg.size() - 1], NULL);

	if ((int)deg.size() == 1) { head = new PolyNode(-1, 0, currNode); return; }

	for (int i = (int)deg.size() - 2; i >= 0; i--) {
		tempNode = new PolyNode(deg[i], coeff[i], currNode);
		currNode = tempNode;
	}

	head = new PolyNode(-1, 0, currNode);

}

Poly::~Poly()  // O(n) where n = # of PNodes
{
	// Method: Delete each of the nodes, making sure to store next before deletion
	// Note: only non-native memebers need to be deleted (maxDegree gets deleted automatically)
	PolyNode* currPtr = head, * nextPtr;
	while (currPtr->next != NULL) {
		nextPtr = currPtr->next;
		delete currPtr;
		currPtr = nextPtr;
	}
	delete currPtr;
}

void Poly::addMono(int i, double c) // O(n) where n = # of nodes
{
	// Process:
	// 1. Check each of the nodes and note the degree
	// 2. Once currPtr->deg is greater than i, and currPTr->next->deg is less than 
	// or equal to i, then:
	//		a. If next deg < i && c != 0, create new PolyNode and insert inbetween
	//		b. If next deg < i && c == 0, ignore
	//		c. If next deg = i && c != 0, edit next PolyNode
	//		d. If next deg = i && c == 0, delete next Poly node, connect curr to
	//		   next next before deleting
	// 3. If the current node is the last, then add to end

	//
	// Let x be a number greater than 4, and y be less than 4. Input i = 4, then the situations can be:
	// (current = c, current->next = c)
	// 
	// | c  | n | action  |
	//   x    x   ignore
	//   x    4   replace
	//   x    y   insert
	// ------------------------  // there will never a 4 or y in current, since it is avoided through the
	//   -1   x   ignore         // following steps:
	//   -1   4   replace
	//   -1   y   insert
	// ------------------------
	//   -1   N   insert
	//   x    N   insert

	PolyNode* currPtr = head;



	while (currPtr->next != NULL) {
		// x,x
		if (currPtr->next->deg > i) {
			currPtr = currPtr->next;
			continue;
		}
		// x,i
		else if (currPtr->next->deg == i) {
			currPtr->next->coeff += c;
			if (currPtr->next->coeff == 0) {
				PolyNode* tempNode = currPtr->next;
				currPtr->next = currPtr->next->next;
				delete tempNode;
			}
			return;
		}
		// x,y
		else if (currPtr->next->deg < i) {
			break;
		}
	}
	
	// If reached this state, while loop was broken, or had reached NULL.
	if (c == 0) { return; }
	PolyNode *tempNode = new PolyNode(i,c, currPtr->next);
	currPtr->next = tempNode;
	return;
}

void Poly::addPoly(const Poly& p) // O(n) where n = # of pnodes + # of input pnodes
{
	// Process:
	// 1. Track both heads using pointers - tracker for 'this' should be one step behind,
	//	  tracker for p should be on current
	// 2. Situations:
	//	  a. If current node in p is less than both this and this next, then increment this
	//	  b. If current node in p is less than this, and greater than next, add p to this next, 
	//       increment both
	//	  All cases below
	// 3. If this next has reached null, and there are still nodes in p, append to tail
	//    If p is null, then return
	//

	// Let x be a number greater than 4, and y be less than 4. Input i = 4, then the situations can be:
	// (current = c, current->next = c)
	// 
	// | c  | n | action  |
	//   x    x   increment this, p is still relevant and not discarded
	//   x    4   add coeffs to n, increment p, its done, increment if not 0 coeff in next
	//   x    y   insert inbetween this and this next, increment p and this
	// ------------------------  
	//   -1   x  ^^
	//   -1   4  ^^
	//   -1   y  ^^
	// ------------------------
	//   -1   N  all of p should be appended
	//   x    N  all of p should be appended
	// 
	//

	PolyNode* currPtr = head, * pcurrPtr = p.head->next;

	while (currPtr->next != NULL && pcurrPtr != NULL) {
		if (currPtr->next->deg > pcurrPtr->deg) {
			currPtr = currPtr->next;
			continue;
		}
		else if (currPtr->next->deg == pcurrPtr->deg) {
			currPtr->next->coeff += pcurrPtr->coeff;
			pcurrPtr = pcurrPtr->next;
			if (currPtr->next->coeff == 0) {
				PolyNode* tempNode = currPtr->next;
				currPtr->next = currPtr->next->next;
				delete tempNode;
				continue;
			}
			currPtr = currPtr->next;
		}
		else if (currPtr->next->deg < pcurrPtr->deg) {
			PolyNode* tempNode = new PolyNode(pcurrPtr->deg, pcurrPtr->coeff, currPtr->next);
			currPtr->next = tempNode;
			pcurrPtr = pcurrPtr->next;
			currPtr = currPtr->next;
		}
	}
	

	// If pcurrPtr is not null, create a duplicate node system for remaining nodes, and connect to tail
	if (pcurrPtr != NULL) {
		PolyNode* appendNode = new PolyNode(pcurrPtr->deg, pcurrPtr->coeff, NULL), *tracker = appendNode;
		pcurrPtr = pcurrPtr->next;
		while (pcurrPtr != NULL) {
			tracker->next = new PolyNode(pcurrPtr->deg, pcurrPtr->coeff, NULL);
			pcurrPtr = pcurrPtr->next, tracker = tracker->next;
		}

		currPtr->next = appendNode;
	}
	return;
}

void Poly::multiplyMono(int i, double c) // O(n) where n = # of pnodes
{
	// Process:
	// 1. Iterate through each node
	// 2. Add the degs, multiply the c
	// 
	// If c == 0, then delete all variables
	//


	if (c == 0) {
		PolyNode* currPtr = head->next, * delPtr;
		while (currPtr != NULL) { delPtr = currPtr, currPtr = currPtr->next, delete delPtr; }
		head->next = NULL;
		return;
	}

	PolyNode* currPtr = head;

	while (currPtr->next != NULL) {
		currPtr = currPtr->next;
		currPtr->deg += i; currPtr->coeff *= c;
	}
}

void Poly::multiplyPoly(const Poly& p) // O(n^3) where n = # of nodes on avg from input and current state
{
	// Process: Follow how polynomial multiplication normally works
	// 1. Loop over each node (complexity O(n^2))
	// 2. Multiply each node by every other node, and add it to current
	//

	PolyNode* currPtr = head->next, * delPtr = currPtr, * tempPtr;

	head->next = NULL;

	while (currPtr != NULL) {
		PolyNode* pcurrPtr = p.head->next;
		while (pcurrPtr != NULL) {
			addMono(currPtr->deg + pcurrPtr->deg, currPtr->coeff * pcurrPtr->coeff);
			pcurrPtr = pcurrPtr->next;
		}
		currPtr = currPtr->next;
	}

	// Delete the nodes that were disconnected from head
	while (delPtr != NULL) {
		tempPtr = delPtr;
		delPtr = delPtr->next;
		delete tempPtr;
	}
	
}

void Poly::duplicate(Poly& outputPoly) // O(n) where n is equal to # of nodes in input a+ # of nodes in output
{
	// Process:
	// 0. Delete all values in outputPoly
	// 1. Iterate through each node
	// 2. Add to head
	
	PolyNode* currPtr = head, * pcurrPtr = outputPoly.head->next, * delNode;

	while (pcurrPtr != NULL) { delNode = pcurrPtr, pcurrPtr = pcurrPtr->next, delete delNode; }

	pcurrPtr = outputPoly.head;

	while (currPtr->next != NULL) {
		pcurrPtr->next = new PolyNode(currPtr->next->deg, currPtr->next->coeff, NULL);
		currPtr = currPtr->next, pcurrPtr = pcurrPtr->next;
	}

}

int Poly::getDegree() { return (head->next != NULL) ? head->next->deg : -1; } // O(1)

int Poly::getTermsNo() // O(n)
{
	// Set a counter, and iterate for every non-dummy node
	int counter = 0;
	PolyNode* currPtr = head;
	while (currPtr->next != NULL) {
		counter++;
		currPtr = currPtr->next;
	}
	return counter;//change this after completing this function
}

double Poly::evaluate(double x) // O(n)
{
	// Method: Loop through each node, and eval and add to a tracker
	double tracker = 0; PolyNode* currPtr = head;

	while (currPtr->next != NULL) {
		currPtr = currPtr->next;
		double t = pow(x, currPtr->deg) * currPtr->coeff;
		tracker += t;
	}

	return tracker;
}

std::string Poly::toString() // O(n)
{
	// Set returnString to the values for the degree
	std::string returnString = "";
	returnString += "degree=";
	returnString += std::to_string(head->next->deg);
	returnString += "; ";

	// Method: iterate over each node and add to the string	
	PolyNode* currPtr = head;

	while (currPtr->next != NULL) {
		currPtr = currPtr->next;
		returnString += "a(" + std::to_string(currPtr->deg) + ")=" + std::to_string(currPtr->coeff) + "; ";
	}
	returnString += "\n";

	return returnString;//change this after completing this function
}
