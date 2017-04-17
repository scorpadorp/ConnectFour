#pragma once
#include "Human.h"
#include "Board.h"
#include "Game.h"
#include <string>

class Bot : public Human {
public:
	Bot(const std::string& name, std::string token);
	~Bot();
	int rating(Game& game, Board& board, Point& point);
	int getInput(Game& game, Board& board);
};
