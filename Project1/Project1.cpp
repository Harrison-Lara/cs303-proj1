/*
	Written by: Harrison R. Lara

	REFERENCES
	-- Professor Kuhail @ UMKC (stack lecture and example)
	-- Harald Scheirich from https://codereview.stackexchange.com/questions/190862/converting-prefix-expressions-to-infix
		-> Used for contextual ideas
*/

#include "pch.h"
#include <iostream>
#include <stack>
#include <cmath>
#include <string>

using namespace std;

int precedence(char operation) { // function for valid operators to check for
	switch (operation) {
	case '+': return 1;
	case '++': return 1;
	case '-': return 1;
	case '--': return 1;
	case '!': return 1;
	case '^': return 2;
	case '%': return 3;
	case '/': return 3;
	case '*': return 3;
	case '>': return 4;
	case '>=': return 4;
	case '<': return 4;
	case '<=': return 4;
	case '&&': return 5;
	case '||': return 6; // Precendence order goes low to high instead of high to low
	}
	return 0;
}

int detectOperator(int operation1, int operation2, char operation) { // function for selecting operaters for stack
	switch (operation) {
	case '+': return operation1 + operation2;
		break;
	case '-': return operation1 - operation2;
		break;
	case '/': if (operation2 == 0 ){
		cout << "\n" << "Cant divide by zero!! Exiting..." << "\n"; // error handling
		exit(1);
		}
		else {
			return operation1 / operation2;
			break;
		}
	case '*': return operation1 * operation2;
		break;
	case '--': return operation1 - 1;
		break;
	case '++': return operation1 + 1;
		break;
	case '!': return operation1 = 0;
		break;
	case '^': return operation1 ^ operation2;
		break;
	case '%': return operation1 % operation2;
		break;
	case '<': return operation1 < operation2;
		break;
	case '==': return operation1 == operation2;
		break;
	case '>': return operation2 > operation1;
		break;
	case '>=': return operation1 >= operation2;
		break;
	case '<=': return operation1 <= operation2;
		break;
	case '&&': if ("&&&") { 
		cout << "\n" << "Two binary operators in a row!! Exiting..."; // error handling
		exit(1);
		}
		else {
		return operation1 && operation2;
		}
		break;
	case '||': return operation1 || operation2;
		break;
	}
	return 0;
}

int evaluate(string location) { // function evaluates infix expressions
	int i;
	stack <int> number; // number stack
	stack <char> symbol; // operater stack

	for (i = 0; i < location.length(); i++) {

		if (location[i] == ' ') // stack handles space
			continue;

		else if (location[i] == '(') { // stack handling opening (
			symbol.push(location[i]);
		}
		else if (isdigit(location[i])) {
			int answer = 0;

			while (i < location.length() && // allocates stack space when needed
				isdigit(location[i]))
			{
				answer = (answer * 10) + (location[i] - '0');
				i++;
			}
			number.push(answer);
		}
		else if (location[i] == ')') // stack handling closing )
		{
			while (!symbol.empty() && symbol.top() != '(')
			{
				int numeral = number.top();
				number.pop();

				int numerals = number.top();
				number.pop();

				char operators = symbol.top();
				symbol.pop();

				number.push(detectOperator(numeral, numerals, operators));
			}
			symbol.pop();
		}
		else
		{
			while (!symbol.empty() && precedence(symbol.top())
				>= precedence(location[i])) {
				int numerals = number.top();
				number.pop();

				int numeral = number.top();
				number.pop();

				char operators = symbol.top();
				symbol.pop();

				number.push(detectOperator(numeral, numerals, operators));
			}
			symbol.push(location[i]);
		}
	}
	while (!symbol.empty()) {
		int numerals = number.top();
		number.pop();

		int numeral = number.top();
		number.pop();

		char operators = symbol.top();
		symbol.pop();
	
		number.push(detectOperator(numeral, numerals, operators));	
	}
	return number.top();
}

int equations() { // function holds all equations to be evaluated
	cout << " Evaluating 1 + 2 * 3 = " << evaluate("1 + 2 * 3") << "\n"; // functioning expressions
	cout << " Evaluating 2 + 2^2 * 3 = " << evaluate("2 + 2^2 * 3") << "\n";
	cout << " Evaluating (1 + 3) * 2  = " << evaluate("2 + 2^2 * 3") << "\n";
	cout << " Evaluating 100 * (8 / 10 ) = " << evaluate("100 * ( 8 /10 )") << "\n";
	cout << " Evaluating 1==2 = " << evaluate("1==2") << "\n";
	cout << " Evaluating 10 + 2 * 6 = " << evaluate("10 + 2 * 6") << "\n";
	cout << " Evaluating 100 * ( 2 + 12 ) / 14 = " << evaluate("100 * ( 2 + 12 ) / 14") << "\n";
	cout << " Evaluating 1 + 3 > 2 = " << evaluate("1 + 3 > 2") << "\n";
	cout << " Evaluating 100 * 2 + 12 = " << evaluate("100 * 2 + 12") << "\n";

	cout << "\n" << "Now lets check for some invalid expressions    Ex. 1 / 0 " << "\n"; // error expressions

	cout << " Evaluating 1 / 0 = " << evaluate("1 / 0") << "\n";
	cout << " Evaluating <3+2 = " << evaluate("<3+2") << "\n";
	cout << " Evaluating 3&&&& 5 = " << evaluate("3&&&& 5") << "\n";
	cout << " Evaluating 15+ 3 2 = " << evaluate("15+3 2") << "\n";
	cout << " Evaluating 10+ ++<3 = " << evaluate("10+ ++<3") << "\n";
	cout << " Evaluating )3+2 = " << evaluate(")3+2") << "\n";
	return 0;
}

int main()
{
	equations();
}