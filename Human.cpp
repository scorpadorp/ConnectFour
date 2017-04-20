#include "stdafx.h"
#include "Human.h"
#include <iostream>
#include <string>

Human::Human(const std::string& name, std::string token, int value) : GenericPlayer(name, token, value) {}
Human::~Human() {}
int Human::getInput(Game& game, Board& board) {
	int choice;
	do {
		std::cout << "Enter the column you want to play (1 - 7): ";
		std::cin >> choice;
	} while (choice < 1 || choice > 7);

	// Subtract one since visual board indexing starts at 1
	return choice - 1;
}