#include <iostream>
#include <string>
#include <fstream>

#include "Player.h"

#ifndef CONTESTANTS_H	// if it is NOT defined (T/F)
#define CONTESTANTS_H	// define it

#define SIZE 3

class Contestants         // unordered data structure - .h file
{
public:
	// constructors
	Contestants();      // Default constructor to set to empty 

	// modifiers
	void insert(Player itemToAdd);
	void removeItem(Player itemToRemove);
	void removeByIndex(int index);


	// accessing
	int findItem(Player itemToFind);   // returning to index found
	Player getItem(int index);
	int getOccurrences(Player itemToFind); // return counting number
	int getHowMany() const { return howManyItems; }

	const Player& operator[] (int pos) const;

	// other
	void readFile(std::string fileName, Contestants &self);
	bool writeFile(std::string fileName, Contestants &self);


private:      // contestants "has a" data member
	Player items[SIZE];
	int howManyItems;
};

#endif