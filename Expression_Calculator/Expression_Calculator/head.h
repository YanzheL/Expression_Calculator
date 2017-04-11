#pragma once
#include "stdafx.h"
using namespace std;

class Expression
{
protected:
	//存储去掉空格之后的原始(中缀)表达式
	string InitExpression;
	//运算符栈
	vector <string> OP_Stack;
	//存储最终的前缀表达式
	vector <string> polishNotation_Vec;
	string polishNotation_Str;
	//已知的运算符列表
	string ValidOperators = "+-*/%^()";
	//检查运算符是否在已知列表中
	bool isOperatorValid(char ch);
	//返回运算符的优先级
	//+ - 为 0	* / % 为 1	^ 为 2
	int findOperatorPower(char ch);
	//根据给定的运算符计算结果
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
	inline void output_raw()
	{
		cout << "\t"<<InitExpression << endl << endl;
	}
	inline void output_poliNotation()
	{
		if (polishNotation_Vec.size() == 0)
			parse2polish();
		cout << "\t"<<polishNotation_Str << endl << endl;
	}
	friend inline string Double2Str(double Input);
	friend inline string Vec2Str(vector <string> vec);
	friend void strcut(string& str, char ch);
	friend inline void strrpl(string& str, char16_t src_ch, char des_ch);
};







//--------------------------------------------------------- Tools ---------------------------------------------------------
void Show_Index_Page();
inline string Double2Str(double Input)
{
	stringstream Oss;
	Oss << Input;
	return Oss.str();
}
inline string Vec2Str(vector <string> vec)
{
	string result_str = "";
	for (size_t i = 0; i < vec.size(); ++i)
		result_str += (vec.at(i) + ",");
	result_str.pop_back();
	return result_str;
}
void strcut(string& str, char ch);
inline void strrpl(string& str, char16_t src_ch, char des_ch);

