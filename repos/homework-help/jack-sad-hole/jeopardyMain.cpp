#include <string>
#include <iostream>
#include "Player.h"
#include "Contestants.h"

int main() {
	Contestants contestants;
	Player player;

	std::string inputFile ("player.txt");
	std::string outputFile ("players_output.txt");

	contestants.readFile(inputFile, contestants);

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << "Name: " << contestants.getItem(i).getName() << ", Score: " << contestants.getItem(i).toString() << std::endl;
	}

	for (int i = 0; i < SIZE; i++)
	{
		contestants.removeByIndex(0);
	}

	std::cin >> player;
	contestants.insert(player);

	std::cin >> player;
	contestants.insert(player);

	std::cin >> player;
	contestants.insert(player);

	for (int i = 0; i < SIZE; i++)
	{
		std::cout << "Name: " << contestants.getItem(i).getName() << ", Score: " << contestants.getItem(i).toString() << std::endl;
	}

	return contestants.writeFile(outputFile, contestants);
}