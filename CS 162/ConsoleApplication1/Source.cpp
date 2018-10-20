#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;


//Checks to see what value appears most, if two or all appear the same amount of times it returns 0.
int mode(vector<int> data) {
	sort(data.begin(), data.end());
	int mode = data[0];
	int newMode = NULL;
	int count = 0;
	int newCount = 0;
	for (int i = 1; i < data.size(); ++i) {
		if (mode != data[i]) {
			if (newMode != data[i]) {
				newMode = data[i];
				newCount = 1;
				} else {
				++newCount;
				if (newCount > count) {
					mode = data[i];
					++count;
					newCount = 0;
					}
				}
			} else {
				++count;
		}
		if (data[i] = data[data.size() - 1]) {
			if (count == newCount) {
				mode = NULL;
			}
		}
	}
	return mode;
}

int main(int argc, const char *argv[]) {
	vector<int> data = { 1, 1, 2, 2, 2, 3, 4, 4, 4, 5, 5, 5, 5};
	cout << "Mode: " << mode(data) << endl;
}
