/*
 *  RPNCalc.cpp
 *  Armaan Sikka
 *  2/28/24
 *
 *  CS 15 HW 4 CalcYouLater
 *
 *  Function definitions of RPNCalc class.
 *
 */

#include "RPNCalc.h"

using namespace std;

// Nullary Constructor
RPNCalc::RPNCalc() {
}

// Nullary Destructor
RPNCalc::~RPNCalc() {
}

/*
 * name: run
 * purpose: execute the command for the queryLoop function
 * arguments: none
 * returns: none
 * effects: prints a thank-you message to cerr after queryLoop has terminated
 */
void RPNCalc::run() {
    queryLoop(cin);
    cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name: queryLoop
 * purpose: starts and executes a query loop which prompts the user for
 *           commands
 * arguments: input-stream reference
 * returns: none
 * effects: executes the specified functions on the stack
 */
void RPNCalc::queryLoop(istream &input) {
    string query;
    int intResult;

    while (input >> query and query != "quit") {

        if (got_int(query, &intResult)) {
            myStack.push(Datum(intResult));

        } else if (query == "#f") {
            myStack.push(Datum(false));

        } else if (query == "#t") {
            myStack.push(Datum(true));

        } else if (query[0] == '{') {
            myStack.push(Datum(parseRString(input)));

        } else if (query == "print") {
            print();

        } else if (query == "not") {
            makeNot();

        } else if (query == "clear") {
            myStack.clear();

        } else if (query == "drop") {
            drop();

        } else if (query == "dup") {
            dup();

        } else if (query == "swap") {
            swap();

        } else if (query == "-" or query == "+" or query == "*" or query == "/"
                    or query == "mod" or query == ">" or query == "<"
                    or query == ">=" or query == "<=" or query == "==") {
            mathematics(query);
        } else if (query == "exec") {
            exec();

        } else if (query == "if") {
            executeIf();

        } else if (query == "file") {
            executeFile();

        } else {
            cerr << query << ": unimplemented\n";
        }
    }
}

/*
 * name: got_int
 * purpose: to check whether a given string contains an integer or not
 * arguments: the string in question and the address of a integer variable
 * returns: a boolean value of true if the string given contains an integer and
 *          false if not
 * effects: none
 */
bool RPNCalc::got_int(string s, int *resultp)
{
    /* Holds the first non-whitespace character after the integer */
    char extra;

    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name: print
 * purpose: to print the top element of the stack
 * arguments: none
 * returns: none
 * effects: prints the top element of the stack to cout
 */
void RPNCalc::print() {
    string err_msg = "";

    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }

    try {
        if (myStack.top().isInt()) {
            cout << myStack.top().getInt() << endl;

        } else if (myStack.top().isBool()) {
            if (myStack.top().getBool()) {
                cout << "#t" << endl;

            } else {
                cout << "#f" << endl;
            }

        } else if (myStack.top().isRString()) {
            cout << myStack.top().getRString() << endl;
        }
    } catch (const runtime_error &e) {
        err_msg = e.what();
        cerr << "Error: " << err_msg << endl;
    }
}

/*
 *  name: swap
 *  purpose: to swap the topmost element with the second topmost element in the
 *           stack
 *  arguments: none
 *  returns: none
 *  effects: swaps the topmost element with the second topmost element in the
 *           stack
 */
void RPNCalc::swap() {
    string err_msg = "";

    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }

    try {
        Datum temp1 = myStack.top();
        myStack.pop();
        Datum temp2 = myStack.top();
        myStack.pop();
        myStack.push(temp1);
        myStack.push(temp2);

    } catch (const runtime_error &e) {
        err_msg = e.what();
        cerr << "Error: " << err_msg << endl;
    }
}

/*
 *  name: drop
 *  purpose: to remove the top element from the stack
 *  arguments: none
 *  returns: none
 *  effects: removes the top element from the stack
 */
void RPNCalc::drop() {
    string err_msg = "";

    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }
    
    try {
        myStack.pop();
    } catch (const runtime_error &e) {
        err_msg = e.what();
        cerr << "Error: " << err_msg << endl;
    }
}

/*
 *  name: dup
 *  purpose: to duplicate the top element of the stack and push it onto the 
 *           stack
 *  arguments: none
 *  returns: none
 *  effects: duplicates the top element of the stack and pushes it onto the
 *           stack
 */
void RPNCalc::dup() {
    string err_msg = "";

    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }
    
    try {
        myStack.push(myStack.top());
    } catch (const runtime_error &e) {
        err_msg = e.what();
        cerr << "Error: " << err_msg << endl;
    }
}

/*
 *  name: makeNot
 *  purpose: to pop the top element from the stack and push the opposite boolean
 *           value of the popped Datum object back onto the stack
 *  arguments: none
 *  returns: none
 *  effects: swaps the boolean value of the topmost element of the stack
 */
void RPNCalc::makeNot() {
    string err_msg = "";

    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }

    Datum temp = myStack.top();
    myStack.pop();

    try {
        temp.isBool();
        bool check = temp.getBool();

        if (check) {
            myStack.push(Datum(true));

        } else {
            myStack.push(Datum(false));
        }
    } catch (const runtime_error &e) {
        err_msg = e.what();
        cerr << "Error: " << err_msg << endl;
    }
}

