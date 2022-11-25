/*
program comments:
Jack Craggs, Player class declaration
*/

#ifndef PLAYER_H	// if it is NOT defined (T/F)
#define PLAYER_H	// define it

#include <iostream>
#include <string>
#include <fstream>
#include <istream>

// declarations - class declarations

class Player
{

public:								// functionality - member functions
	Player();                       // default constructor
	Player(std::string, double);    // constructors - initialize data members
	void set(std::string, double);	// set - modifier member function
	std::string getName() const;	// get - accessor member functions
	double getScore() const;

	void print();					// other member functions
	std::string toString() const;
	std::string toFileString() const;


	friend bool operator==(const Player& p1, const Player& p2);
	friend bool operator!=(const Player& p1, const Player& p2);
	friend bool operator>=(const Player& p1, const Player& p2);
	friend bool operator<=(const Player& p1, const Player& p2);
	friend bool operator>(const Player& p1, const Player& p2);
	friend bool operator<(const Player& p1, const Player& p2);

	friend std::ostream& operator<<(std::ostream& os, const Player& p);
	friend std::istream& operator>>(std::istream& is, Player& p);

	friend std::ofstream& operator<<(std::ofstream& of, const Player& p);
	friend std::ifstream& operator>>(std::ifstream& in, Player& p);


private:							// data members
	std::string name;				// Player "has a" name
	double score;					// Player "has a" score
};

#endif