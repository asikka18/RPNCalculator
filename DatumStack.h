/*
 *  DatumStack.h
 *  Armaan Sikka
 *  2/28/24
 *
 *  CS 15 HW 4 CalcYouLater
 *
 *  Function declarations for DatumStack class.
 *
 */

#include "Datum.h"
#include <vector>

class DatumStack {
public:
    DatumStack();
    DatumStack(Datum curr[], int size);
    ~DatumStack();

    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(Datum object);

private:
    std::vector<Datum> theStack;
    std::string toString();
};
