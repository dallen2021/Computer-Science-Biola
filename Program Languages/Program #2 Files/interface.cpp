#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "interface.h"
#include "lexanalyzer.h"
using namespace std;

//this is the first interface that shows when you start the program, it displays information on the interpreter 
void Interface::startInterface() {
    LexicalAnalyzer lexAnalysis;
    cout << "PySUB Interpreter 1.0 on Windows (September 2020)" << endl;
    cout << "Enter program lines or read(<filename>.py) at command line interface" << endl;
    cout << "Type 'help' for more information or 'quit' to exit" << endl;
    //calls the getInput function to get user input for commands
    getInput();
}

//gets the user input and decyphers what word it is and finds if there are any inputs placed between the parentheses
void Interface::getInput() {
q:
    string pyfile;
    string Input = "";
    cout << ">>> ";
    getline(cin, Input);
    int l = Input.length();
    //checks if user typed help and checks what they typed after the word or between the parentheses
    if (Input[0] == 'h' && Input[1] == 'e' && Input[2] == 'l' && Input[3] == 'p' && Input[4] == '(' && Input[l - 1] == ')') {
        string check;
        for (int i = 5; i < l - 1; i++) {
            check.push_back(Input[i]);
        }
        if (helpInfo(check)) {
            goto q;
        }
        help(Input);
        cout << endl;
        goto q;
    }
    else if (Input[0] == 'h' && Input[1] == 'e' && Input[2] == 'l' && Input[3] == 'p') {
        string check;
        for (int i = 5; i < l; i++) {
            check.push_back(Input[i]);
        }
        if (helpInfo(check)) {
            goto q;
        }
        help(Input);
        cout << endl;
        goto q;
    }
    //checks if user typed read and check what they typed after the word or between parentheses
    else if (Input[0] == 'r' && Input[1] == 'e' && Input[2] == 'a' && Input[3] == 'd' && Input[4] == '(' && Input[l - 1] == ')') {
        for (int i = 5; i < l - 1; i++) {
            pyfile.push_back(Input[i]);
        }
        if (pyfile == ""){
            cout << "Please enter a valid filename." << endl << endl;
            goto q;
        }
        programCode = read(pyfile);
        goto q;
    }
    else if (Input[0] == 'r' && Input[1] == 'e' && Input[2] == 'a' && Input[3] == 'd') {
        for (int i = 5; i < l; i++) {
            pyfile.push_back(Input[i]);
        }
        if (pyfile == ""){
            cout << "Please enter a valid filename." << endl << endl;
            goto q;
        }
        programCode = read(pyfile);
        goto q;
    }
    //user input for show
    else if (Input[0] == 's' && Input[1] == 'h' && Input[2] == 'o' && Input[3] == 'w' && Input[4] == '(' && Input[l - 1] == ')') {
        string check;
        for (int i = 5; i < l - 1; i++) {
            check.push_back(Input[i]);
        }
        if (check == "") {
            show();
        }
        else if (check != "tokens") {
            cout << "Invalid input, please enter 'tokens' inside of the brackets or after the word, or nothing at all" << endl << endl;
            goto q;
        }
        else if (check == "tokens") {
            showTokens();
        }
        cout << endl;
        goto q;
    }
    else if (Input[0] == 's' && Input[1] == 'h' && Input[2] == 'o' && Input[3] == 'w') {
        string check;
        for (int i = 5; i < l; i++) {
            check.push_back(Input[i]);
        }
        if (check == "") {
            show();
        }
        else if (check != "tokens") {
            cout << "Invalid input, please enter 'tokens' inside of the brackets or after the word, or nothing at all" << endl << endl;
            goto q;
        }
        else if (check == "tokens") {
            showTokens();
        }
        cout << endl;
        goto q;
    }
    //user input for clear
    else if (Input == "clear" || Input == "clear()") {
        programCode.clear();
        goto q;
    }
    //user input for quit or exit
    else if (Input == "quit" || Input == "quit()" || Input == "exit" || Input == "exit()") {
        exit(0);
    }
    else {
        cout << "Please input a valid command!" << endl << endl;
        goto q;
    }
}

