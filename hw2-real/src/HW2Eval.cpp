// HW2Eval.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
// Convert char to bool: 'T' => true; 'F' => false
bool char_2_bool(char ch) {
    assert(ch == 'T' || ch == 'F');
    return ch == 'T' ? true : false;
}

// Convert bool to char: true => 'T'; false => 'F'
char bool_2_char(bool b) {
    return b ? 'T' : 'F';
}

int main()
{
    string pf = "";
    bool answer = false;
    //assert(evaluate("T^ F", pf, answer) == 0 && pf == "TF^" && answer);
    //assert(evaluate("T^", pf, answer) == 1);
    //assert(evaluate("F F", pf, answer) == 1);
    //assert(evaluate("TF", pf, answer) == 1);
    //assert(evaluate("()", pf, answer) == 1);
    //assert(evaluate("()T", pf, answer) == 1);
    //assert(evaluate("T(F^T)", pf, answer) == 1);
    //assert(evaluate("T(&T)", pf, answer) == 1);
    //assert(evaluate("(T&(F^F)", pf, answer) == 1);
    //assert(evaluate("T|F", pf, answer) == 1);
    //assert(evaluate("", pf, answer) == 1);
    //assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
    //    && pf == "FF!TF&&^" && !answer);
    //assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    //assert(evaluate("!(!!!(!T))", pf, answer) == 0 && pf == "T!!!!!" && !answer);
    //assert(evaluate("(!!!(!T))", pf, answer) == 0 && pf == "T!!!!" && answer);
    //assert(evaluate("(!(!T)", pf, answer) == 1);
    //assert(evaluate("T&!(F^T&T^F)^!!!(F&T&F)", pf, answer) == 0 && answer);

    int res = evaluate("T^(T)", pf, answer);
    cout << (res?"WRONG" : "OK") << endl << pf << endl << answer << endl;

    cout << "Passed all tests" << endl;
}

int evaluate(string infix, string& postfix, bool& result) {
    postfix = "";
    // Infix -> postfix conversion 
    // Base case T^F&(T^F)&T
    stack<char> operatorStack;
    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];
        if (ch == ' ') {
            continue;
        }
        switch (ch) {
        case 'T':
        case 'F':
            postfix += ch;
            while (!operatorStack.empty() && operatorStack.top() == '!') {
                postfix += operatorStack.top();
                operatorStack.pop(); // !!!T
            }
            break;
        case '!':
            operatorStack.push(ch);
            break;
        case '&':
            while (!operatorStack.empty() && operatorStack.top() == '&') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
            break;

        case '^':
            while (!operatorStack.empty()) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
            break;
        case '(':
        {
            int count = 0;
            int j = i + 1;
            for (; j < infix.length(); j++) {
                if (infix[j] == '(') count++;
                else if (infix[j] == ')') {
                    if (count-- == 0) {
                        string subinfix = infix.substr(i + 1, j - i - 1);
                        string subpostfix;
                        bool subResult;
                        if (evaluate(subinfix, subpostfix, subResult) == 1) {
                            return 1;
                        }
                        postfix += subpostfix;
                        while (!operatorStack.empty() && operatorStack.top() == '!') {
                            postfix += operatorStack.top();
                            operatorStack.pop(); // !!!T
                        }
                        i = j;
                        break;
                    }
                }
            }
            if (j == infix.length()) {        // Still haven't found ')'
                return 1;
            }
        }
        break;

        default:
            return 1;
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    stack<char> operandStack;
    // For each character ch in the postfix string 
    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];
        if (ch == 'T' || ch == 'F') {
            operandStack.push(ch);
        }
        else if (ch == '!') { // unary operator
            if (operandStack.size() < 1) { // expecting at least 1 operand
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
            // Push the result onto the stack
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

    std::cerr << "done" << endl;
    return 0;
}
