#include "TestBSTSet.h"
#include <iostream>
#include <vector>
using namespace std;

int test()
{
	int max_run = 50;
	vector<int> max_size_array = { 1, 5, 10, 50 };

	double fullMark = 0;
	double totalMark = 0;
	double bonusFullMark = 0;
	double bonusTotalMark = 0;

	TestBSTSet tbs(max_run, max_size_array);

	tbs.testConstructor(totalMark, fullMark);
	tbs.testIsIn(totalMark, fullMark);
	tbs.testAdd(totalMark, fullMark);
	tbs.testRemove(totalMark, fullMark);
	tbs.testUnion(totalMark, fullMark);
	tbs.testIntersection(totalMark, fullMark);
	tbs.testDifference(totalMark, fullMark);
	tbs.testSize(totalMark, fullMark);
	tbs.testHeight(totalMark, fullMark);
	tbs.testPrintNonRec(totalMark, fullMark);
	tbs.testBonus(bonusTotalMark, bonusFullMark);

	cout << "********************************" << endl;
	cout << "*** FINAL TOTAL MARK IS " << totalMark << "/" << fullMark << " ***" << endl;
	cout << "*** FINAL BONUS MARK IS " << bonusTotalMark << "/" << bonusFullMark << " ***" << endl;
	cout << "********************************" << endl;

	return 0;
}

int main(void) {
	test();
	//std::vector<int> input1{ 5,3,1,2,4 };
	////std::vector<int> input2{ 7,3,6,5,4 };

	//BSTSet setOne = BSTSet(input1);
	////BSTSet setTwo = BSTSet(input2);

	//setOne.printNonRec();
}
