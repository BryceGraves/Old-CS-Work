// Decimal to Binary.cpp : Converts Decimal to Binary


#include <iostream>
using namespace std;

int main()
{
	int number;
	int *storage = (int *)malloc(sizeof(int) * 16);
	int index = 15;

	cout << "Please enter an integer from 0 - 65535: ";
	cin >> number;

	while (number > 65535 || number < 0) {
		cout << "ERROR: The number you entered is out of range.\n";
		cout << "Please enter and integer between 0 - 65535: ";
		cin >> number;
	}

	while (number > 0) {
		storage[index] = number % 2;
		number /= 2;
		index -= 1;
	}

	while (index != -1) {
		storage[index] = 0;
		index -= 1;
	}

	for (int j = 0; j < 16; ++j) {
		printf("%d", storage[j]);
	}

	return 0;
}
