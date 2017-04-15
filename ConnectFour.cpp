#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "Game.h"
#include "Board.h"
#include "GenericPlayer.h"
#include "Human.h"
#include "Bot.h"
#include "Point.h"

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	int ans;
	std::string p1, p2 = "BOT", inp = "yes";
	std::cout << "\n-----------------------------------------------------" << std::endl;
	std::cout << "\t\tWelcome to Connect 4!" << std::endl;
	std::cout << "-----------------------------------------------------\n\n";

	std::cout << "Main Menu:" << std::endl;
	std::cout << "1) Player vs Player\n";
	std::cout << "2) Player vs AI\n";
	std::cout << "3) Exit\n";
	std::cout << "\nWhat will it be, stranger?: ";
	std::cin >> ans;

	switch (ans) {
	case 1: std::cout << "\nWhat are the Player names?\n" << "Human 1: \n";
		std::cin >> p1;
		std::cout << "\nPlayer 2: \n";
		std::cin >> p2;
		break;
	case 2: std::cout << "\nGood choice! You will regret it though.\nWhat is your name?: ";
		std::cin >> p1;
		break;
	default:
		return 0;
	}

	Game game(p1, p2);
	while (inp == "yes" || inp == "y") {
		game.Play();
		std::cout << "\nDo you want to play again? (Y/N): ";
		std::cin >> inp;
	}

	return 0;
}