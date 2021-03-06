#pragma once
#include "GenericPlayer.h"
#include "Board.h"
#include <string>

class Human : public GenericPlayer {
public:
	Human(const std::string& name, std::string token, const int value);
	int getInput(Game& game, Board& board);
};
