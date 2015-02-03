#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int calculateCycleLength(int);
int maxCycleLength(int, int);

int main() {
	int i, j, i2, j2, max;
	string input, output;
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
		cout << i << " " << j << " " << max << endl;
	}
	return 0;
}

int maxCycleLength(int low, int high) {
	int max = calculateCycleLength(low);
	int temp;
	for(int i = low; i < high; i++) {
		temp = calculateCycleLength(i);
		if(temp > max)
			max = temp;
		}
	return max;
}

int calculateCycleLength(int num) {
	int cycleLength = 1;
	while(num != 1) {
		if(num % 2 == 0) {
			num /= 2;
			cycleLength++;
		}
		else {
			num = num + (num >> 1) + 1;
			cycleLength = cycleLength + 2;
		}
	}
	return cycleLength;
}