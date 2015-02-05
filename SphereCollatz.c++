#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

using namespace std;

pair<int, int> collatz_read (const string&);
int collatz_eval (int, int);
int calculateCycleLength(int);
void collatz_print (ostream&, int, int, int);
void collatz_solve (istream&, ostream&);

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
    return make_pair(i, j);
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int low, int high) {
    int switchNum;
    if(low > high) {
        switchNum = low;
        low = high;
        high = switchNum;
    }
    int max = calculateCycleLength(low);
    int temp;
    int newLow = (high / 2) + 1;
    if(newLow > low)
        low = newLow;
    for(int i = low; i <= high; i++) {
        temp = calculateCycleLength(i);
        if(temp > max)
            max = temp;
        }
    return max;
}

// --------------------
// calculateCycleLength
// --------------------

int calculateCycleLength(int num) {
    int cycleLength = 1;
    int origNum = num;
    while(num > 1) {
        if(num < CACHESIZE) {
            if(cache[num]) {
                cycleLength += cache[num] - 1;
                break;
            }
        }
        if(num % 2 == 0) {
            num /= 2;
            cycleLength++;
        }
        else {
            num = num + (num >> 1) + 1;
            cycleLength = cycleLength + 2;
        }
    }
    if(origNum < CACHESIZE)
        cache[origNum] = cycleLength;
    return cycleLength;
}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;
}

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
        collatz_print(w, i, j, v);
    }
}

#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

// ----
// main
// ----

int main () {
    collatz_solve(cin, cout);
    return 0;
}