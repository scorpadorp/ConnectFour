#pragma once
#include <string>

class Game;
class Board;
class GenericPlayer {
public:
	GenericPlayer(const std::string& name, std::string token, const int value);
	virtual ~GenericPlayer() = default;
	virtual int getInput(Game& game, Board& board) = 0;
	std::string getName() const { return pName; }
	std::string getToken() const { return pToken; }
	int getValue() const { return value; }
private:
	const std::string pName;
	const std::string pToken;
	const int value;
};
