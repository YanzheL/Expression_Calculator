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
	//��ʼ��
	Expression(string rawInput);
	//����׺���ʽת��Ϊǰ׺���ʽ
	string parse2polish();
	//������׺���ʽ�Ľ��
	double calculate();
	//����ȥ��ԭʼ���ʽ�еĿո�
	void strip();
	//���ԭʼ���ʽ
	inline void output()
	{
		cout << rawExprs<<endl;
	}

	friend string DoubleToString(double Input);
	friend string Vector2String(vector <string> vec);
	friend void strcut(string& str, char ch);
	friend void strrpl(string& str, char16_t src_ch, char des_ch);
};


