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
	GenericPlayer** getPlayerTurn() { return playerTurn; }
	bool areAllElementsEqual(int arr[], const int size);
	bool wonVert(bool pm = false);
	bool wonHoz(bool pm = false);
	bool wonForwardDiag(bool pm = false);
	bool wonBackwardDiag(bool pm = false);
	bool isGameOver();
	void makeMove(Point& point);
	Point pointToMove(int col);
	Point longestRun(const std::vector<int>& arr, const int size);
protected:
	Board board;
	GenericPlayer* Player1;
	GenericPlayer* Player2;
	GenericPlayer** playerTurn;
	std::vector<Point> answers;
	std::vector<Point> moves;
	int p1Wins = 0;
	int p2Wins = 0;
	int draws = 0;
};
