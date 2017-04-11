// Expression_Calculator.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "head.h"

int main()
{
	system("cls");
	Show_Index_Page();
	cout << endl << "Please inupt the expression:" << endl << endl;
	string rawInput;
	//while (true)
	//{
	//	getline(cin, rawInput);
	//	if (rawInput.size() == 0)
	//	{
	//		cout << "Do not input empty expression, please input again:" << endl;
	//	}
	//	else break;
	//}
	//rawInput = "10 % 7 + 25 + ( 2 ^ (3 + 2) * 20 )";
	rawInput = "1+4-3-(4^(1+3)*8-6)+5";

	Expression expr1(rawInput);

	cout << "\n--------------------------------- Confirm Input --------------------------------\n\n";
	expr1.output_raw();

	cout << "\n----------------------------- Parsed Polish Notation ---------------------------\n\n";
	expr1.output_poliNotation();
	cout << "\n------------------------------- Calculation result -----------------------------\n\n";
	cout << "\t" << expr1.calculate() << endl;
	cout << endl;
	system("pause");
	return 0;
}
