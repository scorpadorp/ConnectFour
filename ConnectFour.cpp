#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Game.h"
#include "Board.h"
#include "GenericPlayer.h"
#include "Human.h"
#include "Bot.h"
#include "Point.h"
using std::cin;
using std::cout;

int getValidInput(int low, int high);

int main() //catch all exceptions thrown
{
	int ans; int diff_b1, diff_b2;
	bool p1human = true, p2human = true;
	std::string p1, p2, inp = "yes";
	cout << "\n-----------------------------------------------------" << std::endl;
	cout << "\t\tWelcome to Connect 4!" << std::endl;
	cout << "-----------------------------------------------------";

	while (true) {
		cout << "\n\nMain Menu:" << std::endl;
		cout << "1) Player vs Player\n";
		cout << "2) Player vs AI\n";
		cout << "3) AI vs AI\n";
		cout << "4) Exit\n";
		cout << "\nWhat will it be, stranger?: ";
		cin >> ans;

		switch (ans) {
		case 1: std::cout << "\nWhat are the Player names?\n" << "Player 1: \n";
			cin >> p1;
			cout << "\nPlayer 2: \n";
			cin >> p2;
			break;
		case 2: std::cout << "\nGood choice! You will regret it though.\nWhat is your name?: ";
			cin >> p1;
			cout << "\nChoose your difficulty:\n";
			cout << "1) Beginner\n" << "2) Easy\n" << "3) Medium\n";
			diff_b2 = getValidInput(1, 3);
			p2 = "BOT";
			p2human = false;
			break;
		case 3: cout << "\nSit back and watch!";
			p1 = "BOT 1";
			p2 = "BOT 2";
			cout << "\nChoose your difficulty for both:\n";
			cout << "1) Beginner\n" << "2) Easy\n" << "3) Medium\n";
			cout << "\nFirst Bot: ";
			diff_b1 = getValidInput(1, 3);
			cout << "\nSecond Bot: ";
			diff_b2 = getValidInput(1, 3);
			p1human = p2human = false;
			break;
		default:
			return 0;
		}

		cin.clear();
		cin.ignore(10000, '\n');
		{
			Game game(p1, p1human, p2, p2human, diff_b1*2, diff_b2*2);
			while (inp == "yes" || inp == "y") {
				game.Play();
				cout << "\nDo you want to play again? (Y/N): ";
				cin >> inp;
			}
		}
		inp = "yes";
		p1human = p2human = true;
	}
	return 0;
}

int getValidInput(int low, int high) {
	int choice;
	bool valid = false;

	while (!valid) {
		valid = true;
		std::cin >> choice;
		if (std::cin.fail() || choice < low || choice > high) {
			std::cin.clear();
			std::cin.ignore();
			valid = false;
		}
	}

	return choice;
}
