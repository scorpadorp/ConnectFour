#pragma once
#include "Board.h"
#include "Human.h"
#include "Bot.h"
#include "GenericPlayer.h"
#include "Point.h"

class Game {
public:
	Game(const std::string& p1name, bool p1human, const std::string& p2name, bool p2human, double diff1, double diff2);
	void Play();
	void changePlayer();
	void resetGame();
	void makeMove(Point& point);
	bool isGameOver();
	std::vector<int> wonVert(bool pm = false, int player = 0);
	std::vector<int> wonHoz(bool pm = false, int player = 0);
	std::vector<int> wonForwardDiag(bool pm = false, int player = 0);
	std::vector<int> wonBackwardDiag(bool pm = false, int player = 0);
	Point pointToMove(const int col);
	Point longestRun(const std::vector<int>& arr, const int size, int player = 0);
	std::unique_ptr<GenericPlayer>* getPlayerTurn() { return playerTurn; }
private:
	Board board;
	std::unique_ptr<GenericPlayer> Player1;
	std::unique_ptr<GenericPlayer> Player2;
	std::unique_ptr<GenericPlayer>* playerTurn;
	std::vector<Point> answers;
	int p1Wins = 0;
	int p2Wins = 0;
	int draws = 0;
};
