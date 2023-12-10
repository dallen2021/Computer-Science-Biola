#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "expevaluator.h"
#include "lexanalyzer.h"
#include "interpreter.h"

class Interface {

    friend class LexicalAnalyzer;
    friend class expEvaluator;
    friend class Interpreter;

private:
    typedef std::vector<std::string> programType;
    programType programCode;

public:
    void startInterface();
    void getInput();
    void help(std::string);
    bool helpInfo(std::string);
    void commands();
    void read(std::string);
    void show();
    bool is_expression(string);
    void showTokens();

};
#endif