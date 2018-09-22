#include "pch.h"
#include <iostream>
#include <stack>
#include <cmath> //unsure if needed
#include <string>

using namespace std;

int precedence(char operation) {
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
	case '||': return 6;
	}
	return 0;
}

int detectOperator(int operation1, int operation2, char operation) {
	switch (operation) {
	case '+': return operation1 + operation2;
		break;
	case '-': return operation1 - operation2;
		break;
	case '/': return operation1 / operation2;
		break;
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
	case '>': return operation1 > operation2;
		break;
	case '>=': return operation1 >= operation2;
		break;
	case '<=': return operation1 <= operation2;
		break;
	case '&&': return operation1 && operation2;
		break;
	case '||': return operation1 || operation2;
		break;
	}
	return 0;
}

int evaluate(string location) {
	int i;
	stack <int> number;
	stack <char> symbol;

	for (i = 0; i < location.length(); i++) {

		if (location[i] == ' ')
			continue;

		else if (location[i] == '(') {
			symbol.push(location[i]);
		}
		else if (isdigit(location[i])) {
			int answer = 0;

			while (i < location.length() &&
				isdigit(location[i]))
			{
				answer = (answer * 10) + (location[i] - '0');
				i++;
			}

			number.push(answer);
		}
		else if (location[i] == ')')
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

int equations() {
	cout << " Evaluating 1 + 2 * 3 = " << evaluate("1 + 2 * 3") << "\n";
	cout << " Evaluating 2 + 2^2 * 3 = " << evaluate("2 + 2^2 * 3") << "\n";
	cout << " Evaluating 100 * (8 / 10) = " << evaluate("100 * ( 8 /10 )") << "\n";
	cout << " Evaluating 1==2 = " << evaluate("1==2") << "\n";
	cout << " Evaluating 10 + 2 * 6 = " << evaluate("10 + 2 * 6") << "\n";
	cout << " Evaluating 100 * ( 2 + 12 ) / 14 = " << evaluate("100 * ( 2 + 12 ) / 14") << "\n";
	cout << " Evaluating 1 + 3 > 2 = " << evaluate("1 + 3 > 2") << "\n";
	cout << " Evaluating 100 * 2 + 12 = " << evaluate("100 * 2 + 12") << "\n";
	cout << "\n" << "Now lets check for some invalid expressions. Press enter to continue";
	cin.ignore();
	return 0;
}

int main()
{
	equations();
}