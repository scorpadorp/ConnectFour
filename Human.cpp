//#include "stdafx.h"
#include "Human.h"
#include <iostream>
#include <string>

Human::Human(const std::string& name, std::string token, const int value) : GenericPlayer(name, token, value) {}
int Human::getInput(Game& game, Board& board) {
	int choice;
	bool valid = false;
	
	std::cin.clear();
	std::cout << "Enter the column you want to play (1 - 7): ";
	while (!valid) {
		valid = true;
		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > 7) {
			std::cin.clear();
			std::cin.ignore();
			valid = false;
		}
	}

	// Subtract one since visual board indexing starts at 1
	return choice - 1;
}