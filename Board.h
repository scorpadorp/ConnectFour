#pragma once
#include "GenericPlayer.h"
#include "Point.h"
#include <vector>
#include <Windows.h>

class Board {
public:
	Board();
	~Board();
	void drawBoard(std::vector<Point>& ans, GenericPlayer& p1, GenericPlayer& p2, HANDLE &h);
	bool isColored(std::vector<Point>& ans, int x, int y);
	bool isLegal(int col);
	bool isFull();
	void Clear();
	int getBoardHeight() { return boardHeight; }
	int getBoardWidth() { return boardWidth; }
	int getValue(int x, int y) { return board[x][y]; }
	void setValue(int x, int y, int z) { board[x][y] = z; }
protected:
	const int boardHeight = 6;
	const int boardWidth = 7;
	int board[6][7] = { { 0 } };
};
