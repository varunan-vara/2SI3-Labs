#include "HashTableQuad.h"
#include "MiscFuncs.h"
#include <math.h>
#include <iostream>
using namespace std;

HashTableQuad::HashTableQuad(int maxNum, double load)
{
    // 1. Init 0 as the number of keys stored
    // 2. Init size to maxNum/load -> nearest larger prime
    // 3. Init maxLoadFactor
    // 4. Set values up to size in vector to 0

    keyNum = 0;
    // Temp init:
    size = 0;

    double tempSize = (double)maxNum / load;
    // Find if double value is greater than own int value: if so, double != x.000, so round up
    int roundUpInt = (tempSize > (int)tempSize) ? (int)tempSize + 1 : (int)tempSize;

    for (int i = roundUpInt; true; i++) {
        if (isNumPrime(i)) {
            size = i;
            break;
        }
    }

    //Insert 0 multiple times
    table.insert(table.end(), size, 0);

    maxLoadFactor = load;

    // Complexity of Θ(1) as it takes a constant amount of time, granted that vector allocation is constant 
    // too
}

void HashTableQuad::insert(int n)
{
    // Calculate the initial hash value, then impliment a for loop. The for loop handles secondary hashing
    // Quadratic hashing is handled in the "newHash" value within the for loop
    int hashValue = n % size; int newHash;
    for (int i = 0; i < size; i++) {
        newHash = (hashValue + (int)pow(i, 2)) % size;
        if (table[newHash] == n) {
            return;
        }

        if (table[newHash] == 0) {
            table[newHash] = n;
            keyNum++;
            break;
        }
    }

    if (((double)keyNum / (double)size) > maxLoadFactor)
        rehash();
    // Complexity of Θ(1) average and best case, since it is takes a constant time on average to look up 
    // a hash and any relevant secondary hashes. Worst case Θ(n) as if each value in the hash table has
    // to be read, this may be considered more complex
}

void HashTableQuad::rehash()
{
    // Find the new size, then create a new table
    std::vector<int> newTable;

    int newTableSize; //= size * 2 + 1;
    for (newTableSize = size * 2 + 1; true; newTableSize++) {
        if (isNumPrime(newTableSize))
            break;
    }

    newTable.insert(newTable.end(), newTableSize, 0);

    int hashVal;


    // This for loop handles handles each of the values from the old hash table
    for (int i = 0; i < table.size(); i++) {
        if (table[i] != 0) {
            hashVal = table[i] % newTableSize; int newHash;
            // This for loop inserts the values into the new hash table
            for (int j = 0; j < newTableSize; j++) {
                newHash = (hashVal + (int)pow(j, 2)) % newTableSize;
                if (newTable[newHash] == 0) {
                    newTable[newHash] = table[i];
                    break;
                }
            }
        }
    }
    table = newTable;
    size = newTableSize;

    // Complexity of Θ(n) in average and best case, as given the new table size, each of the old values has
    // to be assessed. Insertion process should be constant. Worst case of Θ(n^2) in rare situations where 
    // both many values have to be evaluated from the existing hash table on top of average case.
}

bool HashTableQuad::isIn(int n)
{
    int defaultHashValue = n % size; int newHash;

    for (int i = 0; i < size; i++) {
        newHash = (defaultHashValue + (int)pow(i, 2)) % size;
        if (table[newHash] == n) 
            return true;
        
        if (table[newHash] == 0)
            return false;
    }

    return false;

    // Complexity of Θ(1) average and best case, since it is takes a constant time on average to look up 
    // a hash and any relevant secondary hashes. Worst case Θ(n) as if each value in the hash table has
    // to be read, this may be considered more complex
}

void HashTableQuad::printKeys()
{
    for (int i = 0; i < size; i++) {
        if (table[i] != 0)
            std::cout << table[i] << ",";
    }
    std::cout << std::endl;
    // Complexity of Θ(n) as each value in the hash table has to be iterated through
}

void HashTableQuad::printKeysAndIndexes()
{
    for (int i = 0; i < size; i++) {
        std::cout << "[" << i << "]: " << table[i] << ",";
    }
    std::cout << std::endl;
    // Complexity of Θ(n) as each value in the hash table has to be iterated through
}

int HashTableQuad::getNumKeys() {
    // TODO, change following code after completing this function
    return keyNum;
    // Θ(1)
}

int HashTableQuad::getTableSize() {
    // TODO, change following code after completing this function
    return size;
    // Θ(1)
}

double HashTableQuad::getMaxLoadFactor() {
    // TODO, change following code after completing this function
    return maxLoadFactor;
    // Θ(1)
}

std::vector<double> HashTableQuad::simProbeSuccess()
{
    // Lambda values to be tested, as well as final result output
    std::vector<double> testLambdas{ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 }, results(9);
    // Pointer assigned to repeatedly delete and create new HashTables
    HashTableQuad* test;

    // Default values
    int runRepitition = 100;
    int testNum = 100000;

    // Define
    int i, j, k, x;
    double lambda, allRunsSum, allStepsSum;

    cout << "Test Started for Probe Success" << endl;

    // This for loop tests each lambda defined above (ensure results and testLambdas are equal in size
    for (i = 0; i < testLambdas.size(); i++) {
        lambda = testLambdas[i];
        allRunsSum = 0;
        // Handles the number of tests that are to be averaged
        for (j = 0; j < runRepitition; j++) {
            allStepsSum = 0;
            test = new HashTableQuad(testNum, lambda);
            // Handles the insertion of testNum times, ensuring the value doesn't already exist
            for (k = 0; k < testNum; k++) {
                x = rand() * rand();
                while (test->isIn(x)) {
                    x = rand() * rand();
                }
                allStepsSum += test->insertCount(x);
            }
            allRunsSum = (double)allStepsSum / (double)testNum;
            cout << "Successful Test for Lambda " << lambda << ": " << (double)allStepsSum / (double)testNum << std::endl;
            delete test;
        }
        results.at(i) = allRunsSum;
    }

    return results;

    // Complexity of Θ(1), if the above default values are constant. If testNum is not variable, then Θ(n)
}

int HashTableQuad::insertCount(int n)
{
    int count = 0;
    int hashValue = n % size; int newHash;
    for (int i = 0; i < size; i++) {
        count++;
        newHash = (hashValue + (int)pow(i, 2)) % size;
        if (table[newHash] == n) {
            return count;
        }

        if (table[newHash] == 0) {
            table[newHash] = n;
            keyNum++;
            break;
        }
    }

    if (((double)keyNum / (double)size) > maxLoadFactor)
        rehash();
    return count;
}