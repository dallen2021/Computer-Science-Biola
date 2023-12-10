#ifndef LEXANALYZER_H
#define LEXANALYZER_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

class LexicalAnalyzer {

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
    

private:
    typedef std::vector<std::vector<std::pair<std::string, categoryType>>> tokenType;
    typedef std::vector<std::pair<std::string, categoryType>> tokenLineType;
    typedef std::pair<std::string, categoryType> pairType;
    tokenType tokenInfo;

public:
    void startAnalysis(std::vector<std::string>);
    void print(std::vector<std::vector<std::pair<std::string, categoryType>>>&, int);
    
};
#endif