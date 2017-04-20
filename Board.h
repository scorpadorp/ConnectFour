#pragma once
#include "GenericPlayer.h"
#include "Point.h"
#include <vector>
#include <Windows.h>

class Board {
public:
	Board();
	~Board();
	void drawBoard(std::vector<Point>& ans, GenericPlayer* p1, GenericPlayer* p2, HANDLE &h);
	bool isColored(std::vector<Point>& ans, int x, int y);
	bool isLegal(int col, bool pm = false);
	bool isFull();
	void Clear();
	int getBoardHeight() const { return boardHeight; }
	int getBoardWidth() const { return boardWidth; }
	int getValue(int x, int y) const { if (x > 0 || x < boardHeight || y > 0 || y < boardWidth) return board[x][y]; else return -1; }
	void setValue(int x, int y, int z) { board[x][y] = z; }
protected:
	const int boardHeight = 6;
	const int boardWidth = 7;
	int board[6][7] = { { 0 } };
};
