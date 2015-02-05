#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int calculateCycleLength(int);
int maxCycleLength(int, int);
void printCache();
void printCache(int, int);

const int CACHESIZE = 1000;

int cache[CACHESIZE];

int main() {
	int i, j, i2, j2, max;
	string input, output;
	//printCache();
	while(getline(cin, input)) {
		stringstream stream(input);
		stream >> i;
		stream >> j;
		if(j < i){
			i2 = j;
			j2 = i;
		}
		else {
			i2 = i;
			j2 = j;
		}
		max = maxCycleLength(i2, j2);
		//printCache(i2, j2);
		cout << i << " " << j << " " << max << endl;
	}
	return 0;
}

int maxCycleLength(int low, int high) {
	int max = calculateCycleLength(low);
	int temp;
	int newLow = (high / 2) + 1;
	if(newLow > low)
		low = newLow;
	for(int i = low; i <= high; i++) {
		temp = calculateCycleLength(i);
		//cout << i << "'s cycleLength is: " << temp << endl;
		if(temp > max)
			max = temp;
		}
	return max;
}

int calculateCycleLength(int num) {
	int cycleLength = 1;
	int origNum = num;
	while(num != 1) {
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

void printCache() {
	for(int i = 1; i < CACHESIZE; i++) {
		cout << i << "'s cycleLength is: " << cache[i] << endl;
	}
}

void printCache(int low, int high) {
	for(int i = low; i < high; i++) {
		cout << i << "'s cycleLength is: " << cache[i] << endl;
	}
}