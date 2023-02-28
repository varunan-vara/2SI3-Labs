#include "Poly.h"
#include <iostream>
#include <math.h>
 
Poly::Poly()
{
	// Default constructor
	// Impliment basic settings
	// Create DummyNode
	head = new PolyNode(-1, 0, NULL);
}

Poly::Poly(const std::vector<int>& deg, const std::vector<double>& coeff)
{
	// Impliment a setter system to create new nodes
	std::cout << "1";
	// Set degree
	// init counter
	int counter = 0;

	// Loop from front to back
	PolyNode* lastNode, * tempNode;

	// Process:
	// 1. Set the lastmost node with tail to NULL
	// 2. Create Nodes from lower pos in the list, until hit 0. Set last to curr next
	// 3. Set to dummyheader next
	//

	std::cout << "1";

	lastNode = new PolyNode(deg[deg.size() - 1], coeff[deg.size() - 1], NULL);

	for (int i = deg.size() - 2; i >= 0; i--) {
		tempNode = new PolyNode(deg[i], coeff[i], lastNode);
		lastNode = tempNode;
	}

	head = new PolyNode(-1, 0, lastNode);
}

Poly::~Poly()
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

void Poly::addMono(int i, double c)
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
	
	PolyNode* currPtr = head; // Instead of using bool to track change, return upon change
	std::cout << "Running\n";
	while (currPtr->next != NULL) {
		if (currPtr->next->deg > i) {
			currPtr = currPtr->next;
			continue;
		}
		if (currPtr->next->deg == i) {
			if (c == 0) {
				PolyNode* delPtr = currPtr->next;
				currPtr->next = currPtr->next->next;
				delete delPtr;
			}
			else {
				currPtr->next->coeff = c;
			}
			return;
		}
		if (currPtr->next->deg < i) {
			// breaks here, currPtr is equal to 'x' and next is 'y'
			break;
		}
	}

	// If broken in loop, then currPtr is x, else, last val is x

	if (c == 0) {
		NULL;
	}
	else {
		PolyNode* newPtr = new PolyNode(i, c, currPtr->next);
		currPtr->next = newPtr;
	}
}

void Poly::addPoly(const Poly& p)
{

	

	
}



void Poly::multiplyMono(int i, double c)
{
	// TODO
}

void Poly::multiplyPoly(const Poly& p)
{
	// TODO
}

void Poly::duplicate(Poly& outputPoly)
{
	// TODO
}

int Poly::getDegree()
{
	return head->next->deg;//change this after completing this function
}

int Poly::getTermsNo()
{
	// Method: iterate for each polynode (minus dummy node)
	int count = 0; PolyNode* currPtr = head;

	while (currPtr->next != NULL) {
		currPtr = currPtr->next;
		count++;
	}
	return count;//change this after completing this function
}

double Poly::evaluate(double x)
{
	// Method: loop over each polynode and add to final value

	PolyNode* currPtr = head;

	double returnval = 0.0;

	while (currPtr->next != NULL) {
		currPtr = currPtr->next;
		returnval = returnval + (pow(x, currPtr->deg) * currPtr->coeff);
	}

	return returnval;//change this after completing this function
}

std::string Poly::toString()
{
	// Set returnString to the values for the degree
	std::string returnString = "";
	returnString += "degree=";
	returnString += std::to_string(head->next->deg);
	returnString += "; ";

	// Method: iterate over each node and add to the string	
	PolyNode *currPtr = head;

	while (currPtr->next != NULL) {
		currPtr = currPtr->next;
		returnString += "a(" + std::to_string(currPtr->deg) + ")=" + std::to_string(currPtr->coeff) + "; ";
	}
	returnString += "\n";

	return returnString;//change this after completing this function
}
