#include "HugeInteger.h"
#include <string>
#include <cstdlib>

HugeInteger::HugeInteger(const std::string& val) {
	// Goal: Store each digit as a char (ASCII Value) and manipulate this value
	// for functions and operations
	// Store length of val, set vars
	// std::cout << "Input: " << val << std::endl;
	size = (int) val.length(); int i,x;
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
		if (i >= size) { break; }
		// Avoid assignment error
		if (x >= size) {
			break;
		}
		// If the ascii value of the input is less than or greater than the values for '0' 
		// and '9', then throw an error
		if (val[x] > 57 || val[x] < 48) {
			delete num;
			std::string error = "The inputted string has characters that are not digits (ie. 0, 1, ..., 9). Inputted Value: " + val + ";\tThis value is " + ((isNegative) ? "negative." : "not negative.");
			throw std::invalid_argument(error);
		}
		//  Assign value
		num[i] = val[x];
	}
	// Readjust size for negative numbers
	if (isNegative) {
		size--;
	}
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

/*   std::string tempVal = ""; int o;
	 for (o = 0; o < h.size; o++) {
		 tempVal = tempVal + h.num[o];
	 }
	HugeInteger tempH = HugeInteger(tempVal);
	tempH.isNegative = h.isNegative;
	std::cout << "Testing: " << toString() << " + " << tempH.toString() << std::endl;
	std::cout << size << " " << h.size << std::endl; */
	// 
	// 
	// ^ To ensure the num in this class isn't affected
	// 
	// Dealing with negatives:
	// If:
	// x + y   -> add(x,y)
	// -x + y  -> subtract(y,x)
	// x + -y  -> subtract(x,y)
	// -x + -y -> 0 - add(x,y) (find the add, then set isNegative to true)
	// 
	if (isNegative) {
		// Get a new HugeInteger value that does not have a negative
		HugeInteger nonCurrent = HugeInteger(toString());
		nonCurrent.isNegative = 0;
		// Convert the input HugeInteger value into a non negative value
		std::string nonHVal = ""; int i;
		for (i = 0; i < h.size; i++) {
			nonHVal = nonHVal + h.num[i];
		}
		// Create the new HugeInteger value
		HugeInteger nonH = HugeInteger(nonHVal);
		if (h.isNegative) {
			// Do the base addition
			HugeInteger returnval = nonCurrent.add(nonH);
			// Make it negative
			returnval.isNegative = 1;
			return returnval;
		}
		else {
			// Convert into new HugeInteger
			std::string newHVal = ""; int i;
			for (i = 0; i < h.size; i++) {
				newHVal = newHVal + h.num[i];
			}
			// Make new HugeInteger value
			HugeInteger newH = HugeInteger(newHVal);
			// Do subtraction
			HugeInteger returnval = nonH.subtract(nonCurrent);
			return returnval;
		}
	} else{
		if (h.isNegative) {
			// Convert the input HugeInteger value into a non negative value
			std::string nonHVal = ""; int i;
			for (i = 0; i < h.size; i++) {
				nonHVal = nonHVal + h.num[i];
			}
			// Create the new HugeInteger value
			HugeInteger nonH = HugeInteger(nonHVal);
			return subtract(nonH);
		}
	}
	// 
	// Goal: add the ASCII values together. ('0' = 48, '9' = 57). Deal with overflows.
	// Find the minimum number of digits of the two numbers: these digits  will be
	// manipulated:
	// 
	// NOTE: The char is not a string, since it is not followed by a null character. 
	// Change to string at end
	// 
	char* tempHolder;
	// 1. Ensure that both values have the same number of digits (add 0's to the beginning)
	if (size < h.size) {
		// Convert either currentVal or adderVal
		tempHolder = new char[h.size];
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
		tempHolder = new char[size];
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
	std::string tempVal = ""; int o;
	for (o = 0; o < h.size; o++) {
		tempVal = tempVal + h.num[o];
	}
	HugeInteger tempH = HugeInteger(tempVal);
	tempH.isNegative = h.isNegative;

	// std::cout << "Testing: " << toString() << " - " << tempH.toString() << std::endl;
	// Dealing with negatives
	// If:
	// x - y   = subtract(x,y)
	// -x - y  = 0 - (add(x,y))
	// x - -y  = add(x,y)
	// -x - -y = subtract(y,x)
	// Goal: subtract the ASCII values from each other. Deal with carries
	// Use the same method that applies for long form subtraction
	if (isNegative) {
		// Create new value for h
		std::string newHVal = ""; int i;
		for (i = 0; i < h.size; i++) {
			newHVal = newHVal + h.num[i];
		}
		HugeInteger newH = HugeInteger(newHVal);
		newH.isNegative = 0;

		// Create new value for this
		HugeInteger thisVal = HugeInteger(toString());
		thisVal.isNegative = 0;
		if (h.isNegative) {
			return (newH.subtract(thisVal));
		}
		else {
			HugeInteger returnval = thisVal.add(newH);
			returnval.isNegative = 1;
			return returnval;
		}
	}
	else if (h.isNegative) {
		// Create new value for h
		std::string newHVal = ""; int i;
		for (i = 0; i < h.size; i++) {
			newHVal = newHVal + h.num[i];
		}
		HugeInteger newH = HugeInteger(newHVal);
		newH.isNegative = 0;
		return (add(newH));
	}
	// If the current value is smaller than the input, subtract in the opposite pattern,
	// and make negative after
	// for: 90
	//     -82
	//   =   8
	// for: 80
	//     -92
	//   = -12
	// 
	// If in x - y, y is larger than x, return 0 - subtract(y,x)

	bool reorg = 0;
	if (h.size > size) { reorg = 1; }
	if (h.size == size) {
		int t = 0;
		while (h.num[t] == num[t]) {
			t++;
		}
		if (h.num[t] > num[t]) {
			reorg = 1;
		}
	}

	if (reorg) {
		// Return 0 - subtract(y,x)
		// Create new value for h
		std::string newHVal = ""; int i;
		for (i = 0; i < h.size; i++) {
			newHVal = newHVal + h.num[i];
		}
		HugeInteger newH = HugeInteger(newHVal);
		// Create new value for this
		HugeInteger returnval = newH.subtract(HugeInteger(toString()));
		returnval.isNegative = 1;
		return returnval;
	}
	// Reassign num to avoid changing current private members
	char* currentVal = num;
	char* subtractVal = h.num;
	char* tempVal;

	// Assign 0's to begginning of char array if smaller than max
	if (size > h.size) {
		char* tempVal = new char[size]; int x;
		for (x = 0; x < size - h.size; x++) {
			tempVal[x] = '0';
		}
		for (int y = 0; y < h.size; y++) {
			tempVal[x + y] = h.num[y];
		}
		subtractVal = tempVal;
	}
	// Run the subtract algorithm, similar to add, work with ASCII characters
	// ('0' = 48, '9' = 57)
	int asciiVal;
	for (int i = size - 1; i >= 0; i--) {
		// Subtract ASCII
		asciiVal = (int)currentVal[i] - (int)subtractVal[i] + 48;
		if (asciiVal < 48) {
			if (i == 0) { break; }
			asciiVal = asciiVal + 10;
			currentVal[i - 1] --;
		}
		currentVal[i] = asciiVal;
	}
	// Convert to string (because there is no null value) - could be done with char array too
	std::string stringVal = "";
	for (int n = 0; n < size; n++) {
		stringVal = stringVal + currentVal[n];
	}

	return HugeInteger(stringVal);
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {
	// Goal: Mimmic how long multiplication is performed
	//  34
	// *17
	// =
	// 238
	// 340
	// +
	// 578
	// Check if there is only one negative - the result has to be negative if this is the case
	bool relNegative = (h.isNegative != isNegative);

	// 1. Setup a int array that can be used to add values to
	// Did not use .add() function as it has unnecessary steps that takes up a lot of time
	int* resultArray = new int[size + h.size];
	int i, j;
	for (i = 0; i < size + h.size; i++) {
		resultArray[i] = 0;
	}

	// Reverse the char arrays
	char *reversedThis = new char[size];
	for (i = 0; i < size; i++) {
		reversedThis[i] = num[size - i - 1];
	}
	
	char* reversedH = new char[h.size];
	for (i = 0; i < h.size; i++) {
		reversedH[i] = h.num[h.size - i - 1];
	}
	// 2. Set each of the digits to the right number. Remember - assign digits one space to the left
	// if the digit that is being manipulated is increased
	for (i = 0; i < size; i++) {
		for (j = 0; j < h.size; j++) {
			resultArray[i + j] += (reversedThis[i] - 48) * (reversedH[j] - 48);
			resultArray[i + j + 1] += resultArray[i + j] / 10;
			resultArray[i + j] = resultArray[i + j] % 10;
		}
	}

	// 3. Convert char array into string
	std::string returnValwithZero = "";
	for (i = 0; i < size + h.size; i++) {
		returnValwithZero = (char) (resultArray[i] + 48) + returnValwithZero;
	}

	// Also remove 0's
	std::string returnVal = ""; bool isFirstDigit = 1;
	for (i = 0; i < size + h.size; i++) {
		if (returnValwithZero[i] == '0' && isFirstDigit) continue;
		else isFirstDigit = 0;
		returnVal = returnVal + returnValwithZero[i];
	}
	
	delete[] reversedThis;
	delete[] reversedH;

	HugeInteger returnInteger = HugeInteger(returnValwithZero);
	returnInteger.isNegative = relNegative;
	return returnInteger;
}

int HugeInteger::compareTo(const HugeInteger& h) {
	int multiplyingfactor = 1;
	if (isNegative && !h.isNegative) {
		return -1;
	}
	else if (!isNegative && h.isNegative) {
		return 1;
	}
	else if (isNegative && h.isNegative) {
		multiplyingfactor = -1;
	}
	// If one of the numbers has more digits, the answer is obvious
	if (size > h.size) {
		return 1 * multiplyingfactor;
	}
	else if (h.size > size) {
		return -1 * multiplyingfactor;
	}
	else if (size == h.size){
		// For one's with the same length, check each digit, and return 
		for (int i = 0; i < size; i++) {
			if (num[i] > h.num[i]) {
				return 1 * multiplyingfactor;
			}
			else if (num[i] < h.num[i]) {
				return -1 * multiplyingfactor;
			}
		}
	}

	return 0;
}

std::string HugeInteger::toString() {
	// Ensure that the last value is a null
	std::string returnval = ""; int i = 0; bool isFirstDigit = 1;
	if (isNegative) {
		i++;
		returnval = returnval + (char) 45;
	}
	for (i = 0; i < size; i++) {
		if (num[i] == '0' && isFirstDigit) {
			continue;
		}
		isFirstDigit = 0;
		returnval = returnval + num[i];
	}
	if (returnval == "-" || returnval == "") {
		returnval = "0";
	}

	return returnval;
}
