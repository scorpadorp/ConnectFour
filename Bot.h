#pragma once
#include "Human.h"
#include "Board.h"
#include "Game.h"
#include <string>
#include <vector>

struct Node {
	Node() {};
	Node(double Score) : score(Score) {}
	int x;
	int y;
	double score;
};

class Bot : public Human {
public:
	Bot(const std::string& name, std::string token, const int value, double mode);
	double rating(Game& game, Board& board, int player);
	int getInput(Game& game, Board& board) override;
	void checkStatusAll(Game& game, Board& board, std::vector<double>& p_me, std::vector<double>& p_enemy, int player, int enemy);
	Node minimax(Game& game, Board& board, int player, double depth);
private:
	double depth;
	double weights[4] = { 1, 5, 15, 1000 };
};
