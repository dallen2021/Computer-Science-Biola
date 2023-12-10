#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"
using namespace std;

LexicalAnalyzer lexEval;

int expEvaluator::infixToPostfix(string Input) { // translates the infix operation to postfix and then calls the postfix evaluation function and returns the value
	lexEval.clear();
	lexEval.startAnalysis(Input, 0);
	vector<pair<string, LexicalAnalyzer::categoryType>> inTokens = lexEval.sendTokens(0);

	stack<pair<string, LexicalAnalyzer::categoryType>> tstack;
	vector<pair<string, LexicalAnalyzer::categoryType>> out;

	for (int i = 0; i < inTokens.size(); i++) {
		if (inTokens[i].second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL) {
			out.push_back(inTokens[i]);
		}
		else if (inTokens[i].second == LexicalAnalyzer::categoryType::IDENTIFIER) {
			out.push_back(inTokens[i]);
		}
		else if (inTokens[i].second == LexicalAnalyzer::categoryType::LEFT_PAREN) {
			tstack.push(inTokens[i]);
			continue;
		}
		else if (inTokens[i].second == LexicalAnalyzer::categoryType::RIGHT_PAREN) {
			if (tstack.empty()) {
				cout << "Error. Input not a valid expression." << endl;
				exit(1);
			}
			while (true) {
				if (tstack.top().second == LexicalAnalyzer::categoryType::LEFT_PAREN) {
					tstack.pop();
					break;
				}
				out.push_back(tstack.top());
				tstack.pop();
			}
		}
		else if (inTokens[i].second == LexicalAnalyzer::categoryType::ARITH_OP ||
			inTokens[i].second == LexicalAnalyzer::categoryType::RELATIONAL_OP ||
			inTokens[i].second == LexicalAnalyzer::categoryType::LOGICAL_OP) {

			while (!tstack.empty() && tstack.top().second != LexicalAnalyzer::categoryType::LEFT_PAREN &&
				is_higher_precedence(tstack.top(), inTokens[i])) {
				out.push_back(tstack.top());
				tstack.pop();
			}
			tstack.push(inTokens[i]);
		}
		else
			continue;
	}
	while (!tstack.empty()) {
		out.push_back(tstack.top());
		tstack.pop();
	}
	return postfixEval(out);
	lexEval.clear();
}

int expEvaluator::postfixEval(vector<pair<string, LexicalAnalyzer::categoryType>> tokens) { // evaluates the postfix operation
	stack<int> stackEval;
	int result, var1, var2;
	for (int i = 0; i < tokens.size(); i++) {
		if (tokens[i].second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL)
			stackEval.push(stod(tokens[i].first));
		else if (tokens[i].second == LexicalAnalyzer::categoryType::IDENTIFIER)
			stackEval.push(getValue(tokens[i].first));
		else if (tokens[i].first == "not") { // unary operator
			if (stackEval.empty()) {
				cout << "Error not a valid expression." << endl;
				exit(1);
			}
			var1 = stackEval.top();

			if (var1 == 1)
				stackEval.push(0);
			else if (var1 == 0)
				stackEval.push(1);
			else {
				cout << "Error not a valid expression." << endl;
				exit(1);
			}
		}
		else {
			if (stackEval.empty()) {
				cout << "Error not a valid expression." << endl;
				exit(1);
			}
			var2 = stackEval.top();
			stackEval.pop();

			if (stackEval.empty()) {
				cout << "Error not a valid expression." << endl;
				exit(1);
			}
			var1 = stackEval.top();
			stackEval.pop();

			stackEval.push(variableEval(var1, var2, tokens[i].first));
		}
	}
	if (stackEval.empty()) {
		cout << "Error" << endl;
		exit(1);
	}
	return stackEval.top();
}

int expEvaluator::variableEval(int x, int y, string op) { // evaluates the variables in the equations
	if (op == "*")
		return x * y;
	else if (op == "/")
		return x / y;
	else if (op == "%")
		return x % y;
	else if (op == "+")
		return x + y;
	else if (op == "-")
		return x - y;
	else if (op == "<") {
		if (x < y)
			return 1;
		else
			return 0;
	}
	else if (op == "<=") {
		if (x <= y)
			return 1;
		else
			return 0;
	}
	else if (op == ">") {
		if (x > y)
			return 1;
		else
			return 0;
	}
	else if (op == ">=") {
		if (x >= y)
			return 1;
		else
			return 0;
	}
	else if (op == "!=") {
		if (x != y)
			return 1;
		else
			return 0;
	}
	else if (op == "==") {
		if (x == y)
			return 1;
		else
			return 0;
	}
	else if (op == "and") {
		if (x == 1 && y == 1)
			return 1;
		else
			return 0;
	}
	else if (op == "or") {
		if (x == 1 || y == 1)
			return 1;
		else
			return 0;
	}
}

int expEvaluator::precedence(pair<string, LexicalAnalyzer::categoryType> token) { // checks for precedence
	if (token.first == "%" || token.first == "*" || token.first == "/")
		return 5;
	else if (token.first == "+" || token.first == "-")
		return 4;
	else if (token.second == LexicalAnalyzer::categoryType::RELATIONAL_OP)
		return 3;
	else if (token.first == "not")
		return 2;
	else if (token.first == "and")
		return 2;
	else if (token.first == "or")
		return 1;

}

bool expEvaluator::is_higher_precedence(pair<string, LexicalAnalyzer::categoryType> scanned, pair<string, LexicalAnalyzer::categoryType> stackTop) { 
	if (precedence(scanned) >= precedence(stackTop)) // if higher than or equal to precedence it will return true 
		return true;
	else
		return false;
}

int expEvaluator::getValue(string key) {
	if (symbolTable.count(key)) {
		return stod(symbolTable[key]); // returns the double value of the value for the variable in the symbolTable
	}
	else {
		cout << "Value not found" << endl;
		exit(1);
	}
}

void expEvaluator::addValue(string key, string value) { // adds value to the symbolTable
	symbolTable[key] = value;
	return;
}

void expEvaluator::clear() { // clears symbolTable
	symbolTable.clear();
}

void expEvaluator::showVariables() { // iterates through the symbolTable and outputs each identifier with its respective assigned value
	map<string, string>::iterator it = symbolTable.begin();
	cout << "****************VARIABLE TABLE****************" << endl;
	int count = 0;
	cout << "\t\tKEY\tVALUE" << endl;
	while (it != symbolTable.end()) {
		cout << "Variable [" << count << "]" << "\t" << it->first << "\t" << it->second << endl;
		it++;
		count++;
	}
}