//the entirety of the help utility is in this function
void Interface::help(string o) {
    if (o == "help" || o == "help()") {
        cout << "You have entered the help utility!" << endl;
        cout << "* To exit and return to the interpreter, type 'exit'" << endl;
        cout << "* To get a list of commands, type 'commands'" << endl;
        cout << "* To get a description of any command, just type the command at the help> prompt" << endl << endl;
    }
q:
    string Input = "";
    cout << "help> ";
    getline(cin, Input);
    //this entire set of code past this comment checks if the user types in any commands while in the help utility, if so it displays information
    if (Input == "exit" || Input == "exit()") {
        return;
    }
    else if (Input == "commands" || Input == "commands()") {
        commands();
        goto q;
    }
    if (Input == "clear" || Input == "clear()") {
        cout << "This command will clear all data that was copied from the file that was read." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        goto q;
    }
    else if (Input == "help" || Input == "help()") {
        cout << "This command enters the help utility." << endl;
        cout << "In the help utility you can see all commands that you can use and more information." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        goto q;
    }
    else if (Input == "quit" || Input == "quit()") {
        cout << "This command exits the command line interpreter." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        goto q;
    }
    else if (Input == "read" || Input == "read()") {
        cout << "This command takes a filename and stores it into a data structure." << endl;
        cout << "You can use the command 'show' to show the elements of the file." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        goto q;
    }
    else if (Input == "show" || Input == "show()") {
        cout << "Show will print out all of the elements of a file that was read with 'read'." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
        cout << "If you type 'tokens' in the brackets or after the word 'show', it will display all tokens in the program." << endl << endl;
        goto q;
    }
    else {
        cout << "Please enter a valid command!"<<endl<<endl;
        goto q;
    }
}

//display further information on each command if typed into the utility correctly
bool Interface::helpInfo(string check) {
    //this checks if the user typed in help('command') into the interpreter and displays information, even if they weren't in the help utility directly
    if (check == "clear" || check == "clear()") {
        cout << "This command will clear all data that was copied from the file that was read." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        return true;
    }
    else if (check == "help" || check == "help()") {
        cout << "This command enters the help utility." << endl;
        cout << "In the help utility you can see all commands that you can use and more information." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        return true;
    }
    else if (check == "quit" || check == "quit()") {
        cout << "This command exits the command line interpreter." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        return true;
    }
    else if (check == "read" || check == "read()") {
        cout << "This command takes a filename and stores it into a data structure." << endl;
        cout << "You can use the command 'show' to show the elements of the file." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl << endl;
        return true;
    }
    else if (check == "show" || check == "show()") {
        cout << "Show will print out all of the elements of a file that was read with 'read'." << endl;
        cout << "To exit the help utility and return to the interpreter, enter 'exit'" << endl;
        cout << "If you type 'tokens' in the brackets or after the word 'show', it will display all tokens in the program." << endl << endl;
        return true;
    }
    else if (check != "") {
        cout << "help("<<check<<") is not a valid command!"<<endl<<endl;
        return true;
    }
    return false;
}

//run the commands interface
void Interface::commands() {
    cout << "Below is a list of commands.Enter any command at the prompt to get more help\nclear\thelp\tquit\nread\tshow\n" << endl;
    cout << "NOTE: All commands can also be entered as functions:\nclear()\thelp()\tquit()\nread()\tshow()\n" << endl;
}

//read the contents of a file and place them into a vector
vector<string> Interface::read(string pyfile) {
    string line;
    ifstream myfile(pyfile);
    //while the file is open it will read line by line and put all lines into a vector
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            programCode.push_back(line);
        }
        myfile.close();
        cout << "File read successfully!" << endl << endl;
    }
    else {
        cout << "Unable to read the file or file does not exist!" << endl << endl;
    }
    return programCode;
}

//show the contents of the file that was read
void Interface::show() {
    //for loop iterates through the vector of file lines and prints them to the screens
    for (int i = 0; i < programCode.size(); i++) {
        cout << "[" << i << "]\t" << programCode[i] << endl;
    }
    cout << endl;
}

void Interface::showTokens() {
    LexicalAnalyzer lexAnalysis;
    lexAnalysis.startAnalysis(programCode);
}