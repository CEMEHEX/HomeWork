#include <iostream>
#include <stack>
#include <string>
using namespace std;
bool isOperation(char c) {
	return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '%');
}

bool isValid(char c) {
	return ((c >= '0') && (c <= '9')) || (c == '(') || (c == ')') || isOperation(c);
}

int prio(char c) {
	if ((c == '*') || (c == '/') || (c == '%')) return 3;
	if ((c == '+') || (c == '-')) return 2;
	else return 1;
}

void error(string s) {
	cout << "Error:" + s;
	exit(0);
}

int main(int argc, char* argv[])
{
	string expression;
	string output;
	getline(cin, expression);
	stack <char> stack1;
	stack <int> stack2;
	string s;
	bool isEmpty = true;
	for (int i = 0; i < expression.length(); ++i) {
		if (isOperation(expression[i]) || ((expression[i] >= '0') && (expression[i] <= '9'))) {
			isEmpty = false;
		}
		if (expression[i] != ' ') {
			s += expression[i];
		}
	}
	if (isEmpty) {
		error("Empty expression");
	}
	int balance = 0;
	for (int i = 0; i < s.length(); ++i)
	{
		if (s[i] == '(') {
			balance++;
		}
		if (s[i] == ')') {
			balance--;
		}
		if (balance < 0) {
			error("No opening parenthesis");
		}
		if ((isOperation(s[i])) && (((i < s.length() - 1) && (isOperation(s[i + 1]))) || (i == s.length() - 1) || (i == 0))) {
			error("No argument");
		}
		if (!isValid(s[i])) {
			error("Invalid symbol in expression");
		}

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
			while ((!stack1.empty()) && (prio(stack1.top()) >= prio(s[i])))
			{
				output += stack1.top();
				stack1.pop();
			}
		}
		if ((stack1.empty()) || (prio(stack1.top()) < prio(s[i]))) stack1.push(s[i]);
	}
	if (balance < 0) {
		error("No opening parenthesis");
	}
	if (balance > 0) {
		error("No closing parenthesis");
	}
	while (!stack1.empty())
	{
		output += stack1.top();
		stack1.pop();
	}
	cout << output << endl;
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
			case '+':stack2.push(a + b); break;
			case '-':stack2.push(a - b); break;
			case '*':stack2.push(a * b); break;
			case '/': if (b == 0) error("Division by zero");
				stack2.push(a / b); break;
			case '%': if (b == 0) error("Division by zero"); stack2.push(a % b); break;
			}
		}
	}
	cout << stack2.top();
	return 0;
}

