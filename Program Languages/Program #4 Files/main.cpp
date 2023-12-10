#include <iostream>
#include "interface.h"
#include "interface.cpp"
#include "lexanalyzer.h"
#include "lexanalyzer.cpp"
#include "expevaluator.h"
#include "expevaluator.cpp"
#include "interpreter.h"
#include "interpreter.cpp"
using namespace std;

int main()
{
     Interface pySubInterpreter;

     // Start the interface
     pySubInterpreter.startInterface();

     return 0;
}