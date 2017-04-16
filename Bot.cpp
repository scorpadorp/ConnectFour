#include "stdafx.h"
#include "Bot.h"
#include <string>

Bot::Bot(const std::string& name, std::string& token) : Human(name, token) {}
Bot::~Bot() {}
int Bot::getInput(Board& board, std::string& playerName) {
	return (rand() % 6);
}