#include "HugeInteger.h"
#include <string>
#include <cmath>
#include <cstdlib>

HugeInteger::HugeInteger(const std::string& val) {
	// Goal: Store each digit as a char (ASCII Value) and manipulate this value
	// for functions and operations
	// Store length of val, set vars
	// std::cout << "Input: " << val << std::endl;
	size = val.length(); int i,x;
	// Check for zero size
	if (size < 1) {
		throw std::invalid_argument("The input string has a size less than 1");
	}
	//Allocate Space
	num = new char[size];

	// Check for negatives
	isNegative = (val[0] == '-');

	for (i = 0; i < size; i++) {
		// x is the value that needs to be filled in, accounting for the minus sign
		x = (isNegative) ? i + 1 : i;
		// Avoid assignment error
		if (x >= size) {
			break;
		}
		// If the ascii value of the input is less than or greater than the values for '0' 
		// and '9', then throw an error
		if (val[x] > 57 || val[x] < 48) {
			delete num;
			throw std::invalid_argument("The inputted string has characters that are not digits (ie. 0, 1, ..., 9)");
		}
		//  Assign value
		num[i] = val[x];
	}
	// Readjust size for negative numbers
	if (isNegative) {
		size--;
	}
	// std::cout << "Output: " << num << std::endl;
}

HugeInteger::HugeInteger(int n) {
	// Check if number is invalid
	if (n < 1) {
		throw std::invalid_argument("The inputted integer is equal to 0.");
	}
	// Allocate char array
	num = new char[n];
	// Make sure the first value is not 0 (set random idea from 0 - 8, then add 1)
	num[0] = (char)(std::rand() % 9) + 49; // <-- 1 + 48
	for (int i = 1; i < n; i++) {
		// Address any digit for the rest
		num[i] = (char)(std::rand() % 10) + 48;
	}

	size = n;
	isNegative = 0;
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	char* adderVal = h.num;
	char* currentVal = num;
	// ^ To ensure the num in this class isn't affected
	// 
	// Dealing with negatives:
	// If:
	// x + y   -> add(x,y)
	// -x + y  -> subtract(y,x)
	// x + -y  -> subtract(x,y)
	// -x + -y -> 0 - add(x,y)
	// 
	// Goal: add the ASCII values together. ('0' = 48, '9' = 57). Deal with overflows.
	// Find the minimum number of digits of the two numbers: these digits  will be
	// manipulated:
	// 
	// NOTE: The char is not a string, since it is not followed by a null character. 
	// Change to string at end
	// 
	// 1. Ensure that both values have the same number of digits (add 0's to the beginning)
	if (size < h.size) {
		// Convert either currentVal or adderVal
		char* tempHolder = new char[h.size];
		int x;
		// h.size - size = number of 0's
		for (x = 0; x < h.size - size; x++) {
			tempHolder[x] = '0';
		}
		// Fill the rest
		for (int y = 0; y < size; y++) {
			tempHolder[x + y] = currentVal[y];
		}
		// Set
		currentVal = tempHolder;
	}
	else if (size > h.size) {
		// Same as above
		char* tempHolder = new char[size];
		int x;
		for (x = 0; x < size - h.size; x++) {
			tempHolder[x] = '0';
		}
		for (int y = 0; y < h.size; y++) {
			tempHolder[x + y] = adderVal[y];
		}
		adderVal = tempHolder;
	}
	// std::cout << "Value 1: " << currentVal << ", Value 2: " << adderVal << std::endl;

	// Note: use the maximum of the two numbers for future loops
	int maxNum = (h.size > size) ? h.size : size;
	int asciiVal;

	// 2. Add the ASCII values (one can remain as the native ASCII, the other has to be 
	// subtracted. ('0' = 48, '9' = 57)
	int i;
	for (i = maxNum - 1; i >= 0; i--) {
		// Extract ASCII value (subtract '0' from one of the values)
		asciiVal = (int)currentVal[i] + (int)adderVal[i] - 48;
		// If value is above '9', carry one digit over
		if (asciiVal > 57) {
			asciiVal = asciiVal - 10;
			// Convert currentVal to asciiVal
			currentVal[i] = asciiVal;
			// If the last digit requires a carry, create a new char array with extra space
			if (i == 0) {
				char* tempHolderTwo = new char[maxNum + 1];
				// Carried digit:
				tempHolderTwo[0] = '1';
				for (int k = 0; k < maxNum; k++) {
					tempHolderTwo[k + 1] = currentVal[k];
				}
				// Replace CurrentVal, increment maxNum (required for string change)
				currentVal = tempHolderTwo;
				maxNum++;
			}
			// Else, simply add one to the previous char
			else {
				currentVal[i - 1] = currentVal[i - 1] + 1;
			}
		}
		else {
			currentVal[i] = asciiVal;
		}
	}

	// Convert to string (because there is no null value) - could be done with char array too
	std::string stringVal = "";
	for (int n = 0; n < maxNum; n++) {
		stringVal = stringVal + currentVal[n];
	}
	return HugeInteger(stringVal);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	// Dealing with negatives
	// If:
	// x - y   = subtract(x,y)
	// -x - y  = 0 - (add(x,y))
	// x - -y  = add(x,y)
	// -x - -y = subtract(y,z)
	return HugeInteger("");
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// TODO
	return HugeInteger("");
}

int HugeInteger::compareTo(const HugeInteger& h) {
	// TODO
	return 0;
}

std::string HugeInteger::toString() {
	// Ensure that the last value is a null
	std::string returnval = ""; int i = 0;
	if (isNegative) {
		i++;
		returnval = returnval + (char) 45;
	}
	for (i = 0; i < size; i++) {
		returnval = returnval + num[i];
	}
	return returnval;
}
