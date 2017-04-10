#pragma once
#include "stdafx.h"
#include "head.h"

bool Expression::isOperatorValid(char ch)
{
	bool vaildFlag = false;
	for (size_t j = 0; j < VaildOperators.size(); ++j)
	{
		if (VaildOperators[j] == ch)
		{
			vaildFlag = true;
			break;
		}
	}
	return vaildFlag;
}

void strcut(string& str, char ch)
{
	for (size_t i = 0; i < str.size(); )
	{
		size_t chPos = 0;
		chPos = str.find(' ', i);
		if (chPos != string::npos)
		{
			str.erase(chPos, 1);
			i = chPos + 1;
		}
		else break;
	}
}

inline void strrpl(string& str, char16_t src_ch, char des_ch)
{
	for (size_t i = 0; i < str.size(); ++i)
		if (str[i] == src_ch) str[i] = des_ch;
}

Expression::Expression(string rawInput)
{
	rawExprs = rawInput;
	strip();
}

string Expression::parse2polish()
{
	typedef vector <int> BiArray;

	vector <BiArray> rightBracketPos;
	for (int i = rawExprs.size() - 1; i >= 0; --i)
	{
		if (isdigit(rawExprs[i]) == false)	//如果是运算符，则压入运算符栈
		{
			string tempString;
			if (rawExprs[i] == ')')
			{
				int operIndex = operatorStack.size() - 1;
				if (operIndex < 0)
					operIndex = 0;

				BiArray temp;
				temp.push_back(operIndex);
				temp.push_back(i);
				rightBracketPos.push_back(temp);
			}
			else if (isOperatorValid(rawExprs[i]) == false)
			{
				cout << "Invaild Operator \"" << rawExprs[i] << "\"" << endl;
				exit(1);
			}
			else if (rawExprs[i] == '(')
			{
				if (rightBracketPos.size() > 0)
				{
					for (int k = operatorStack.size() - 1; k > rightBracketPos.back()[0]; --k)
					{
						polishNotation_Vec.push_back(operatorStack.at(k));
					}

					int delLength = operatorStack.end() - (operatorStack.begin() + rightBracketPos.back()[0]);
					operatorStack.erase(operatorStack.begin() + rightBracketPos.back()[0], operatorStack.end());

					for (size_t m = 0; m < rightBracketPos.size(); ++m)
					{
						rightBracketPos[m][1] -= delLength;
					}

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
				tempString.push_back(rawExprs[i]);
				operatorStack.push_back(tempString);
			}
		}
		else						//如果是数字，则直接压入前缀表达式栈
		{
			string tempDigit = "";
			int tempi = i;
			while (tempi >= 0 && isdigit(rawExprs[tempi]))
			{
				tempDigit.insert(tempDigit.begin(), rawExprs[tempi]);
				--tempi;
			}
			polishNotation_Vec.push_back(tempDigit);
		}
	}

	while (operatorStack.size() > 0)
	{
		polishNotation_Vec.push_back(operatorStack.back());
		operatorStack.pop_back();
	}

	vector <string> tempPolish(polishNotation_Vec.rbegin(), polishNotation_Vec.rend());

	polishNotation_Vec = tempPolish;

	return Vector2String(polishNotation_Vec);
}

double Expression::calculate()
{
	double result = 0;
	vector <string> poliNt_copy(polishNotation_Vec.begin(), polishNotation_Vec.end());
	for (int i = poliNt_copy.size() - 1; i >= 0; )
	{
		if (poliNt_copy.size() >= 3 && isdigit(poliNt_copy.at(i)[0]) == false)
		{
			result =
				calc(
					atof(poliNt_copy.at(i + 1).c_str()),
					atof(poliNt_copy.at(i + 2).c_str()),
					poliNt_copy.at(i).c_str()[0]
				);
			poliNt_copy[i + 2] = DoubleToString(result);
			poliNt_copy.erase(poliNt_copy.begin() + i);
			poliNt_copy.erase(poliNt_copy.begin() + i + 1);
			i = poliNt_copy.size() - 1;
		}
		else --i;
	}
	return result;

}

inline void Expression::strip()
{
	strcut(rawExprs, ' ');
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
	default:
		return NULL;
	}
}

inline string DoubleToString(double Input)
{
	stringstream Oss;
	Oss << Input;
	return Oss.str();
}

inline string Vector2String(vector <string> vec)
{
	string result_str = "";
	for (size_t i = 0; i < vec.size(); ++i)
		result_str += (vec.at(i) + ",");
	result_str.pop_back();
	return result_str;
}