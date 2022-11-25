#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// Hoisted functions
// If a function is created below when it is used it must be declared at the top of the file or in a header file and imported.

int acceptUserInput(void);
int customDelete(int [], int &, int);
void populateArray(int [], int);
void printArray(int [], int);
void printDeleteOutcome(int, int);

// Main injection point of the program.
int main() {

  int result = -1, selection = -1, size = 5;
  int fakeInput[size];

  // Populate array with sample data. (Just size multiplied by 10)
  populateArray(fakeInput, size);

  printArray(fakeInput, size);

  // Get user input
  selection = acceptUserInput();

  // If something went wrong with user input such as an empty input or something that isn't a number return a failure
  // I return 1 here since it denotes a generic failure on UNIX based systems
  // Which is different from the -1 which I have used to denote an uninitialized or missing value
  if (selection == -1) return 1;

  // Attempt to delete the number that was given
  result = customDelete(fakeInput, size, selection);

  // Print if the number was deleted based on the result of the delete function
  printDeleteOutcome(result, selection);

  printArray(fakeInput, size);

  return 0;

}

int acceptUserInput() {

  int input;

  cout << "Enter a value to delete: ";

  // Check to see if the next character is a return character (Enter)
  // If it is, the user has not provided input and just hit enter
  if (cin.peek() == '\n') {
    cout << "Please input a value.\n";

    // Return failure
    return -1;

    // Checks to see if gaining user input returns failure due to invalid input.
    // Such as if the user inputs a letter it will return failure when trying to assign it to an integer
  } else if (!(cin >> input)) {
    cout << "Invalid input.\n";

    // Return failure
    return -1;
  }

  // Return valid user input
  return input;

}

int customDelete(int list[], int &size, int toRemove) {

  // Check the last index before iterating through all valuse
  // If it is found reduce the array size to "delete" the value and return success
  if (list[size - 1] == toRemove) {
    size--;
    return 0;
  }

  // Iterate through all values of the array
  for (int i = 0; i < size - 1; i++) {

    // If the value at the current index is the one we want to remove start the removal process
    if (list[i] == toRemove) {

      // Overwrite the current index value with the next index's value until the end of the array
      // We are then left with duplicate values in the last and second to last indexes of the array
      for (int j = i; j < size - 1; j++) {
        list[j] = list[j + 1];
      }

      // This behavior is the same as above since we have removed the value with the first copy, but...
      // we are now left with a duplicate garbage value at the end of the array
      // So we reduce the size to "delete" the value
      // Then return success
      size--;
      return 0;
    }
  }

  // If we make it here nothing was found and we return failure
  return 1;

}

void populateArray(int list[], int size) {

  // Iterate through the array populating it with multiples of 10
  for (int i = 0; i < size; i++) {
    list[i] = (i + 1) * 10;
  }

}

void printArray(int list[], int size) {

  cout << "Current Array:" << endl;

  // Print array representation with each associated index
  for (int i = 0; i < size; i++) {
    cout << "[" << list[i] << "] - index: " << i << endl;
  }

}

void printDeleteOutcome(int result, int selection) {

  // Based on the result print the outcome
  // Any time you print something or do something extra outside the role of the function this is called a "Side Effect"
  // These should be seperated to other functions to avoid unexpected behavior or prints
  if (result == 0) {
    cout << selection << " was deleted from array!" << endl;
  } else {
    cout << selection << " was not found, nothing was deleted!" << endl;
  }

}
