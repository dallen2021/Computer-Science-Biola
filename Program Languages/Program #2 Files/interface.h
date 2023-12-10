#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class Interface {

private:
    typedef std::vector<std::string> programType;
    programType programCode;

public:
    void startInterface();
    void getInput();
    void help(std::string);
    bool helpInfo(std::string);
    void commands();
    std::vector<std::string> read(std::string);
    void show();
    void showTokens();

};
#endif