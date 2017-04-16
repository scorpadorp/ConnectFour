#pragma once
#include "Human.h"
#include "Board.h"
#include <string>

class Bot : public Human {
public:
	Bot(const std::string& name, std::string token);
	~Bot();
	int getInput(Board& board, std::string& playerName);
};
