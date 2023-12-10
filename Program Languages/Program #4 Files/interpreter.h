#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"

using std::string;
using std::vector;
using std::pair;
using std::map;

class Interpreter {

	friend class Interface;
	friend class expEvaluator;
	friend class LexicalAnalyzer;

private:
	vector<string> whileLoop;
	vector<string> ifStatement;
	vector<vector<string>> elifBlock;
	vector<string> elseBlock;

public:
	void run(vector<string>);
	void interpretCode(string);
	void showVariables();
	void clear();
	bool if_loop = false, while_loop = false, if_executed = false, failedCondition = false, newIndent = false;
	int loop_idx = 0;
	string whileCondition, loop_indent;


};


#endif