#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <ranges>
#include <regex>
#include "interface.h"
#include "lexanalyzer.h"
#include "expevaluator.h"
#include "interpreter.h"
#define stringify( name ) #name
using namespace std;

string convertToEnum(int);
bool isLogicalOp(string);
bool isKeyWord(string);

// analyzer start
void LexicalAnalyzer::startAnalysis(string readfile, int lineCount)
{
    pairType p;
    tokenLineType t; 
    tokenInfo.push_back(t);
    for (int i = 0; i < readfile.length(); i++) {
        string str = "";
        if (readfile[i] == ' ' || readfile[i] == '\t')
        {
            if (i == 0)
            {
                while (readfile[i] == ' ' || readfile[i] == '\t')
                {
                    str = str + readfile[i];
                    i++;
                }
                p = make_pair(str, categoryType::INDENT);
                tokenInfo[lineCount].push_back(p);
                i--;
            }
            else
                continue;
        }
        else if (isdigit(readfile[i])) { // if character is a digit
            while (isdigit(readfile[i])) { // gets all digits until it is something else
                str = str + readfile[i];
                i++;
            }
            p = make_pair(str, categoryType::NUMERIC_LITERAL);
            tokenInfo[lineCount].push_back(p);
            i--;
        }
        else if (isalpha(readfile[i])) { // if alphabet character
            while (isalpha(readfile[i])) { // read all alphabet characters into string until it is something else
                str = str + readfile[i];
                i++;
            }

            if (str == "print" || str == "elif" || str == "if" || str == "else" || str == "while" || str == "int" || str == "input") // if keyword
                p = make_pair(str, categoryType::KEYWORD);

            else if (str == "and" || str == "or" || str == "not") // if logical operator
                p = make_pair(str, categoryType::LOGICAL_OP);
            else // if neither of above then identifier
                p = make_pair(str, categoryType::IDENTIFIER);

            tokenInfo[lineCount].push_back(p);
            i--;
        }
        else if (readfile[i] == '(') { //if left parenthesis
            p = make_pair(readfile[i], categoryType::LEFT_PAREN);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == ')') { // if right parenthesis
            p = make_pair(readfile[i], categoryType::RIGHT_PAREN);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == ':') { // if colon
            p = make_pair(readfile[i], categoryType::COLON);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == ',') { // if comma
            p = make_pair(readfile[i], categoryType::COMMA);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '>' || readfile[i] == '<') { // if relational operator (>, <)
            str = readfile[i];

            if (readfile[i + 1] == '=') // if next char is equal then relational operator
            {
                str = str + readfile[i + 1];
                p = make_pair(str, categoryType::RELATIONAL_OP);
                tokenInfo[lineCount].push_back(p);
                i++;
                continue;
            }
            else // if not then relational operator
                p = make_pair(readfile[i], categoryType::RELATIONAL_OP);

            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '=') { // if char is equal
            str = readfile[i];

            if (readfile[i + 1] == '=') {// if next char is also equal then relational operator
                str = str + readfile[i + 1];
                p = make_pair(str, categoryType::RELATIONAL_OP);
                tokenInfo[lineCount].push_back(p);
                i++;
                continue;
            }
            else // if not then assignment operator
                p = make_pair(readfile[i], categoryType::ASSIGNMENT_OP);

            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '!') { // if not (!)
            str = readfile[i];
            if (readfile[i + 1] == '=') {// if the next char is equal then relational operator
                str = str + readfile[i + 1];
                p = make_pair(str, categoryType::RELATIONAL_OP);
                tokenInfo[lineCount].push_back(p);
                i++;
                continue;
            }
            else // if nothing else, then unknown
                p = make_pair(readfile[i], categoryType::UNKNOWN);

            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '+' || readfile[i] == '-' || readfile[i] == '/' || readfile[i] == '*' || readfile[i] == '%')
        { //if arithmetic op
            p = make_pair(readfile[i], categoryType::ARITH_OP);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '#') {//if comment start
            for (i; i < readfile.size(); i++)
            {
                str = str + readfile[i];
            }
            p = make_pair(str, categoryType::COMMENT);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '\'') //if single quote
        {
            str = readfile[i];
            i++;
            while (readfile[i] != '\'' && i < readfile.size())
            {
                str = str + readfile[i];
                i++;
            }
            str = str + '\'';
            p = make_pair(str, categoryType::STRING_LITERAL);
            tokenInfo[lineCount].push_back(p);
        }
        else if (readfile[i] == '\"') //if double quote
        {
            str = readfile[i];
            i++;
            while (readfile[i] != '\"' && i < readfile.size())
            {
                str = str + readfile[i];
                i++;
            }
            str = str + '\"';
            p = make_pair(str, categoryType::STRING_LITERAL);
            tokenInfo[lineCount].push_back(p);
        }
        else //if none of above cases, unknown
        {
            p = make_pair(readfile[i], categoryType::UNKNOWN);
            tokenInfo[lineCount].push_back(p);
        }
    }
}
    

vector<pair<string, LexicalAnalyzer::categoryType>> LexicalAnalyzer::sendTokens(int lineCount) { // sends tokens to expression evaluator
    vector<pair<string, LexicalAnalyzer::categoryType>> data;
    for (int i = 0; i < tokenInfo[lineCount].size(); i++) {
        data.push_back(tokenInfo[lineCount][i]);
    }
    return data;
}

void LexicalAnalyzer::print() { // iterate through the tokenInfo and output each part of each pair with its respective token # and line #
    if (!tokenInfo.size()) {
        cout << "No token data available" << endl;
        return;
    }

    cout << "\n----------TOKEN INFORMATION-----------" << endl;
    for (int i = 0; i < tokenInfo.size(); i++)
    {
        cout << "LINE #" << i+1 << ":" << endl;
        for (int j = 0; j < tokenInfo[i].size(); j++)
        {
            int c = static_cast<int>(tokenInfo[i][j].second);
            cout << "TOKEN[" << j << "]:\t";
            cout << tokenInfo[i][j].first << " - " << convertToEnum(c) << endl;
        }
        cout << "-----------------------------------" << endl;
    }
}

bool LexicalAnalyzer::is_expression(string Input) {
    tokenInfo.clear();
    startAnalysis(Input, 0);

    for (int i = 0; i < tokenInfo[0].size(); i++) {
        if (tokenInfo[0][i].second != categoryType::INDENT) {
            continue;
        }
        if (tokenInfo[0][i].second != categoryType::RELATIONAL_OP ||
            tokenInfo[0][i].second != categoryType::LOGICAL_OP ||
            tokenInfo[0][i].second != categoryType::ARITH_OP ||
            tokenInfo[0][i].second != categoryType::NUMERIC_LITERAL ||
            tokenInfo[0][i].second != categoryType::LEFT_PAREN ||
            tokenInfo[0][i].second != categoryType::RIGHT_PAREN) {
            tokenInfo.clear();
            return false;
        }
        tokenInfo.clear();
        return true;
    }
}

//array containing strings of the enum classes
static const char* enumStr[] =
{ "KEYWORD", "IENTIFIER", "STRING_LITERAL",
  "NUMERIC_LITERAL", "ASSIGNMENT_OP", "ARITH_OP",
  "LOGICAL_OP", "RELATIONAL_OP", "LEFT_PAREN",
  "RIGHT_PAREN", "COLON", "COMMA",
  "COMMENT", "INDENT", "UNKNOWN"
};

//function to convert the enum classes into a string and return the value
string convertToEnum(int val) {
    string MyStr(enumStr[val]);
    return MyStr;
}

void LexicalAnalyzer::clear() {
    tokenInfo.clear();
}