// Expression_Calculator.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "head.h"
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

void strrpl(string& str, char16_t src_ch, char des_ch)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == src_ch)
		{
			str[i] = des_ch;
		}
	}
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
				{
					operIndex = 0;
				}

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

	string polishNotation_Str = "";

	for (size_t i = 0; i < polishNotation_Vec.size(); ++i)
	{
		polishNotation_Str += (polishNotation_Vec.at(i) + ",");
	}
	polishNotation_Str.pop_back();

	return polishNotation_Str;
}

double Expression::calculate()
{
	double result = 0;
	vector <string> poliNt_copy(polishNotation_Vec.begin(), polishNotation_Vec.end());
	for (size_t i = poliNt_copy.size() - 1; i >= 0; )
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

void Expression::strip()
{
	strcut(rawExprs, ' ');
}









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
		else
		{
			break;
		}
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

