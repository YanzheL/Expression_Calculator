#pragma once
#include "stdafx.h"
#include "head.h"

bool Expression::isOperatorValid(char ch)
{
	bool validFlag = false;
	for (size_t j = 0; j < ValidOperators.size(); ++j)
	{
		if (ValidOperators[j] == ch)
		{
			validFlag = true;
			break;
		}
	}
	return validFlag;
}

int Expression::findOperatorPower(char ch)
{
	size_t pos;
	for (pos = 0; pos < ValidOperators.size(); pos++)
	{
		if (ValidOperators.at(pos) == ch)
		{
			break;
		}
	}

	if (pos < 1)
	{
		return 0;
	}
	else if (pos >= 2 && pos <= 4)
	{
		return 1;
	}
	else if (pos == 5)
	{
		return 2;
	}
	else
	{
		return -1;
	}

}

Expression::Expression(string rawInput)
{
	InitExpression = rawInput;
	strip();
	for (size_t i = 0; i < InitExpression.size(); ++i)
	{
		if (isdigit(InitExpression[i])==false)
		{
			if (isOperatorValid(InitExpression[i]) == false)//检查运算符是否在已知的列表里
			{
				cout << "Invalid Operator \"" << InitExpression[i] << "\"" << endl;
				exit(1);
			}
		}
	}
}

string Expression::parse2polish()
{
	//两个元素的容器，存储一个右括号在operatorStack中的下标和在rawExprs的位置下标
	typedef vector <int> BiArray;
	//存储多个右括号的位置
	vector <BiArray> rightBracketPos;

	for (int ielemt = InitExpression.size() - 1; ielemt >= 0; --ielemt)
	{
		if (isdigit(InitExpression[ielemt]) == false)		//如果是运算符，则准备进入运算符栈
		{
			string prepareString;
			if (InitExpression[ielemt] == ')')
			{
				OP_Stack.push_back(")");
				int operIndex = OP_Stack.size() - 1;	//获取当前operatorStack中最后一个元素的下标
				if (operIndex < 0)operIndex = 0;		//如果当前operatorStack没有元素，则下标设置为0

				BiArray temp;
				temp.push_back(operIndex);
				temp.push_back(ielemt);
				rightBracketPos.push_back(temp);
			}
			else if (isOperatorValid(InitExpression[ielemt]) == false)//检查运算符是否在已知的列表里
			{
				cout << "Invalid Operator \"" << InitExpression[ielemt] << "\"" << endl;
				exit(1);
			}
			else if (InitExpression[ielemt] == '(')
			{
				if (rightBracketPos.size() > 0)
				{
					unsigned int delLength = OP_Stack.size() - 1 - rightBracketPos.back()[0];

					for (int ii = 0; ii < delLength; ++ii)
					{
						polishNotation_Vec.push_back(OP_Stack.back());
						OP_Stack.pop_back();
					}
					OP_Stack.pop_back();
					rightBracketPos.pop_back();
				}
				else
				{
					cout << "Expression syntax error" << endl;
					exit(1);
				}
			}
			else
			{
				//先装入tempString里准备push到OP_Stack
				prepareString.push_back(InitExpression[ielemt]);

				int powerCurrent = findOperatorPower(InitExpression[ielemt]);
				int powerPrev = 0;

				if (OP_Stack.size() > 0)
					powerPrev = findOperatorPower(OP_Stack.back()[0]);

				if (powerCurrent >= powerPrev)
					OP_Stack.push_back(prepareString);
				else if(OP_Stack.size()>=2)
				{
					OP_Stack.push_back(prepareString);
					int size = OP_Stack.size() - 1;
					swap(OP_Stack[size - 1], OP_Stack[size]);
					polishNotation_Vec.push_back(OP_Stack.back());
					OP_Stack.pop_back();
				}
			}
		}
		else						//如果是数字，则直接压入前缀表达式结果容器
		{
			string tempDigit = "";
			int tempi = ielemt;
			int digitCount = 0;
			while (tempi >= 0 && isdigit(InitExpression[tempi]))
			{
				tempDigit.insert(tempDigit.begin(), InitExpression[tempi]);
				--tempi;
				++digitCount;
			}
			ielemt = ielemt - digitCount + 1;
			polishNotation_Vec.push_back(tempDigit);
		}
	}

	while (OP_Stack.size() > 0)
	{
		polishNotation_Vec.push_back(OP_Stack.back());
		OP_Stack.pop_back();
	}

	//倒序复制到临时容器，再复制给polishNotation_Vec作为结果
	vector <string> tempPolish(polishNotation_Vec.rbegin(), polishNotation_Vec.rend());
	polishNotation_Vec = tempPolish;
	//将结果转化为string类型
	polishNotation_Str = Vec2Str(polishNotation_Vec);
	return polishNotation_Str;
}

double Expression::calculate()
{
	//如果之前没有进行parse,则调用parse
	if (polishNotation_Vec.size()==0)parse2polish();

	double result = 0;
	vector <string> poliNt_copy(polishNotation_Vec.begin(), polishNotation_Vec.end());
	for (int i = poliNt_copy.size() - 1; i >= 0; )
	{
		//用于Debug
		//cout << "----------" << i << "----------" << endl;
		//int x = 0;
		//while (x != poliNt_copy.size())
		//{
		//	cout << poliNt_copy.at(x) << ",";
		//	++x;
		//}
		//cout << endl;

		if (poliNt_copy.size() >= 3 && isdigit(poliNt_copy.at(i)[0]) == false)
		{
			result =
				calc(
					atof(poliNt_copy.at(i + 1).c_str()),
					atof(poliNt_copy.at(i + 2).c_str()),
					poliNt_copy.at(i).c_str()[0]
				);
			poliNt_copy[i + 2] = Double2Str(result);
			poliNt_copy.erase(poliNt_copy.begin() + i);
			poliNt_copy.erase(poliNt_copy.begin() + i);
			i = poliNt_copy.size() - 1;
		}
		else --i;
	}



	return result;
}

inline void Expression::strip()
{
	strcut(InitExpression, ' ');
}

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
	case '^':return pow(n1, n2);
	default:return NULL;
	}
}