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

	bool isOperatorValid(char ch);
	double calc(double n1, double n2, char oper);

public:
	//初始化
	Expression(string rawInput);
	//将中缀表达式转换为前缀表达式
	string parse2polish();
	//计算中缀表达式的结果
	double calculate();
	//用于去除原始表达式中的空格
	inline void strip();
	//输出原始表达式
	inline void output()
	{
		cout << rawExprs << endl;
	}
	friend inline string DoubleToString(double Input);
	friend inline string Vector2String(vector <string> vec);
	friend void strcut(string& str, char ch);
	friend inline void strrpl(string& str, char16_t src_ch, char des_ch);
};

