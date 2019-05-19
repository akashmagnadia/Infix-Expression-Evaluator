//Name: Akash Magnadia
//Class: CS 211
//amagna2Project5Header.h

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>

using namespace std;

enum TokenType { Operator, Value, Invalid };

class myStack
{
private:
	int inUseValue;
	int capacityValue;
	int inUseOperator;
	int capacityOperator;

	int *valueStack;
	char *operatorStack;

	//file2
	void expand(myStack &stack, TokenType token, bool debugMode); //expand the size by 2 and make memory from them

public:
	myStack() { //default
		inUseValue = 0;
		capacityValue = 2;
		inUseOperator = 0;
		capacityOperator = 2;
		int *valueStack;
		char *operatorStack;
	}

	//file1
	void init(myStack &stack); //initialize by 2 capacity
	bool isEmpty(myStack stack, TokenType token); //returns true if the given token stack is empty
	void push(myStack &stack, char operator1, int num, TokenType token, bool debugMode); //push the value to the stack
	int topValue(myStack stack); //return the value on the top
	char topOperator(myStack stack); //return the operator on top
	void pop(myStack &stack, TokenType token); //pop the value on top of value stack or operator
	void reset(myStack &stack); //delete the arrays

	//file2
	static TokenType tokenReader(string c); //return the type of token it is
	void popAndEval(myStack &stack, bool debugMode); //evaluate the expression using two values and one operator
	void printStack(myStack stack); //used only for debugging purposes
};

