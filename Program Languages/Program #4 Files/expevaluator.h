#ifndef EXPEVALUATOR_H
#define EXPEVALUATOR_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include "lexanalyzer.h"
#include "interface.h"
#include "interpreter.h"

using std::string;
using std::vector;
using std::pair;
using std::map;

class expEvaluator {

    friend class Interface;
    friend class LexicalAnalyzer;
    friend class Interpreter;

private:
    typedef map<string, string> symbolTableType;
    symbolTableType symbolTable;

public:
    int infixToPostfix(string);
    int postfixEval(vector<pair<string, LexicalAnalyzer::categoryType>>);
    int variableEval(int, int, string);
    int precedence(pair<string, LexicalAnalyzer::categoryType>);
    bool is_higher_precedence(pair<string, LexicalAnalyzer::categoryType> scanned, pair<string, LexicalAnalyzer::categoryType> stackTop);
    int getValue(string key);
    void addValue(string key, string value);
    void clear(); 
    void showVariables();

};
#endif