/*
 *  name: mathematics
 *  purpose: to execute the inputted mathematical function on the two topmost
 *           elements in the stack and push the new Datum object with the new
 *           integer value onto the stack
 *  arguments: a string variable of the query type inputted by the user
 *  returns: none
 *  effects: pops the two topmost elements of the stack and pushes a new Datum
 *           object with the new integer value onto the stack
 */
void RPNCalc::mathematics(string query) {
    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack" << endl;
        return;
    }

    Datum temp1 = myStack.top();
    myStack.pop();
    Datum temp2 = myStack.top();
    myStack.pop();

    if (temp1.isInt() and temp2.isInt()) {
        int num1, num2;

        num1 = temp1.getInt();
        num2 = temp2.getInt();

// checking for each mathematical operator or logical comparison operator
        if (query == "==") {
            if (num2 == num1) {
                myStack.push(Datum(true));
            } else {
                myStack.push(Datum(false));
            }
        } else if (query == "<=") {
            if (num2 <= num1) {
                myStack.push(Datum(true));
            } else {
                myStack.push(Datum(false));
            }
        } else if (query == ">=") {
            if (num2 >= num1) {
                myStack.push(Datum(true));
            } else {
                myStack.push(Datum(false));
            }
        } else if (query == "<") {
            if (num2 < num1) {
                myStack.push(Datum(true));
            } else {
                myStack.push(Datum(false));
            }
        } else if (query == ">") {
            if (num2 > num1) {
                myStack.push(Datum(true));
            } else {
                myStack.push(Datum(false));
            }
        } else if (query == "mod") {
            myStack.push(Datum(num2 % num1));

        } else if (query == "/") {
            myStack.push(Datum(num2 / num1));

        } else if (query == "-") {
            myStack.push(Datum(num2 - num1));

        } else if (query == "+") {
            myStack.push(Datum(num1 + num2));

        } else if (query == "*") {
            myStack.push(Datum(num1 * num2));
        }

    } else {
        cerr << "Error: datum_not_int\n";
    }
}

/*
 *  name: exec
 *  purpose: to pop the topmost element off the stack and use the contents as
 *           commands to run in the queryLoop function
 *  arguments: none
 *  returns: none
 *  effects: prints a message to cerr if the stack is empty or the topmost
 *           element is not an rString
 */
void RPNCalc::exec() {
    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    } 

    Datum temp = myStack.top();
    myStack.pop();

    if (temp.isRString()) {
        string check = temp.getRString();
        check[0] = ' ';
        check[check.length() - 1] = ' ';
        istringstream input(check);
        queryLoop(input);

    } else {
        cerr << "Error: cannot execute non rstring\n";
        return;
    }
}

/*
 *  name: executeIf
 *  purpose: if the test condition is true, the true case is executed and the
 *           false case is executed if the condition is false
 *  arguments: none
 *  returns: none
 *  effects: prints messages to cerr if the top 2 elements on the stack aren't
 *           rStrings and if the test condition isn't a boolean
 */
void RPNCalc::executeIf() {
    string err_msg = "";
    
    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }

    try {
        Datum temp1 = myStack.top();
        myStack.pop();
        Datum temp2 = myStack.top();
        myStack.pop();
        Datum condition = myStack.top();
        myStack.pop();

// checks whether top two elements of the stack are rStrings or not
        if (temp1.isRString() and temp2.isRString()) {

// checks whether test condition is a boolean or not
            if (condition.isBool()) {

// checks whether test condition is true or false and executes the specified
// case for each possible result
                if (condition.getBool()) {
                    string check = temp2.getRString();
                    check[0] = ' ';
                    check[check.length() - 1] = ' ';
                    istringstream input(check);
                    queryLoop(input);

                } else {
                    string check = temp1.getRString();
                    check[0] = ' ';
                    check[check.length() - 1] = ' ';
                    istringstream input(check);
                    queryLoop(input);
                }

            } else {
                cerr << "Error: expected boolean in if test\n";
                return;
            }
        } else {
            cerr << "Error: expected rstring in if branch\n";
            return;
        }
    } catch (const runtime_error &e) {
        cerr << "Error: " << err_msg << "\n";
        return;
    }
}

/*
 *  name: executeFile
 *  purpose: pops the topmost element off the stack and opens the file specified
 *           in the element and executes the contents as input
 *  arguments: none
 *  returns: none
 *  effects: prints messages to cerr if the file specified cannot be opened or
 *           read and if the topmost element is not an rString
 */
void RPNCalc::executeFile() {
    if (myStack.isEmpty()) {
        cerr << "Error: empty_stack\n";
        return;
    }
    
    Datum temp = myStack.top();
    myStack.pop();

    if (temp.isRString()) {
        string filename = temp.getRString();
        ifstream infile;
        infile.open(filename);

        if(not infile.is_open()) {
            cerr << "Unable to read " << filename << "\n";
            return;
        }

        queryLoop(infile);

    } else {
        cerr << "Error: file operand not rstring\n";
        return;
    }
}
