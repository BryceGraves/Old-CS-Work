#include "Contestants.h"


// constructors
Contestants::Contestants()      // Default constructor to set to empty
{
	howManyItems = 0;
}

// modifiers
void Contestants::insert(Player itemToAdd) // adds at the end - unordered
{
	if (howManyItems < SIZE)  // room in array
		items[howManyItems++] = itemToAdd;
}

void Contestants::removeItem(Player itemToRemove)
{
	int index = findItem(itemToRemove);
	if (findItem(itemToRemove) != -1)
		removeByIndex(index);
}

void Contestants::removeByIndex(int index)  // unordered - take end and replace
{
	if (index >= 0 && index <= howManyItems)
		items[index] = items[index + 1];
		howManyItems--;
}

// accessing
int Contestants::findItem(Player itemToFind)   // returning to index found
{
	for (int i = 0; i < howManyItems; i++)
		if (items[i] == itemToFind)
			return i;
	return -1;
}

Player Contestants::getItem(int index)
{
	if (index >= 0 && index < howManyItems)
		return items[index];
}

int Contestants::getOccurrences(Player itemToFind) // return counting number
{
	int count = 0;
	for (int index = 0; index < howManyItems; index++)
		if (items[index] == itemToFind)
			count++;
	return count;
}

const Player& Contestants::operator[] (int pos) const
{
	if (pos >= 0 && pos < howManyItems)
		return items[pos];
}

// other
void Contestants::readFile(std::string fileName, Contestants &self)
{
	std::ifstream file(fileName);
	std::string tempDataString, tempPlayerName, tempPlayerScore;
	Player tempPlayer;

	int separatorIndex = -1;
	int currentPlayerIndex = 0;

	if (file.is_open()) {
		while (getline(file, tempDataString)) // not failed or end of file
		{
			separatorIndex = tempDataString.find(",");
			tempPlayerName = tempDataString.substr(0, separatorIndex);
			tempPlayerScore = tempDataString.substr(separatorIndex + 1, tempDataString.length());

			std::cout << tempPlayerName << std::endl;
			std::cout << tempPlayerScore << std::endl;

			tempPlayer.set(tempPlayerName, std::stod(tempPlayerScore));

			self.insert(tempPlayer);
		}

		file.close();
	}
}

bool Contestants::writeFile(std::string fileName, Contestants &self)
{
  std::ofstream outputFile(fileName);
  if (outputFile.is_open())
  {
		for (int i = 0; i < howManyItems; i++) {
			outputFile << self.getItem(i).getName() << "," << self.getItem(i).toString() << std::endl;
		}

		outputFile.close();
	}
}