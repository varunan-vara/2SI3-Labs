# 2SI3-Labs

A repository I used to manage my coursework for the course: COMPENG 2SI3 - Data Structures and Algorithms

Currently Stored: 
 - Labs 1 & 2 (both are same parts of one cumulative lab)
 - Lab 3 (Stored under Lab_3_alt - Lab 3 DOES NOT WORK)
 - Lab 4
 - Lab 5


### Approach for Lab 1

To store more than 64 bits, an ASCII character was used to store each digit. This could have also been done using binary values. 
When an std::string is inputted, it is converted to a char array, and this array is manipulated for any relevant functions. 
The class stores number of digits, char array, and a bool to indicate whether the function is negative. 
This allows for future functions to be implemented easier. 

### Approach for Lab 2

The strategy stayed largely the same from the previous lab, where items were accessed

### Approach for Lab 3

The strategy to store values in a Linked List is largely a given. Several while loops are used to infinitely iterate over a linked list until the right values are found.
The most important consideration was to identify an efficient manner to multiple, add, and subtract values. 
Multiply is straight forward, but add and subtract required a lot of manipulation of negative and positive values. 
See the code in Poly.cpp and the comments in particular to identify how this is done.
This lab was done in groups, and was also contributed to by Kris Modi.

### Approach fo Lab 4

The strategy for this lab largely resembled a common BST implementation, and therefore was very easy to implement. 

### Approach for Lab 5

Implementing the Hash Table was not too difficult, as it constituted general code to conduct primary and secondary hashing.
However, the class had to be able to test average probing for both insertions and false isIn() function calls. 
To accomplish this, default values are set, which can be manually changed, and for loops accomplish a very high number of tests, which is then averaged.
This was found to match very closely with theoretical values found for linear and quadratic coding.