/*
 *  main.cpp
 *  Armaan Sikka
 *  2/28/24
 *
 *  CS 15 HW 4 CalcYouLater
 *
 *  Function definition for parseRString function.
 *
 */

#include <string>
#include <iostream>
using namespace std;


/*
 * name: parseRString
 * purpose: To convert input into an rstring type with a specified format
 * arguments: the input stream
 * returns: an rstring of the input in the specified format
 * effects: converst the input into the specified format for an rstring
 */
string parseRString(istream &input) {
    string rs = "{";
    string check;
    int count = 1;
    bool end_reached = false;

    while ((not input.eof()) and (not end_reached)) {
        input >> check;

        if (check != " ") {
            rs += " ";
            rs += check;
        }

        if (check == "{") {
            count++;
        }

        if (check == "}") {
            count--;
        }

        if (count == 0) {
            end_reached = true;
        }
    }

    return rs;
}
