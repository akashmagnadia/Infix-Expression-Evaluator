//Author: Akash Magnadia

#include "pch.h"

void myStack::init(myStack &stack)
{
	stack.inUseValue = 0;
	stack.inUseOperator = 0;
	stack.capacityValue = 2;
	stack.capacityOperator = 2;
	stack.valueStack = new int[stack.capacityValue];
	stack.operatorStack = new char[stack.capacityOperator];
}

bool myStack::isEmpty(myStack stack, TokenType token) {
	if (token == Value) {
		if (stack.inUseValue == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	if (token == Operator) {
		if (stack.inUseOperator == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	return false; //default
}

void myStack::push(myStack &stack, char operator1, int num, TokenType token, bool debugMode)
{
	if (debugMode) {
		cout << endl << "Before Pushing: " << endl;
		stack.printStack(stack);
	}

	if (token == Value) {
		if (stack.capacityValue <= stack.inUseValue) {
			expand(stack, token, debugMode);
		}

		stack.inUseValue = stack.inUseValue + 1; //increase the value of inUse

		for (int i = stack.inUseValue - 1; i > 0; i--) {
			if (debugMode) {
				cout << endl << "Value - i : " << i << " --> " << "stack.valueStack[" << i << "] " << " is equal to " << stack.valueStack[i - 1] << endl;
			}
			stack.valueStack[i] = stack.valueStack[i - 1]; //shift all values to right
		}

		stack.valueStack[0] = num; //set the data to top
	}
	else if (token == Operator) {
		if (stack.capacityOperator <= stack.inUseOperator) {
			expand(stack, token, debugMode);
		}

		stack.inUseOperator = stack.inUseOperator + 1; //increase the value of inUse

		for (int i = stack.inUseOperator - 1; i > 0; i--) {
			if (debugMode) {
				cout << endl << "Operator - i : " << i << " --> " << "stack.operatorStack[" << i << "] " << " is equal to " << stack.operatorStack[i - 1] << endl;
			}
			stack.operatorStack[i] = stack.operatorStack[i - 1]; //shift all values to right
		}

		stack.operatorStack[0] = operator1; //set the data to top
	}
	else {
		return;
	}

	if (debugMode) {
		cout << endl << endl << "After Pushing: " << endl;
		stack.printStack(stack);
		cout << endl << endl;
	}
}

int myStack::topValue(myStack stack) {
	if (stack.isEmpty(stack, Value)) {
		cout << "Nothing on top. Value stack is empty. Returning -999 as default value. The final value maybe wrong." << endl;
		return -999;
	}
	return stack.valueStack[0];
}

char myStack::topOperator(myStack stack) {
	if (stack.isEmpty(stack, Operator)) {
		cout << "Nothing on top. Operator stack is empty. Returning ! as default value. The final value maybe wrong" << endl;
		return '!';
	}
	return stack.operatorStack[0];
}

void myStack::pop(myStack &stack, TokenType token) {
	if (token == Value) {
		if (isEmpty(stack, Value)) {
			cout << "Nothing to pop. Value stack is empty" << endl;
			return; //if value stack is empty
		}

		for (int i = 0; i < stack.inUseValue - 1; i++) {
			stack.valueStack[i] = stack.valueStack[i + 1]; //shift values to left
		}
		stack.inUseValue = stack.inUseValue - 1; //decrease the values being used
	}
	else if (token == Operator) {
		if (isEmpty(stack, Operator)) {
			cout << "Nothing to pop. Operator stack is empty" << endl;
			return; //if Operator stack is empty
		}

		for (int i = 0; i < stack.inUseOperator - 1; i++) {
			stack.operatorStack[i] = stack.operatorStack[i + 1]; //shift operators to left
		}
		stack.inUseOperator = stack.inUseOperator - 1; //decrease the values being used
	}
	else {
		cout << "Invalid valued passed to pop" << endl; // debug mode
		return;
	}
}

void myStack::reset(myStack &stack) {
	delete[] valueStack;
	delete[] operatorStack;
}


void myStack::expand(myStack &stack, TokenType token, bool debugMode)
{
	if (token == Value) {
		stack.capacityValue += 2;
		if (debugMode) {
			cout << endl << "expanding memory for value stack from " << stack.capacityValue - 2 << " to " << stack.capacityValue << endl;
		}

		int *tempArray = new int[stack.capacityValue];

		for (int i = 0; i < inUseValue; i++) {
			tempArray[i] = stack.valueStack[i];
		}

		delete[] stack.valueStack;
		stack.valueStack = tempArray;
	}
	else if (token == Operator) {
		stack.capacityOperator += 2;
		if (debugMode) {
			cout << endl << "expanding memory for operator stack from " << stack.capacityOperator - 2 << " to " << stack.capacityOperator << endl;
		}

		char *tempArray = new char[stack.capacityOperator];

		for (int i = 0; i < inUseOperator; i++) {
			tempArray[i] = stack.operatorStack[i];
		}

		delete[] stack.operatorStack;
		stack.operatorStack = tempArray;
	}
	else {
		return;
	}
}

TokenType myStack::tokenReader(string input) {
	if ((input == "+") || (input == "-") || (input == "*") || (input == "/") || (input == "(") || (input == ")")) {
		return Operator; //if its a operator
	}

	if (input == "") {
		return Invalid;
	}
	int num = atoi(input.c_str()); //convert to number

	if (errno == EDOM) {
		return Invalid; // invalid operator detected
	}


	//try {
	//	int num = atoi(input.c_str()); //convert to number
	//}
	//catch (invalid_argument) {
	//	return Invalid; // invalid operator detected
	//}

	return Value; //if the number check is passed then it has to be a number
}

void myStack::popAndEval(myStack &stack, bool debugMode) {
	char op = topOperator(stack); //grab the operator
	if (debugMode) {
		cout << "popping " << op << " from operator stack" << endl;
	}
	pop(stack, Operator); //pop that operator from operator stack

	int value1 = topValue(stack); //grab the number
	if (debugMode) {
		cout << "popping " << value1 << " from value stack" << endl;
	}
	pop(stack, Value); // pop the number from the value stack

	int value2 = topValue(stack); //grab the number
	if (debugMode) {
		cout << "popping " << value2 << " from value stack" << endl;
	}
	pop(stack, Value); // pop the number from the value stack

	int result = -1; //initalize the result variable

	if (debugMode) {
		cout << "Evaluating " << value2 << " " << op << " " << value1 << endl;
	}

	if (op == '+') {
		result = value2 + value1;
	}
	else if (op == '-') {
		result = value2 - value1;
	}
	else if (op == '*') {
		result = value2 * value1;
	}
	else { //the last one has to be division(/)
		result = value2 / value1;
	}

	if (debugMode) {
		cout << "Evaluation successful" << endl;
		cout << value2 << " " << op << " " << value1 << " = " << result << endl;
		cout << "Pushing the calculated value " << result << " to the value stack" << endl;
	}

	stack.push(stack, '!', result, Value, debugMode); //push the calculated value to the value stack
}

void myStack::printStack(myStack stack) {
	cout << "Value: ";
	for (int i = 0; i < stack.inUseValue; i++) {
		cout << stack.valueStack[i] << " ";
	}
	cout << endl << "Values in Value stack: " << stack.inUseValue;

	cout << endl << "Operator: ";
	for (int i = 0; i < stack.inUseOperator; i++) {
		cout << stack.operatorStack[i] << " ";
	}
	cout << endl << "Operators in Operator stack: " << stack.inUseOperator;
}

int main(int argc, char **argv)
{
	myStack stack; //myStack class
	TokenType token; //to store the tokens
	bool debugMode = false; //debug Mode

	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			debugMode = true;
		}
	}
	//debugMode = true; //to manually set to debug mode

	string input = " "; //initialization of string input

	//introdcution
	cout << "Command 'q' to quit the program" << endl;
	cout << "Command '?' to get help with how to use this program" << endl;
	cout << "Type in Expression to be calculated for example 2 + 1 + 1, which will give 4" << endl;
	while (getline(cin, input)) //keep reading until you can in the file
	{
		if (input.at(0) == 'q') { //if q is entered
			if (debugMode) {
				cout << "Resetting stacks" << endl;
			}

			stack.reset(stack);
			cout << "Quiting the program" << endl;
			break;
		}

		if (debugMode) {
			cout << "Initializing inUse, Capacity and arrays to be used" << endl;
		}

		stack.init(stack);

		int length = input.length(); //length of the input

		if (input.at(0) == '?') { //if help is needed
			cout << "Command 'q' to quit the program" << endl;
			cout << "Type in Expression to be calculated for example '2 + 1 + 1', which will give 4" << endl;
			cout << "This program only recognizes following operators: +, -, *, /, (, )" << endl;
			continue;
		}

		for (int i = 0; i < length; i++) {
			string current = ""; //a word or one might say part of expression

			while (input.at(i) != ' ') { //pick out individual words
				if ((input.at(i) == '(') || (input.at(i) == ')')) {
					current = input.at(i);
					break;
				}
				current.push_back(input.at(i));
				if (i + 1 < length) {
					if (input.at(i + 1) == ')') {
						break;
					}
				}
				i++;

				if (i >= length) {
					break;
				}
			}

			token = myStack::tokenReader(current); //get the token

			//following structural guide from proj5s19.pdf
			if (token == Value) {
				int tempNum = atoi(current.c_str()); //turning the current to int becasue it is guaranteed to be int

				if (errno == EDOM) {
					break; //if something is wrong with tempNum
				}

				if (debugMode) {
					cout << "Pushing " << tempNum << " to value stack" << endl;
				}
				stack.push(stack, '!', tempNum, Value, debugMode); //passing in ! just to fill even though not being used
			}

			if (token == Operator) {
				char tempOp = current.at(0); //convert it to char since the functions accept char

				if (tempOp == '(') { //if opening parenthesis is detected

					if (debugMode) {
						cout << tempOp << " detected" << endl;
						cout << "Pushing " << tempOp << " to operator stack" << endl;
					}
					stack.push(stack, tempOp, -1, Operator, debugMode);
				}

				if ((tempOp == '+') || (tempOp == '-')) { //if + or - is detected

					if (debugMode) {
						cout << tempOp << " detected" << endl;
					}

					while ((!(stack.isEmpty(stack, Operator))) &&
						((stack.topOperator(stack) == ('+')) || (stack.topOperator(stack) == ('-')) || (stack.topOperator(stack) == ('*')) || (stack.topOperator(stack) == ('/')))) {
						stack.popAndEval(stack, debugMode); //evaluate the expression
					}

					if (debugMode) {
						cout << "Pushing " << tempOp << " to operator stack" << endl;
					}
					stack.push(stack, tempOp, -1, Operator, debugMode); //push the current operator
				}

				if ((tempOp == '*') || (tempOp == '/')) { //if + or - is detected

					if (debugMode) {
						cout << tempOp << " detected" << endl;
					}

					while ((!(stack.isEmpty(stack, Operator))) && ((stack.topOperator(stack) == ('*')) || (stack.topOperator(stack) == ('/')))) {
						stack.popAndEval(stack, debugMode); //evaluate the expression
					}

					if (debugMode) {
						cout << "Pushing " << tempOp << " to operator stack" << endl;
					}
					stack.push(stack, tempOp, -1, Operator, debugMode); //push the current operator
				}

				if (tempOp == ')') { //if closing parenthesis is detected
					if (debugMode) {
						cout << tempOp << " detected" << endl;
					}

					while ((!(stack.isEmpty(stack, Operator))) && !(stack.topOperator(stack) == ('('))) {
						stack.popAndEval(stack, debugMode); //evaluate the expression
					}

					if (stack.isEmpty(stack, Operator)) {
						cout << "Error: ( is not at the end of the expression" << endl;
					}
					else {
						char tempOp2 = stack.topOperator(stack); //another temp operator variable
						if (debugMode) {
							cout << "Popping " << tempOp2 << " from operator stack" << endl;
						}

						stack.pop(stack, Operator); //pop ( when done with the expression inside ( )

					}
				}
			}
		}

		if (debugMode) {
			cout << endl; //add space between line between each thing computed
		}

		while (!(stack.isEmpty(stack, Operator))) {
			stack.popAndEval(stack, debugMode);
		}

		int result = stack.topValue(stack);
		cout << input << " = " << result << endl;

		if (debugMode) {
			cout << "Popping " << result << " from top of value stack to make it empty" << endl;
		}
		stack.pop(stack, Value); //popping from value

		if (debugMode) {
			cout << "Resetting stacks" << endl;
		}

		stack.reset(stack);
	}

	return 0;
}
