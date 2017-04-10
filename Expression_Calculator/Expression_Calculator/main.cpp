// Expression_Calculator.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "head.h"

int main()
{
	string rawInput;
	cout << "Please inupt the expression:" << endl;

	while (true)
	{
		getline(cin, rawInput);
		if (rawInput.size() == 0)
		{
			cout << "Do not input empty expression, please input again:" << endl;
		}
		else break;
	}

	Expression expr1(rawInput);

	cout << "Stripped raw expression is:" << endl;
	expr1.output();

	cout << "Parsed Polish Notation is:" << endl;
	cout << expr1.parse2polish() << endl;
	cout << "Calculation result is:" << endl;
	cout << expr1.calculate() << endl;

	cout << endl;
	return 0;
}
