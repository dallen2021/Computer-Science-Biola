#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"

using namespace std;

expEvaluator exprEval;

void Interpreter::run(vector<string> programCodeLines) { // runs through each index of the program code line and sends it to the interpreter function
	for (int i = 0; i < programCodeLines.size(); i++) {
		interpretCode(programCodeLines[i]);
	}
	if_loop = false;
	if_executed = false;
	for (int i = 0; i < ifStatement.size(); i++)
	{
		interpretCode(ifStatement[i]);
	}
	ifStatement.clear();
	loop_idx = 0;
	loop_indent = "";
	return;
}

void Interpreter::interpretCode(string programCode) {
	LexicalAnalyzer lexAnalysis;
	lexAnalysis.startAnalysis(programCode, 0); // analyzes the programCode to use later 
	int idx = 0;
	string val;

	if (failedCondition) {
		if (lexAnalysis.tokenInfo[0].empty()) { 
			loop_idx = 0;
			failedCondition = false;
			loop_indent = "";
		}
		else if (lexAnalysis.tokenInfo[0][0].first == "elif") {
			loop_idx = 0;
			failedCondition = false;
			loop_indent = "";
		}
		else if (lexAnalysis.tokenInfo[0][0].first == "else") {
			loop_idx = 0;
			newIndent = true;
			failedCondition = false;
			if_loop = true;
			return;
		}
		else if (loop_idx == 0) {
			loop_indent = lexAnalysis.tokenInfo[0][0].first;
			loop_idx++;
			return;
		}
		else if (loop_indent != lexAnalysis.tokenInfo[0][0].first) {
			loop_idx = 0;
			failedCondition = false;
			loop_indent = "";
		}
		else if (loop_indent == lexAnalysis.tokenInfo[0][0].first) {
			loop_idx++;
			return;
		}
	}

	if (if_executed) {
		if (lexAnalysis.tokenInfo[0].empty());
		else if (newIndent)
		{
			if (lexAnalysis.tokenInfo[0][0].second != LexicalAnalyzer::categoryType::INDENT)
			{
				cout << "... Syntax error no indent before code" << endl;
				return;
			}
			loop_indent = lexAnalysis.tokenInfo[0][0].first;
			newIndent = false;
			return;
		}
		else if (lexAnalysis.tokenInfo[0][0].first == loop_indent)
		{
			return;
		}
		else if (lexAnalysis.tokenInfo[0][idx].first == "elif" || lexAnalysis.tokenInfo[0][idx].first == "else")
		{
			newIndent = true;
			return;
		}
	}

	if (if_loop) { 
		if (lexAnalysis.tokenInfo[0].empty()) {
			if_loop = false;
			if_executed = false;
			for (int i = 0; i < ifStatement.size(); i++) {
				interpretCode(ifStatement[i]);
			}
			ifStatement.clear();
			loop_idx = 0;
			loop_indent = "";
			return;
		}
		if (loop_idx == 0) {
			if (lexAnalysis.tokenInfo[0][0].second != LexicalAnalyzer::categoryType::INDENT) {
				cout << "... Syntax error no indent before code." << endl;
				return;
			}
			loop_indent = lexAnalysis.tokenInfo[0][0].first;
			for (int i = 0; i < lexAnalysis.tokenInfo[0].size(); i++) {
				if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::UNKNOWN || (lexAnalysis.tokenInfo[0].size() == 2 && lexAnalysis.tokenInfo[0][0].first != "else")) { //breaks
					cout << "Error invalid syntax" << endl << endl;
					ifStatement.clear();
					loop_idx = 0;
					if_executed = true;
					if_loop = false;
					loop_indent = "";
					return;
				}
			}
			ifStatement.push_back(programCode); //pushes back if statement to vector and adds to the loop index
			loop_idx++;
			return;
		}
		else if (lexAnalysis.tokenInfo[0][0].first == "elif" || lexAnalysis.tokenInfo[0][0].first == "else") {
			if_executed = true;
			newIndent = true;
			return;
		}
		else {
			ifStatement.push_back(programCode);
			loop_idx++;
			return;

			if (lexAnalysis.tokenInfo[0].empty() || lexAnalysis.tokenInfo[0][0].first != loop_indent) {
				cout << "test";
			}
			else {
				cout << "test";
			}
		}
	}

	if (while_loop) {
		if (loop_idx == 0) {
			if (lexAnalysis.tokenInfo[0][0].second != LexicalAnalyzer::categoryType::INDENT) {
				cout << "Syntax error, no indent before code." << endl;
				return;
			}
			loop_indent = lexAnalysis.tokenInfo[0][0].first;
			for (int i = 0; i < lexAnalysis.tokenInfo[0].size(); i++) {
				if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::UNKNOWN || lexAnalysis.tokenInfo[0].size() == 2) {
					cout << "Error, invalid syntax" << endl << endl;
					whileLoop.clear();
					while_loop = false;
					loop_idx = 0;
					whileCondition = "";
					return;
				}
			}
			whileLoop.push_back(programCode);
			loop_idx++;
			return;
		}
		else {
			if (lexAnalysis.tokenInfo[0].empty() || lexAnalysis.tokenInfo[0][0].first != loop_indent) {
				while_loop = false;
				while (exprEval.infixToPostfix(whileCondition)) {
					for (int i = 0; i < whileLoop.size(); i++) {
						interpretCode(whileLoop[i]);
					}
				}
				whileLoop.clear();
				loop_idx = 0;
				whileCondition = "";
				loop_indent = "";
				return;
			}
			else if (lexAnalysis.tokenInfo[0][0].first == loop_indent) {
				whileLoop.push_back(programCode);
				loop_idx++;
				return;
			}
		}
	}

	if (lexAnalysis.tokenInfo.empty() || lexAnalysis.tokenInfo[0].empty())
		return;
	else if (lexAnalysis.tokenInfo[0][0].second == LexicalAnalyzer::categoryType::INDENT) // if the token is an indent then add to the index
		idx++;

	if (lexAnalysis.tokenInfo[0][idx].second == LexicalAnalyzer::categoryType::COMMENT) { // if the token is a comment, then ignore
		return;
	}
	else if (lexAnalysis.tokenInfo[0].size() < 2) {
		cout << "Syntax error, please revise" << endl << endl;
		return;
	}
	else if (lexAnalysis.tokenInfo[0][idx + 1].second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP) { // check for assignment operator
		if (lexAnalysis.tokenInfo[0].size() == 3 + idx)
			val = to_string(exprEval.infixToPostfix(lexAnalysis.tokenInfo[0][idx + 2].first));
		else if (lexAnalysis.tokenInfo[0][idx + 2].first == "int" && lexAnalysis.tokenInfo[0][idx + 4].first == "input") {
			if (lexAnalysis.tokenInfo[0].size() < 9) { // check for invalid code and output an error
				cout << "Error, invalid code." << endl; 
				exit(1);
			}
			for (int j = 1; j < lexAnalysis.tokenInfo[0][idx + 6].first.length() - 1; j++)
				cout << lexAnalysis.tokenInfo[0][idx + 6].first[j];
			cout << " ";
			getline(cin, val);
		}
		else {
			string exprIn = programCode;
			string::iterator iter = exprIn.begin();
			while (*iter != '=') {
				iter++;
			}
			exprIn.erase(exprIn.begin(), ++iter);
			val = to_string(exprEval.infixToPostfix(exprIn));
		} // add token to the symbolTable
		exprEval.addValue(lexAnalysis.tokenInfo[0][idx].first, val);
	}
	else if (lexAnalysis.tokenInfo[0][idx].first == "if" || lexAnalysis.tokenInfo[0][idx].first == "elif" || lexAnalysis.tokenInfo[0][idx].first == "else") { // check for if, elif, else statements
		string condition = "";
		int k = idx + 1;

		if (lexAnalysis.tokenInfo[0][lexAnalysis.tokenInfo[0].size() - 1].first != ":") { // checks for colon, if it is not there then output a syntax error (missing colon)
			for (int i = 0; i < lexAnalysis.tokenInfo[0].size(); i++)
				cout << lexAnalysis.tokenInfo[0][i].first;
			cout << "Invalid syntax. Please make sure that your condition statement ends with ':'" << endl; 
			return;
		}

		if (lexAnalysis.tokenInfo[0][idx].first == "else") {
			newIndent = true;
			if_executed = true;
			return;
		}

		while (lexAnalysis.tokenInfo[0][k].first != ":") { // loops through to get condition and then puts it into the expression evaluator
			condition += lexAnalysis.tokenInfo[0][k].first;
			k++;
		}

		if (exprEval.infixToPostfix(condition)) { // checks if the if condition evaluates to true
			if_loop = true;
			return;
		}
		else {
			failedCondition = true;
			loop_idx = 0;
			return;
		}
	}
	else if (lexAnalysis.tokenInfo[0][idx].first == "while") { // checks for a while loop
		whileCondition = "";
		int k = idx + 1;
		if (lexAnalysis.tokenInfo[0][lexAnalysis.tokenInfo[0].size() - 1].first != ":") {
			cout << "Invalid syntax. Please make sure that your condition statement ends with ':'" << endl; // checks for colon and gives syntax error if it is missing
			return;
		}
		while (lexAnalysis.tokenInfo[0][k].first != ":") { // loops through to get condition and puts it into the expression evaluator
			whileCondition += lexAnalysis.tokenInfo[0][k].first;
			k++;
		}
		if (exprEval.infixToPostfix(whileCondition)) { // checks if the if condition evaluates to true
			while_loop = true;
			return;
		}
		else
			failedCondition = true;
	}
	else if (lexAnalysis.tokenInfo[0][idx].first == "print") { // checks if there is a print statement
		if (lexAnalysis.tokenInfo[0].size() < 4) {
			cout << "Syntax error please revise" << endl << endl; // syntax error 
			return;
		}

		for (int i = 0; i < lexAnalysis.tokenInfo[0].size(); i++) {
			if (lexAnalysis.tokenInfo[0][i].first == ")") { // checks for end parenthesis 
				cout << endl;
				return;
			}
			else if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::STRING_LITERAL) { // checks for a string and then outputs it
				for (int j = 1; j < lexAnalysis.tokenInfo[0][i].first.length() - 1; j++)
					cout << lexAnalysis.tokenInfo[0][i].first[j];
			}
			else if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL) { // checks for a number and then outputs it
				if (lexAnalysis.tokenInfo[0][i + 1].second == LexicalAnalyzer::categoryType::COMMA) // checks for a comma for syntax error
					cout << lexAnalysis.tokenInfo[0][i].first;
				else {
					string str = "";
					while (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::IDENTIFIER 
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::RELATIONAL_OP 
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::LOGICAL_OP 
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::ARITH_OP)
					{ // while the token is any of these, add it to the string
						str += lexAnalysis.tokenInfo[0][i].first;
						i++;
					}
					cout << exprEval.infixToPostfix(str);
				}
			}
			else if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::IDENTIFIER) { // checks for identifier
				if (lexAnalysis.tokenInfo[0][i + 1].second == LexicalAnalyzer::categoryType::COMMA || lexAnalysis.tokenInfo[0][i + 1].second == LexicalAnalyzer::categoryType::RIGHT_PAREN) 
					cout << exprEval.getValue(lexAnalysis.tokenInfo[0][i].first); // checks for commas or right parenthesis
				else {
					string str = "";
					while (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::IDENTIFIER 
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::ASSIGNMENT_OP
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::RELATIONAL_OP 
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::NUMERIC_LITERAL
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::LOGICAL_OP 
						|| lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::ARITH_OP)
					{ // while the token is any of these, add it to the string
						str += lexAnalysis.tokenInfo[0][i].first;
						i++;
					}
					cout << exprEval.infixToPostfix(str);
				}

			}
			else if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::COMMA) { // check for commas and then print a space
				cout << " ";
			}
			else if (lexAnalysis.tokenInfo[0][i].second == LexicalAnalyzer::categoryType::UNKNOWN) { // check for unknowns, if there are any, print a syntax error
				cout << "Error unrecognized syntax. Please review your code." << endl;
				exit(1);
			}

		}
		cout << endl;
	}
}

void Interpreter::showVariables() {
	exprEval.showVariables(); // calls showVariables function from evaluator class
}

void Interpreter::clear() {
	exprEval.clear();
	whileLoop.clear();
	ifStatement.clear();
}

