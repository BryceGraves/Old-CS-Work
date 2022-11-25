#include "Player.h"


// Player class definition file
// default constructor
Player::Player()
{
	set("unnamed", 0);
}

// Player constructor function definition
Player::Player(std::string n, double s)
{
	set(n,s);
}

// Player member function definitions
void Player::set(std::string n, double s)
{
	
	name = n;
	score = s;

}

std::string Player::getName() const          // get - accessor member functions
{
	return name;
}
double Player::getScore() const
{
	return score;
}

std::string Player::toString() const
{
	std::string scoreStr;
	scoreStr = std::to_string(score);
	return scoreStr;
}

std::string Player::toFileString() const
{
	std::ifstream inFile;					// read from file
	std::string line, tmp;
	std::string fileStr;

	inFile.open("players.csv");

	if (!inFile)
	{
		std::cout << "Error opening file";
	}

	if (std::getline(inFile, line))
	{

		tmp = line;

	}

	fileStr = tmp;
	return fileStr;
}

// Relational operator overloaded functions

bool operator==(const Player& p1, const Player& p2)
{
	if (p1.score == p2.score)
		return true;
	return false;
}
bool operator!=(const Player& p1, const Player& p2)
{
	return(!(p1 == p2));
}
bool operator>=(const Player& p1, const Player& p2)
{
	return (p1 > p2 || p1 == p2);
}
bool operator<=(const Player& p1, const Player& p2)
{
	return(!(p1 > p2));
}
bool operator>(const Player& p1, const Player& p2)
{
	if (p1.score > p2.score)
		return true;
	else
		return false;
}
bool operator<(const Player& p1, const Player& p2)
{
	return(!(p1 >= p2));
}

// insertion operator overload <<
std::ostream& operator<<(std::ostream& os, const Player& p)
{
	os << p.toString();

	return os;
}


// extraction operator overload >>
std::istream& operator>>(std::istream& is, Player& p)
{
	std::string tmp;				//local variable
	
	std::cout << "\nEnter player name: ";
	is >> tmp;

	p.name = tmp;
	p.score = 0;


	return is;
}

std::ofstream& operator<<(std::ofstream& of, const Player& p)
{
	of << p.toFileString();

	return of;
}

std::ifstream& operator>>(std::ifstream& in, Player& p)
{
	std::ifstream inFile;					// read from file

	std::string line;
	std::string tmp;

	int tmpint;

	inFile.open("players.csv");

	in >> tmp;
	tmpint = tmp.find(',');

	p.name = tmp.substr(0, tmpint);
	p.score = std::stod(tmp.substr(tmpint + 1, tmp.length()));

	inFile.close();

	return in;
}


// ----- ignore ----

/*

if (!inFile)
{
	std::cout << "Error opening file";
}

if (std::getline(inFile, line))
{
	tmpint = line.find(',');

	in >> tmp;

	p.name = line.substr(0, tmpint);

	in >> tmp;

	p.score = std::stod(line.substr(tmpint, line.length()));
}

std::ifstream& operator>>(std::ifstream& in, Player& p)
{
	std::ifstream inFile;					// read from file

	std::string line;
	std::string tmp;

	int tmpint;

	inFile.open("players.csv");

	in >> tmp;
	tmpint = tmp.find(',');

	std::cout << tmp;

	p.name = tmp.substr(0, tmpint);
	p.score = std::stod(tmp.substr(tmpint, tmp.length()));

	return in;
}



std::ifstream& operator>>(std::ifstream& in, Player& p)
{
	std::ifstream inFile;					// read from file

	std::string line;
	std::string tmp;

	int tmpint;

	inFile.open("players.csv");

	in >> tmp;
	tmpint = tmp.find(',');

	std::cout << "TESTING";

	p.name = tmp.substr(0, tmpint);
	p.score = std::stod(tmp.substr(tmpint, tmp.length()));

	inFile.close();

	return in;
}
*/