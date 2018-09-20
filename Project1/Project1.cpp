#include "pch.h"
#include <iostream>
#include <stack>
#include <cmath> //unsure if needed
#include <string>
using namespace std;

int precedence(char operation) {
	switch (operation) {
	case '+': return 1;
	case '-': return 1;
	case '/': return 3;
	case '*': return 3;
	case '^': return 4;
	}
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
	}
}
int main()
{
	return 0;
}