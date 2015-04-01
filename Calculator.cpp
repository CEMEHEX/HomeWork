#include "stdafx.h"
#include <iostream>
#include <stack>
#include <string>
using namespace std;
int prio(char c) {
	if ((c == '*') || (c == '/') || (c == '%')) return 3;
	if ((c == '+') || (c == '-')) return 2;
	else return 1;
}
int _tmain(int argc, _TCHAR* argv[])
{
	string s;
	string output;
	cin >> s;
	stack <char> stack1;
	stack <int> stack2;
	for (int i = 0; i < s.length();++i)
	{
		if ((s[i] >= '0') && (s[i] <= '9'))
		{
			output += s[i];
			if ((i == s.length() - 1) || ((s[i + 1] < '0') || (s[i + 1] > '9'))) output += ' ';
			continue;
		}
		if (s[i] == '(')
		{
			stack1.push(s[i]);
			continue;
		}
		if (s[i] == ')')
		{
			while (stack1.top() != '(') 
			{
				output += stack1.top();
				stack1.pop();
			}
			stack1.pop();
			continue;
		}
		if ((stack1.empty()) || (prio(stack1.top()) < prio(s[i]))) stack1.push(s[i]);
		else {
		while ((!stack1.empty()) &&(prio(stack1.top()) >= prio(s[i])))
		{
			output += stack1.top();
			stack1.pop();
		}
		}
		if ((stack1.empty()) || (prio(stack1.top()) < prio(s[i]))) stack1.push(s[i]);
	}
	while(!stack1.empty())
	{
		output += stack1.top();
		stack1.pop();
	}
	cout<<output<<endl;
	string num;
	for (int i = 0; i < output.length(); ++i){
		if ((int)output[i] == 32){
			stack2.push(atoi(num.c_str()));
			num = "";
			continue;
		}
		if ((output[i] >= '0') && (output[i] <= '9')) num += output[i];
		else {
			int b = stack2.top();
			stack2.pop();
			int a = stack2.top();
			stack2.pop();
			switch (output[i])
			{
			    case '+':stack2.push(a + b);break;
			    case '-':stack2.push(a - b);break;
			    case '*':stack2.push(a * b);break;
			    case '/':stack2.push(a / b);break;
				case '%':stack2.push(a % b);break;
			}
		}
	}
	cout<<stack2.top();
	return 0;
}
