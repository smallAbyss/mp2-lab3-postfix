#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
  string expression;
  double res;

  setlocale(LC_ALL, "Russian");
  cout << "Введите арифметическое выражение: ";
  getline(cin, expression);
  cout << expression << endl;
  TPostfix postfix(expression);

  cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
  try {
	cout << postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	map<char, double> var = postfix.GetOperands();
	for (auto oper : var) {
		cout << "Enter " << oper.first << ", " << oper.first << " = ";
		cin >> var[oper.first];
	}
	res = postfix.Calculate(var);
	cout << res << endl;
  }
  catch (string ex) {
	  cout << ex;
  }
  

  return 0;
}
