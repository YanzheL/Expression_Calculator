#pragma once
#include "stdafx.h"
using namespace std;


class Expression
{
protected:
	string rawExprs;
	vector <string> operatorStack;
	vector <string> polishNotation_Vec;
	string VaildOperators = "+-*/%()";
public:
	//初始化
	Expression(string rawInput);
	//将中缀表达式转换为前缀表达式
	string parse2polish();
	static double calc(double n1, double n2, char oper);
	//计算中缀表达式的结果
	double calculate();
	//用于去除原始表达式中的空格
	void strip();

	void output()
	{
		cout << rawExprs<<endl;
	}

	bool isOperatorValid(char ch)
	{
		bool vaildFlag = false;
		for (size_t j = 0; j < VaildOperators.size(); ++j)
		{
			if (VaildOperators[j]==ch)
			{
				vaildFlag = true;
				break;
			}
		}
		return vaildFlag;
	}

	static string DoubleToString(double Input)
	{
		stringstream Oss;
		Oss << Input;
		return Oss.str();
	}

};



double Expression::calc(double n1, double n2, char oper)
{
	if (oper == '%')
	{
		if (n1 != (int)n1 || n2 != (int)n2)
		{
			cout << "Operator '%' can only apply to integers" << endl;
			exit(1);
		}
	}
	switch (oper)
	{
	case '+':return n1 + n2;
	case '-':return n1 - n2;
	case '*':return n1 * n2;
	case '/':return n1 / n2;
	case '%':return (int)n1 % (int)n2;
	default:
		return NULL;
	}
}