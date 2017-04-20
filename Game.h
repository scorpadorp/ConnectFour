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
	void makeMove(Point& point);
	bool isGameOver();
	std::vector<int> wonVert(bool pm = false, int player = 0);
	std::vector<int> wonHoz(bool pm = false, int player = 0);
	std::vector<int> wonForwardDiag(bool pm = false, int player = 0);
	std::vector<int> wonBackwardDiag(bool pm = false, int player = 0);
	Point pointToMove(int col);
	Point longestRun(const std::vector<int>& arr, const int size, int token = -2);
	GenericPlayer** getPlayerTurn() { return playerTurn; }
protected:
	Board board;
	GenericPlayer* Player1;
	GenericPlayer* Player2;
	GenericPlayer** playerTurn;
	std::vector<Point> answers;
	short unsigned p1Wins = 0;
	short unsigned p2Wins = 0;
	short unsigned draws = 0;
};
