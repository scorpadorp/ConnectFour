#pragma once
#include "Human.h"
#include "Board.h"
#include "Game.h"
#include <string>
#include <vector>

struct Node {
	Node() {};
	Node(int Score) : score(Score) {}
	int x;
	int y;
	int score;
};

class Bot : public Human {
public:
	Bot(const std::string& name, std::string token, int value);
	~Bot();
	int rating(Game& game, Board& board);
	int getInput(Game& game, Board& board);
	void checkStatusAll(Game& game, Board& board, std::vector<int>& p_me, std::vector<int>& p_enemy, int player);
	Node minimax(Game& game, Board& board, int player, int depth);
protected:
	static int depth;
};
