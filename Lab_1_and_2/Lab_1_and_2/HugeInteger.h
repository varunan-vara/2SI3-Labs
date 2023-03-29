#ifndef HUGEINTEGER_H_
#define HUGEINTEGER_H_
#include <iostream>

class HugeInteger
{
private:
	char* num;
	int size; // This is the number of digits stored
	bool isNegative;
public:
	// Required methods
	HugeInteger(const std::string& val);
	HugeInteger(int n);
	// ~HugeInteger();
	HugeInteger add(const HugeInteger& h);
	HugeInteger subtract(const HugeInteger& h);
	HugeInteger multiply(const HugeInteger& h);
	int compareTo(const HugeInteger& h);
	std::string toString();
};

#endif /* HUGEINTEGER_H_ */
