
#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
int main()
{
    string postfix;		// Have to declare first bc it's passed by reference
    bool result;
    evaluate("T&F", postfix, result);

    /*string pf;
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
    */
}

int evaluate(string infix, string& postfix, bool& result) {
    // Infix ? postfix conversion 
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
            int count = 0;
            int j = i + 1;
            for (; j < infix.length(); j++) {
                if (infix[j] == '(') count++;
                else if (infix[j] == ')') {
                    count--;

                    if (count == 0) {
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
                    }
                }
            }
            break;

        default:
            return 1;
        }

        std::cerr << "done";
        return 0;
    }
}





