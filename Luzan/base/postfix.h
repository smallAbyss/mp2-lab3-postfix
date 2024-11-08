#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	vector<char> lexems; 
	map<char, int> priority;
	map<char, double> operands;
 
public:
	TPostfix(string inf = "()") : infix(inf), postfix("")
	{ 
		priority = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
		RemoveSpaces();
	}

	string GetInfix() { return infix; }

	string GetPostfix() { return postfix; }

	map<char, double> GetOperands() {
		return operands;
	}

	void RemoveSpaces() {
		string tmp = "";;
		for (char c : infix)
			if (c != ' ')
				tmp += c;
		infix = tmp;
	}

	string ToPostfix() {
		Parse();
		if ( !(Check()) ) throw string("Incorrect");
		TStack<char> st(infix.length());
		char stackItem;
		operands.clear();
		for (char item : lexems) {
			switch (item) {
			case '(':
				st.Push(item);
				break;

			case ')':
				stackItem = st.Pop();
				while (stackItem != '(') {
					postfix += stackItem;
					stackItem = st.Pop();
				}
				break;

			case '+': case '-': case '*': case '/':
				while (!st.IsEmpty()) {
					stackItem = st.Pop();
					if (priority[item] <= priority[stackItem])
						postfix += stackItem;
					else {
						st.Push(stackItem);
						break;
					}
				}
				st.Push(item);
				break;

			default:
				operands.insert({ item, 0.0 });
				postfix += item;
				break;
			} // switch
		} // for
		while (!st.IsEmpty()) {
			stackItem = st.Pop();
			postfix += stackItem;
		}
		return postfix;
	}

	void Parse() { //private
		//lexems.clear();
		for (char c : infix)
			lexems.push_back(c);
	}

	bool LexemIsOperand(const char lex) { //private
		if ((lex <= 'z') && ('a' <= lex)) return true;
		if ((lex <= 'Z') && ('A' <= lex)) return true;
		return false;
	}

	bool Check() {
		for (int i = 0; i < lexems.size()-1; i++) {
			switch (lexems[i]) {
			case '+': case '-': case '*': case '/':
				if (!((lexems[i + 1] == '(') || (LexemIsOperand(lexems[i + 1]))))
					return false;
				break;

			case '(':
				if ( !(LexemIsOperand(lexems[i + 1])) )
					return false;
				break;

			case ')': 
				if (!((lexems[i + 1] == '+') || (lexems[i + 1] == '-') || (lexems[i + 1] == '*') || (lexems[i + 1] == '/') ))
					return false;
				break;
			default:
				if (LexemIsOperand(lexems[i])) {
					if (!((lexems[i + 1] == ')') || (lexems[i + 1] == '+') || (lexems[i + 1] == '-') || (lexems[i + 1] == '*') || (lexems[i + 1] == '/')))
						return false;
				}
				else {
					return false;
				}
				break;
			} // switch end
		} // for end
		if (!( (lexems[lexems.size() - 1] == ')') || (LexemIsOperand(lexems[lexems.size() - 1])) ))
			return false;
		return true;
	} // check end

	double Calculate(const map<char, double>& values) { // Ввод переменных, вычисление по постфиксной форме
		for (auto& val : values) {
			try {
				operands.at(val.first) = val.second;
			}
			catch (out_of_range& e) {}
		}
		TStack<double> st(postfix.length());
		double leftOperand, rightOperand;
		for (char lexem : postfix) {
			switch (lexem) {
			case '+':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand + rightOperand);
				break;
			case '-':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand - rightOperand);
				break;
			case '*':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand * rightOperand);
				break;
			case '/':
				rightOperand = st.Pop();
				leftOperand = st.Pop();
				st.Push(leftOperand / rightOperand);
				break;
			default:
				st.Push(operands[lexem]);
				break;
			}
		}
		return st.Pop();
	}
};

#endif
