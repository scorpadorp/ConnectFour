#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <string>

Board::Board() {}
Board::~Board() {}

void Board::drawBoard(std::vector<Point>& ans, GenericPlayer& p1, GenericPlayer& p2, HANDLE &h) {
	std::cout << "\n 1 2 3 4 5 6 7" << std::endl;
	for (int x = 0; x < boardHeight; ++x) {
		for (int y = 0; y < boardWidth; ++y) {
			if (board[x][y] == 0) {
				std::cout << "| ";
			}
			else if (board[x][y] == 1) {
				if (isColored(ans, x, y)) {
					std::cout << "|";
					SetConsoleTextAttribute(h, 4);
					std::cout << p1.getToken();
					SetConsoleTextAttribute(h, 15);
				}
				else {
					std::cout << "|" << p1.getToken();
				}
			}
			else if (board[x][y] == 2) {
				if (isColored(ans, x, y)) {
					std::cout << "|";
					SetConsoleTextAttribute(h, 14);
					std::cout << p2.getToken();
					SetConsoleTextAttribute(h, 15);
				}
				else {
					std::cout << "|" << p2.getToken();
				}
			}
		}
		std::cout << "|\n";
	}
}

bool Board::isColored(std::vector<Point>& ans, int x, int y) {
	std::vector<Point>::const_iterator iter;
	for (iter = ans.begin(); iter < ans.end(); ++iter) {
		if (x == (*iter)._x && y == (*iter)._y) {
			return true;
		}
	}
	return false;
}

bool Board::isLegal(int col) {
	if (board[0][col] != 0) {
		std::cout << "Column is full! ";
		return false;
	}
	return true;
}

bool Board::isFull() {
	for (int x = 0; x < boardHeight; ++x) {
		for (int y = 0; y < boardWidth; ++y) {
			if (board[x][y] == 0) {
				return false;
			}
		}
	}
	return true;
}

void Board::Clear() {
	for (int x = 0; x < boardHeight; ++x) {
		for (int y = 0; y < boardWidth; ++y) {
			board[x][y] = 0;
		}
	}
}