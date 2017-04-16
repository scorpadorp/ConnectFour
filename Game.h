#pragma once
#include "Board.h"
#include "Human.h"
#include "Bot.h"
#include "GenericPlayer.h"
#include "Point.h"
#include <Windows.h>

class Game {
public:
	Game(const std::string& p1name, bool p1human, const std::string& p2name, bool p2human);
	~Game();
	void Play();
	void changePlayer();
	void resetGame();
	bool areAllElementsEqual(int arr[], const int size);
	bool wonVert();
	bool wonHoz();
	bool wonForwardDiag();
	bool wonBackwardDiag();
	bool isGameOver();
	void makeMove(int col);
	Point longestRun(const std::vector<int>& arr, const int size);
protected:
	Board board;
	GenericPlayer* Player1;
	GenericPlayer* Player2;
	GenericPlayer** playerTurn;
	std::vector<Point> answers;
};
