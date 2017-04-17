#pragma once
#include <string>

class Game;
class Board;
class GenericPlayer {
public:
	GenericPlayer(const std::string& name, std::string token);
	virtual ~GenericPlayer();
	virtual int getInput(Game& game, Board& board) = 0;
	std::string getName() { return pName; }
	std::string getToken() { return pToken; }
protected:
	std::string pName;
	std::string pToken;
};
