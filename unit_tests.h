/*  unit_tests.h
 *  Armaan Sikka
 *  2/28/24
 *
 *  CS 15 HW 4 - CalcYouLater
 *
 *  A testing file for the DatumStack class that uses the unit_test
 *  framework
 */

#include "DatumStack.h"
#include "Datum.h"
#include <cassert>
#include <iostream>

using namespace std;

void constructor_test() {
    DatumStack test;
}

void arr_constructor_test() {
    Datum data[] = {Datum(1), Datum (10), Datum(20)};
    DatumStack test(data, 3);
    assert(test.size() == 3);
    assert(test.top().getInt() == 20);
    assert(not test.isEmpty());
}

void isEmpty_test() {
    DatumStack test;
    assert(test.isEmpty());
}

void pop_test() {
    Datum data[] = {Datum(1), Datum (10), Datum(20)};
    DatumStack test(data, 3);

    test.pop();
    assert(test.size() == 2);

    test.pop();
    assert(test.size() == 1);
}

void push_test() {
    DatumStack test;
    test.push(Datum(1));
    test.push(Datum(300));

    assert(test.size() == 2);
    assert(test.top().getInt() == 300);
}
