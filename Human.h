#pragma once
#include "GenericPlayer.h"
#include "Board.h"
#include <string>

class Human : public GenericPlayer {
public:
	Human(const std::string& name, std::string token);
	~Human();
	int getInput(Board& board, std::string& playerName);
};
