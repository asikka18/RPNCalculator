/*
 *  RPNCalc.h
 *  Armaan Sikka
 *  2/28/24
 *
 *  CS 15 HW 4 CalcYouLater
 *
 *  Function definitions for RPNCalc class.
 *
 */

#include "DatumStack.h"
#include "Datum.h"
#include "parser.h"
#include <iomanip>
#include <string>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

class RPNCalc {
public:
    RPNCalc();
    ~RPNCalc();
    void run();

private:
    DatumStack myStack;
    void queryLoop(istream &input);
    bool got_int(string s, int *resultp);
    void print();
    void swap();
    void drop();
    void dup();
    void makeNot();
    void mathematics(string query);
    void exec();
    void executeIf();
    void executeFile();
};
