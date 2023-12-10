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
#define stringify( name ) #name
using namespace std;

string convertToEnum(int);
bool isLogicalOp(string);
bool isKeyWord(string);
//this is the start of the analyzer 
void LexicalAnalyzer::startAnalysis(vector<string> readfile) {
    int a = 39;
    char ch = char(a);
    string str;
    int x = 1;
    //iterate through every word in the vector of strings
    for (int i = 0; i < readfile.size(); i++) {
        cout << "Line " << x << ":" << endl;
        x++;
        pairType p;
        tokenLineType t;
        int n = 0;
        //iterate through every character in each string 
        for (int j = 0; j < readfile[i].length(); j++) {
            t.clear();
            tokenInfo.clear();
            //check for indents and then pair the string with the enum class type, then push the pair into a vector and then push it further into another vector.
            if (isspace(readfile[i][j]) && isspace(readfile[i][j + 1]) && isspace(readfile[i][j + 2]) && isspace(readfile[i][j + 3]) && j == 0) {
                str.push_back('\t');
                p = { str, categoryType::INDENT };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for spaces and delete them
            else if (isspace(readfile[i][j])) {
                str.push_back(readfile[i][j]);
                str.clear();
            }
            //check for comments
            if (readfile[i][j] == '#') {
                str = readfile[i];
                p = { str, categoryType::COMMENT };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                readfile[i].clear();
                n++;

            }
            //check for keywords
            else if (isalpha(readfile[i][j])) {
                str.push_back(readfile[i][j]);
                if (!isalpha(readfile[i][j + 1])) {
                    if (isKeyWord(str)) {
                        p = { str, categoryType::KEYWORD };
                        t.push_back(p);
                        tokenInfo.push_back(t);
                        print(tokenInfo, n);
                        str.clear();
                        n++;

                    }
                    //check for logical operators
                    else if (isLogicalOp(str)) {
                        p = { str, categoryType::LOGICAL_OP };
                        t.push_back(p);
                        tokenInfo.push_back(t);
                        print(tokenInfo, n);
                        str.clear();
                        n++;
                    }
                    //check for identifier
                    else {
                        p = { str, categoryType::IDENTIFIER };
                        t.push_back(p);
                        tokenInfo.push_back(t);
                        print(tokenInfo, n);
                        str.clear();
                        n++;
                    }
                }
            }
            //check for string literals
            else if (readfile[i][j] == '"' || readfile[i][j] == ch) {
                str.push_back(readfile[i][j]);
                j++;
                while (j <= readfile[i].length()) {
                    if (readfile[i][j] == '"') {
                        str.push_back(readfile[i][j]);
                        goto q;
                    }
                    else if (readfile[i][j] == ch) {
                        str.push_back(readfile[i][j]);
                        goto q;
                    }
                    else {
                        str.push_back(readfile[i][j]);
                        j++;
                    }
                }
                q:
                p = { str, categoryType::STRING_LITERAL };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                t.clear();
                tokenInfo.clear();
                n++;
            }
            //check for left parenthesis
            else if (readfile[i][j] == '(') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::LEFT_PAREN };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for right parenthesis
            else if (readfile[i][j] == ')') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::RIGHT_PAREN };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for arithmetic operators
            else if (readfile[i][j + 1] == '/' && readfile[i][j] == '/' || readfile[i][j + 1] == '*' && readfile[i][j] == '*') {
                str.push_back(readfile[i][j]);
                str.push_back(readfile[i][j + 1]);
                p = { str, categoryType::ARITH_OP };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                readfile[i][j + 1] = ' ';
                n++;
            }
            //check for more arithmetic operators
            else if (readfile[i][j] == '+' || readfile[i][j] == '-' || readfile[i][j] == '*' || readfile[i][j] == '/' || readfile[i][j] == '%') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::ARITH_OP };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for relational operators
            else if (readfile[i][j + 1] == '=' && readfile[i][j] == '=' || readfile[i][j] == '!' || readfile[i][j] == '>' || readfile[i][j] == '<') {
                str.push_back(readfile[i][j]);
                str.push_back(readfile[i][j + 1]);
                p = { str, categoryType::RELATIONAL_OP };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                readfile[i][j + 1] = ' ';
                n++;
            }
            //check for more relational operators
            else if (readfile[i][j] == '>' || readfile[i][j] == '<') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::RELATIONAL_OP };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for assignment operators
            else if (readfile[i][j] == '=') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::ASSIGNMENT_OP };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for numeric literals
            else if (isdigit(readfile[i][j])) {
                str.push_back(readfile[i][j]);
                if (!isdigit(readfile[i][j + 1])) {
                    p = { str, categoryType::NUMERIC_LITERAL };
                    t.push_back(p);
                    tokenInfo.push_back(t);
                    print(tokenInfo, n);
                    str.clear();
                    n++;
                }
            }
            //check for colons
            else if (readfile[i][j] == ':') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::COLON };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //check for commas
            else if (readfile[i][j] == ',') {
                str.push_back(readfile[i][j]);
                p = { str, categoryType::COMMA };
                t.push_back(p);
                tokenInfo.push_back(t);
                print(tokenInfo, n);
                str.clear();
                n++;
            }
            //finally, check for unknowns
            else {
                if (!isspace(readfile[i][j])) {
                    str.push_back(readfile[i][j]);
                    p = { str, categoryType::UNKNOWN };
                    t.push_back(p);
                    tokenInfo.push_back(t);
                    print(tokenInfo, n);
                    str.clear();
                    n++;
                }
            }
        }
        cout << "---------------------------------------------------" << endl;
    }
}

//function to check for logical operators
bool isLogicalOp(string str) {
    vector<string> logicalOperators = { "and", "or", "not" };
    for (int i = 0; i < logicalOperators.size(); i++) {
        if (str == logicalOperators[i]) {
            return true;
        }
    }
    return false;
}

//function to check for keywords
bool isKeyWord(string str) {
    vector<string> keywords = {
        "True", "False", "class",
        "def", "return", "if",
        "elif", "else", "try",
        "except", "raise", "finally",
        "for", "in", "is",
        "from", "import",
        "global", "lambda", "nonlocal",
        "pass", "while", "break",
        "continue", "with",
        "as", "yield", "del",
        "assert", "None", "print"
    };
    for (int i = 0; i < keywords.size(); i++) {
        if (str == keywords[i]) {
            return true;
        }
    }
    return false;
}

//function to print out the vector of vectors containing a pair containing a...
//string and an enum class that has been converted to a string
void LexicalAnalyzer::print(vector<vector<pair<string, categoryType>>>& myVec, int j)
{
    // Iterating over 2D vector elements
    for (auto x : myVec)
    {
        // Each element of the 2D vector is a vector itself
        vector<pair<string, categoryType>> V = x;

        // Iterating over the vector elements
        for (auto y : V)
        {
            int c = static_cast<int>(y.second);
            // Print the elements
            cout << "Token[" << j << "]  " << y.first << " - " << convertToEnum(c) << endl;
        }
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
string convertToEnum(int val)
{
    string MyStr(enumStr[val]);
    return MyStr;
}