#ifndef LEXANALYZER_H
#define LEXANALYZER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "expevaluator.h"
#include "interface.h"
#include "interpreter.h"

using std::string;
using std::vector;
using std::pair;
using std::map;

class LexicalAnalyzer {

    friend class Interface;
    friend class Interpreter;
    friend class LexicalAnalyzer;

public:
    enum class categoryType
    {
        KEYWORD,
        IDENTIFIER,
        STRING_LITERAL,
        NUMERIC_LITERAL,
        ASSIGNMENT_OP,
        ARITH_OP,
        LOGICAL_OP,
        RELATIONAL_OP,
        LEFT_PAREN,
        RIGHT_PAREN,
        COLON,
        COMMA,
        COMMENT,
        INDENT,
        UNKNOWN
    };
    void startAnalysis(string, int);
    void print();
    bool is_expression(string);
    void clear();
    vector<pair<string, categoryType>> sendTokens(int lineCount);

private:
    typedef vector<vector<pair<string, categoryType>>> tokenType;
    typedef vector<pair<string, categoryType>> tokenLineType;
    typedef pair<string, categoryType> pairType;
    tokenType tokenInfo;

};
#endif