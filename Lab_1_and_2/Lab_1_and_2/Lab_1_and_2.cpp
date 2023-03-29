#include <iostream>
#include "TestHugeInteger.h"

using namespace std;
// Add code for comparing running time
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std::chrono;
using namespace boost::multiprecision;

void run() {
    // when test failed, the size of number <= NUM_DISPLAY, display the number
    unsigned int num_display = 1000;
    // iterate the MAX_SIZE_ARRAY MAX_RUN times
    unsigned int max_run = 50;
    // use for generating invalid string for constructor 1 (with string input)
    unsigned int max_invalid_string = 5;
    // different size for test
    vector<int> max_size_array = { 1,20,50,500,5000 };

    double totalMark = 0;

    string demoLab = "Lab2"; // set to Lab1 or Lab2

    TestHugeInteger thi(num_display, max_run, max_invalid_string, max_size_array);

    if (demoLab == "Lab1") {
        totalMark += thi.testConstructorString();
        totalMark += thi.testConstructorNumber();
        totalMark += thi.testPositiveAddition();
    }
    else {
        totalMark += thi.testAdditionSubtraction();
        totalMark += thi.testCompareTo();
        totalMark += thi.testMultiplication();
    }

    cout << "******************************" << endl;
    cout << "*** FINAL TOTAL MARK IS " << totalMark << " ***" << endl;
    cout << "******************************" << endl;

}

int testRandCase(int nOne, int nTwo, bool isNegOne, bool isNegTwo, std::string operation) {
    std::string output = (isNegOne) ? "-" : "", outputTwo = (isNegTwo) ? "-" : ""; int i, j;

    for (i = 0; i < nOne; i++) {
        if (i == 0) {
            output += (char)(rand() % 9 + 49);
        }
        else {
            output += (char)(rand() % 10 + 48);
        }
    }
    for (j = 0; j < nTwo; j++) {
        if (i == 0) {
            outputTwo += (char)(rand() % 9 + 49);
        }
        else {
            outputTwo += (char)(rand() % 10 + 48);
        }
    }

    HugeInteger one = HugeInteger(output), two = HugeInteger(outputTwo);
    cpp_int testOne(output), testTwo(outputTwo);
    if (operation == "add") {
        
    }
    else if (operation == "subtract") {

    }
    else if (operation == "multiply") {

    }
    else if (operation == "compare") {

    }
    else {
        cout << "Invalid operation string input" << endl;
    }
    return 0;
}

std::string runningtimecompare(int input, int m)
{
    int maxrun = m; // tune it such that durationms >= 500
    int maxnumints = 100; // at least 100
    system_clock::time_point starttime, endtime;
    double runtime = 0.0;
    double runtime_cpp_int = 0.0;
    double durationms = 0.0;
    int n = input; // measure the running time for various values of n, e.g., 10, 100, 500, 1000, 5000, 10000
    for (int numints = 0; numints < maxnumints; numints++) {
        HugeInteger huge1(n); //creates a random integer of n digits
        HugeInteger huge2(n); //creates a random integer of n digits
        cpp_int c1(huge1.toString());
        cpp_int c2(huge2.toString());
        starttime = system_clock::now();
        for (int numrun = 0; numrun < maxrun; numrun++) {
            int huge3 = huge1.compareTo(huge2);
        }
        endtime = system_clock::now();
        durationms = (duration<double, std::milli>(endtime - starttime)).count();
        runtime += durationms / ((double)maxrun);
        cout << "durationms: " << durationms << endl; // tune maxrun such that durationms >= 500
        starttime = system_clock::now();
        for (int numrun = 0; numrun < maxrun; numrun++) {
            int c3 = c1 > c2;
        }
        endtime = system_clock::now();
        durationms = (duration<double, std::milli>(endtime - starttime)).count();
        runtime_cpp_int += durationms / ((double)maxrun);
    }
    runtime = runtime / ((double)maxnumints);
    runtime_cpp_int = runtime_cpp_int / ((double)maxnumints);
    std::string result1 = "runing time for hugeinteger add with n=" + to_string(n) + " is:" + to_string(runtime) + " ms\n";
    std::string result2 = "runing time for cpp_int + with n=" + to_string(n) + " is:" + to_string(runtime_cpp_int) + " ms\n";
    cout << "runing time for hugeinteger add with n=" << n << " is:" << runtime << " ms" << endl;
    cout << "runing time for cpp_int + with n=" << n << " is:" << runtime_cpp_int << " ms" << endl;
    return result1 + result2;
}
int main() {

    std::vector<int> testNums{ 5,10,50,100,500,1000,5000,10000,50000 };
    std::string finalprint = "";

    for (int i = 0; i < testNums.size(); i++) {
        finalprint += runningtimecompare(testNums[i], 5000000/testNums[i]);

    }
    cout << endl << endl << endl << finalprint << endl;
    //testRandCase(10,15,1,0,"add");
    return 0;
        //Leave the rest of the main function unchanged
}