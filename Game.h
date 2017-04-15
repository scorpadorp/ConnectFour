#pragma once
#include "Board.h"
#include "Human.h"
#include "Bot.h"
#include "GenericPlayer.h"
#include "Point.h"
#include <Windows.h>

class Game {
public:
	Game(const std::string p1, const std::string p2);
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
	Human Player1; // guaranteed human
	Human Player2; // I want to make it a GenericPlayer pointer so it can point to a human or AI
	GenericPlayer* playerTurn; // points to the current player (human or AI)
	std::vector<Point> answers;
};
