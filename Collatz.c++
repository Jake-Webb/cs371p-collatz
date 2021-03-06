// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#include "Collatz.h"

int calculateCycleLength(int);

using namespace std;

const int CACHESIZE = 1000;

int cache[CACHESIZE];

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int collatz_eval (int low, int high) {
    int switchNum;
    if(low > high) { // will set the ints so low is the smaller value
        switchNum = low;
        low = high;
        high = switchNum;
    }
    int max = calculateCycleLength(low);
    int temp;
    int newLow = (high / 2) + 1; // optimize the range by only checking the upper half
    if(newLow > low)
        low = newLow;
    for(int i = low; i <= high; i++) { // calculating cycleLength of every number in new range
        temp = calculateCycleLength(i); // and maintaining the max value
        if(temp > max)
            max = temp;
        }
    return max;
}

int calculateCycleLength(int num) {
    int cycleLength = 1;
    int origNum = num;
    while(num > 1) {
        if(num < CACHESIZE) { // check if value is in cache
            if(cache[num]) {
                cycleLength += cache[num] - 1; // if it is use it instead of calculating
                break;
            }
        }
        if(num % 2 == 0) {
            num /= 2;
            cycleLength++;
        }
        else {
            num = num + (num >> 1) + 1; // odd optimization, can do two calculations at once
            cycleLength = cycleLength + 2;
        }
    }
    if(origNum < CACHESIZE)
        cache[origNum] = cycleLength; // store cycleLength in cache
    return cycleLength;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
