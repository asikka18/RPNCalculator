/*
 *  DatumStack.cpp
 *  Armaan Sikka
 *  2/28/24
 *
 *  CS 15 HW 4 CalcYouLater
 *
 *  Function definitions for the DatumStack class.
 *
 */

#include "DatumStack.h"
#include <stdexcept>
#include <sstream>

// Nullary constructor
DatumStack::DatumStack() {
}

/*
 *  name: DatumStack constructor (array)
 *  purpose:  creates a stack initialized so that the elements of the array are
 *            on the stack with the array’s element 0 pushed on first and it’s
 *            (size - 1)th element at the top of the stack
 *  arguments: an array of Datum objects and the size of the array
 */
DatumStack::DatumStack(Datum curr[], int size) {
    
    for (int i = 0; i < size; i++) {
        theStack.push_back(curr[i]);
    }
}

// Nullary destructor
// vector class destructor does the work
DatumStack::~DatumStack() {
}

/*
 *  name: isEmpty
 *  purpose: to check whether the DatumStack is empty or not
 *  arguments: none
 *  returns: true if the DatumStack is empty and false otherwise
 *  effects: none
 */
bool DatumStack::isEmpty() {
    return theStack.empty();
}

/*
 *  name: clear
 *  purpose: to clear the contents of the DatumStack
 *  arguments: none
 *  returns: none
 *  effects: clears the contents of the DatumStack
 */
void DatumStack::clear() {
    theStack.clear();
}

/*
 *  name: size
 *  purpose: returns the size of the DatumStack
 *  arguments: none
 *  returns: an integer value of the size of the DatumStack
 *  effects: none
 */
int DatumStack::size() {
    return theStack.size();
}

/*
 *  name: top
 *  purpose: Returns the top element of the DatumStack and throws an error if
 *           the stack is empty
 *  arguments: none
 *  returns: a reference to the top element on the DatumStack
 *  effects: throws an std::runtime_error if the DatumStack is empty
 */
Datum DatumStack::top() {
    if (theStack.empty()) {
        throw std::runtime_error("empty_stack");

    } else {
        return theStack.back();
    }
}

/*
 *  name: pop
 *  purpose: pops the element on the top of the DatumStack and throws an error
 *           if the DatumStack is empty
 *  arguments: none
 *  returns: none
 *  effects: removes the top element on the DatumStack and throws a
 *           runtime_error if the DatumStack is empty
 */
void DatumStack::pop() {
    if (theStack.empty()) {
        throw std::runtime_error("empty_stack");

    } else {
        return theStack.pop_back();
    }
}

/*
 *  name: push
 *  purpose: to add a Datum object on the top of the DatumStack
 *  arguments: a Datum object
 *  returns: none
 *  effects: adds the given Datum object to the top of the DatumStack
 */
void DatumStack::push(Datum object) {
    theStack.push_back(object);
}

/*
 *  name: toString
 *  purpose: returns a string of the elements in the DatumStack
 *  arguments: none
 *  returns: a string of the elements in the DatumStack
 *  effects: none
 */
std::string DatumStack::toString() {
    std::string ss = "";

    for (int i = 0; i < static_cast<int>(theStack.size()); i++) {
        ss += theStack[i].toString();
    }

    return ss;
}
