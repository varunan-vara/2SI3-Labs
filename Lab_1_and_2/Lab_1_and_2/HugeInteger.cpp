#include "HugeInteger.h"
#include <string>
#include <cmath>

HugeInteger::HugeInteger(const std::string& val) {
	// Goal: Store each digit as a char (ASCII Value) and manipulate this value
	// for functions and operations
	// Store length of val, set vars
	std::cout << val << "\n\n\n\n\n";
	size = val.length(); int i = 0;
	//Allocate Space
	num = new char[size];

	// Check for negatives
	isNegative = (val.at(0) == '-');
	if (isNegative) {
		i++;
	}

	for (i = i; i < size; i++) {
		// If the ascii value of the input is less than or greater than the values for '0' 
		// and '9', then throw an error
		if ((int)val.at(i) > 57 || (int)val.at(i) < 48) {
			throw std::invalid_argument("The inputted string has characters that are not digits (ie. 0, 1, ..., 9)");
		}
		*(num + i) = val.at(i);
	}
	if (isNegative) {
		size--;
	}
}

HugeInteger::HugeInteger(int n) {
	// Convert each digit into a char, then store it similar to the above constructor
	// Initialize a counter
	int counter = 0, i;
	std::string holder = "";

	// Find the remainder of the value at 10 (this is the last digit)
	// Then divide by 10 - now the loop has progressed to the next digit
	// Made into a string first, as it is easier to allocate space for a a char array
	while (n > 0) {
		int digit = n % 10;
		holder = std::to_string(digit) + holder;
		n = n / 10;
		counter++;
	}
	delete &holder;

	// Follow the first constructor method
	num = new char[size];
	size = holder.length();
	for (i = 0; i < size; i++) {
		*(num + i) = holder.at(i);
	}
}

HugeInteger HugeInteger::add(const HugeInteger& h) {
	char* adderVal = h.num;
	char* currentVal = num;
	// ^ To ensure the num in this class isn't affected
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

	// Note: use the maximum of the two numbers for future loops
	int maxNum = (h.size > size) ? h.size : size;

	// 2. Add the ASCII values (one can remain as the native ASCII, the other has to be 
	// subtracted. ('0' = 48, '9' = 57)
	int i;
	for (i = maxNum - 1; i >= 0; i--) {
		// Extract ASCII value (subtract '0' from one of the values)
		int asciiVal = (int)currentVal[i] + (int)adderVal[i] - 48;
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
	}

	// Convert to string (because there is no null value) - could be done with char array too
	std::string stringVal = "";
	for (int n = 0; n < maxNum; n++) {
		stringVal = stringVal + currentVal[n];
	}
	return HugeInteger(stringVal);
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {
	// TODO
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
	std::string returnval; int i = 0, max=size;
	if (isNegative) {
		i++;
		returnval = "-";
		max++;
	}
	for (i = 0; i < max; i++) {
		returnval = returnval + num[i];
	}
	return returnval;
}
