#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
	assert(evaluate("T^", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate("()T", pf, answer) == 1);
	assert(evaluate("T(F^T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F^F)", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 1);
	assert(evaluate("", pf, answer) == 1);
	assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
		&& pf == "FF!TF&&^" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
	cout << "Passed all tests" << endl;
}

bool isValid(char prev, char curr) {
	// Skip spaces
	if (curr == ' ') {
		cerr << "space detected";
		return true;
	}
	if (prev == '\0') {		// Start of expression
		cerr << "curr is " << curr << endl;
		return curr == 'T' || curr == 'F' || curr == '(' || curr == '!';
	}
	if (prev == 'T' || prev == 'F') {
		return curr == '!' || curr == '&' || curr == '^' || curr == ')';
	}
	if (prev == '(') {
		return curr == 'T' || curr == 'F' || curr == '(' || curr == '!';
	}
	if (prev == '!') {	// Unary operator, can stack
		return curr == 'T' || curr == 'F' || curr == '(' || curr == '!';
	}
	return false;
}

int evaluate(string infix, string& postfix, bool& result) {
	//Infix --> postfix conversion
	
	// Initialize postfix to empty
	postfix = "";
	// Initialize operator stack to empty
	stack<char> operatorStack;
	//For each character ch in the infix string 
	for (int i = 0; i < infix.length(); i++) {
		// Save previous non-space character off stack
		char prev = '\0';	// No previous character bc we start off with an empty stack
		char ch = infix[i];
		if (ch == ' ') {
			continue;
			cerr << "skip space";
		}
		if (!isValid(prev, ch)) {
			cerr << "invalid";
			return 1;
		}

		switch (ch) {
		case '!':
			postfix += ch;
			break;

		case '&':
			postfix += ch;
			break;

		case '^':
			postfix += ch;
			break;
		
		case '(':
			operatorStack.push(ch);
			break;

		case ')':
			while (!operatorStack.empty() && operatorStack.top() != '(') {
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(ch);
			break;
		}
	}
	// While the stack is not empty 
	while (!operatorStack.empty()) {
		postfix += operatorStack.top();
	}
	operatorStack.pop();

	// Evaluate postfix 
	
	// Initialize operand stack to be empty
	stack<char> operandStack;
	// For each character ch in the postfix string 
	for (int i = 0; i < infix.length(); i++) {
		char ch = postfix[i];
		if (ch == 'T' || ch == 'F') {
			operandStack.push(ch);
		}
		else {
			char operand2 = operandStack.top();
			operandStack.pop();
			char operand1 = operandStack.top();
			operandStack.pop();
			// Apply the operation that ch represents to operand1 and operand2
			// Rush the result onto the stack
			switch (ch) {
			case '&':
				result = operand1 & operand2;
				break;
			case '|':
				result = operand1 | operand2;
				break;
			case '^':
				result = operand1 ^ operand2;
				break;
			}
			operandStack.push(result);
		}
		return 0;
	}
	
}