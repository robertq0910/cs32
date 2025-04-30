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
	assert(evaluate("!(!!!(!T))", pf, answer) == 0 && pf == "T!!!!!" && !answer);
	assert(evaluate("(!!!(!T))", pf, answer) == 0 && pf == "T!!!!" && answer);
	assert(evaluate("(!(!T)", pf, answer) == 1);
	assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer);
	
	cout << "Passed all tests" << endl;
}

bool isValid(char prev, char curr) {
	if (prev == '\0' || prev == '(') {		// Start of expression or parenthesis
		cerr << "curr is " << curr << endl;
		return curr == 'T' || curr == 'F' || curr == '(' || curr == '!';
	}
	// expression, must be followed by operator
	if (prev == 'T' || prev == 'F' || prev == ')') {
		return curr == '&' || curr == '^' || curr == ')';
	}
	// operator, must be followed by an expression
	return curr == 'T' || curr == 'F' || curr == '(' || curr == '!';
}

bool validateInfix(string const& infix) {
	// Save previous non-space character off stack
	char prev = '\0';	// No previous character bc we start off with an empty stack
	for (int i=0; i<infix.length(); i++) {
		char curr = infix[i];
		// Skip spaces
		if (curr == ' ') {
			continue;
		}

		if (!isValid(prev, curr)) {
			return false;
		}
		prev = curr;
	}
	return true;
}

// return: 1 when op1 has higher precendence than op2
// return: 0 when op1 has same precendence as op2
// return: -1 when op1 has lower precendence than op2
int compare(char op1, char op2) {
	if (op1 == '!') {
		return op2 == '!' ? 0 : 1;
	}

	if (op1 == '&') {
		switch (op2) {
		case '!':
			return -1;
		case '&':
			return 0;
		default: // ^
			return 1;
		}
	}

	if (op1 == '^') {
		return op2 == '^' ? 0 : -1;
	}

	return 0;
}

// Convert char to bool: 'T' => true; 'F' => false
bool char_2_bool(char ch) {
	return ch == 'T' ? true : false;
}

// Convert bool to char: true => 'T'; false => 'F'
char bool_2_char(bool b) {
	return b ? 'T' : 'F';
}

int evaluate(string infix, string& postfix, bool& result) {
	//Infix --> postfix conversion
	if (!validateInfix(infix)) {
		return 1;
	}

	// Initialize postfix to empty
	postfix = "";
	// Initialize operator stack to empty
	stack<char> operatorStack;
	//For each character ch in the infix string 
	for (int i = 0; i < infix.length(); i++) {
		char ch = infix[i];

		switch (ch) {
		// operand
		case 'T':
		case 'F':
			postfix += ch;
			// Process all '|'s immediately in front of expression
			while (!operatorStack.empty() && operatorStack.top() == '!') {
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			break;

		// operator
		case '&':
		case '^':
			while (!operatorStack.empty() && operatorStack.top() != '(' && compare(ch, operatorStack.top()) <= 0) {
				postfix += operatorStack.top();
				operatorStack.pop();
			}
			operatorStack.push(ch);
			break;

		case '!':
		case '(':
			operatorStack.push(ch);
			break;

		case ')':
			while (!operatorStack.empty() && operatorStack.top() != '(') {
				postfix += operatorStack.top();
				operatorStack.pop();
			}

			if (operatorStack.empty()) { // not found corresponding '('
				return 1;
			}
			operatorStack.pop();

			// Process all '|'s immediately in front of '('
			while (!operatorStack.empty() && operatorStack.top() == '!') {
				postfix += operatorStack.top();
				operatorStack.pop();
			}

			break;

		// ignore white space
		case ' ':
			break;

		// invalid ch
		default:
			return 1;
		}
	}
	// While the stack is not empty 
	while (!operatorStack.empty()) {
		// '(' left in postfix means no matching ')' e.g.: "((T)"
		if (operatorStack.top() == '(') {
			return 1;
		}

		postfix += operatorStack.top();
		operatorStack.pop();
	}
	// operatorStack.pop(); <-- cannot pop coz it's empty when previous while loop breaks

	// Evaluate postfix 
	
	// Initialize operand stack to be empty
	stack<char> operandStack;
	// For each character ch in the postfix string 
	for (int i = 0; i < postfix.length(); i++) {
		char ch = postfix[i];

		if (ch == 'T' || ch == 'F') {
			operandStack.push(ch);
		}
		else if (ch == '!') { // unary operator
			if (operandStack.size() < 1) { // expecting at least 1 operands
				return 1;
			}

			char operand1 = operandStack.top();
			operandStack.pop();
			operand1 = operand1 == 'T' ? 'F' : 'T';
			operandStack.push(operand1);
		}
		else { // binary operator
			if (operandStack.size() < 2) { // expecting at least 2 operands
				return 1;
			}

			bool operand2 = char_2_bool(operandStack.top());
			operandStack.pop();
			bool operand1 = char_2_bool(operandStack.top());
			operandStack.pop();
			// Apply the operation that ch represents to operand1 and operand2
			// Rush the result onto the stack
			bool val = true;
			switch (ch) {
			case '&':
				val = operand1 && operand2;
				break;
			case '|':
				val = operand1 || operand2;
				break;
			case '^':
				val = operand1 ^ operand2;
				break;
			}
			operandStack.push(bool_2_char(val));
		}
	}
	

	// When the loop is finished, the operand stack will contain one item,
	// the result of evaluating the expression

	// If there're more than 1 char left in stack, it is invalid!
	if (operandStack.size() != 1) {
		return 1;
	}

	result = char_2_bool(operandStack.top());

	return 0;
}