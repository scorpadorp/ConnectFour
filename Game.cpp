#include "stdafx.h"
#include "Game.h"
#include <algorithm>
#include <iostream>
#include <string>

Game::Game(const std::string& p1name, bool p1human, const std::string& p2name, bool p2human) : 
	Player1(p1human ? new Human(p1name, "X") : new Bot(p1name, "X")), Player2(p2human ? new Human(p2name, "O") : new Bot(p2name, "O")) {
	playerTurn = &Player2;
}

Game::~Game() { 
	delete Player1;
	delete Player2;
}

void Game::Play() {
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int ans;
	while (!isGameOver()) {
		changePlayer();
		for (int i = 0; i < 40; ++i) {
			std::cout << "\n";
		}
		board.drawBoard(answers, Player1, Player2, hConsole);
		std::cout << std::endl << (*playerTurn)->getName() << ", it's your turn!" << "(" << (*playerTurn)->getToken() << ")" << std::endl;
		ans = (*playerTurn)->getInput(board, (*playerTurn)->getName());
		bool legalMove = board.isLegal(ans);

		while (!legalMove) {
			ans = (*playerTurn)->getInput(board, (*playerTurn)->getName());
			legalMove = board.isLegal(ans);
		}
		makeMove(ans);
	}
	board.drawBoard(answers, Player1, Player2, hConsole);
	resetGame();
}

void Game::changePlayer() {
	if ((*playerTurn)->getToken() == Player1->getToken()) {
		playerTurn = &Player2;
	}
	else {
		playerTurn = &Player1;
	}
}

bool Game::areAllElementsEqual(int arr[], const int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] != arr[0]) {
			return false;
		}
	}
	return true;
}

bool Game::wonVert() {
	for (int col = 0; col < board.getBoardWidth(); ++col) {
		for (int row = 0; row < (board.getBoardHeight() - 4 + 1); ++row) {
			int temp[4] = { board.getValue(row, col) , board.getValue(row + 1, col),
				board.getValue(row + 2, col), board.getValue(row + 3, col) };

			if (areAllElementsEqual(temp, 4) && board.getValue(row, col) != 0) {
				for (int i = row; i < (row + 4); ++i) {
					Point soln = Point(i, col);
					answers.emplace_back(soln);
				}
				return true;
			}
		}
	}
	return false;
}

bool Game::wonHoz() {
	std::vector<int> temp;
	for (int row = 0; row < 6; ++row) {
		for (int k = 0; k < 7; ++k) {
			temp.emplace_back(board.getValue(row, k));
		}

		Point info = longestRun(temp, 7);
		int length = info.x;
		int index = info.y;

		if (length >= 4 && board.getValue(row, 0 + index) != 0) {
			for (int i = 0; i < length; ++i) {
				Point soln = Point(row, 0 + index + i);
				answers.emplace_back(soln);
			}
			return true;
		}
		temp.clear();
	}
	return false;
}

bool Game::wonForwardDiag() {
	/*
	There are three different lengths of diagonals: (4,5,6).
	The forward diagonals of length 4 start at board[3][0] & board[5][3].
	Each dimension (d) after, the starting positions get closer to the
	bottom-left corner of the board, hence board[3+d][0] and board[5][3-d]
	*/
	int length1, index1;
	int length2, index2;
	std::vector<int> ans1;
	std::vector<int> ans2;

	for (int d = 0; d < 3; ++d) {
		for (int i = 0; i < (4 + d); ++i) {
			ans1.emplace_back(board.getValue(3 + d - i, 0 + i));
			ans2.emplace_back(board.getValue(5 - i, 3 - d + i));
		}

		Point part1 = longestRun(ans1, ans1.size());
		length1 = part1.x;
		index1 = part1.y;

		if (length1 >= 4 && board.getValue(3 + d - index1, 0 + index1) != 0) {
			for (int i = 0; i < length1; ++i) {
				Point soln = Point(3 + d - index1 - i, 0 + index1 + i);
				answers.emplace_back(soln);
			}
			return true;
		}

		Point part2 = longestRun(ans2, ans2.size());
		length2 = part2.x;
		index2 = part2.y;

		if (length2 >= 4 && board.getValue(5 - index2, 3 - d + index2) != 0) {
			for (int i = 0; i < length2; ++i) {
				Point soln = Point(5 - index2 - i, 3 - d + index2 + i);
				answers.emplace_back(soln);
			}
			return true;
		}

		ans1.clear();
		ans2.clear();
	}
	return false;
}

bool Game::wonBackwardDiag() {
	/*
	Same idea as the forward diagonal, but the starting positions differ
	and after each dimension the starting positions get closer to the
	top-left of the board
	*/
	int length1, index1;
	int length2, index2;
	std::vector<int> ans1;
	std::vector<int> ans2;

	for (int d = 0; d < 3; ++d) {
		for (int i = 0; i < (4 + d); ++i) {
			ans1.emplace_back(board.getValue(2 - d + i, 0 + i));
			ans2.emplace_back(board.getValue(0 + i, 3 - d + i));
		}

		Point part1 = longestRun(ans1, ans1.size());
		length1 = part1.x;
		index1 = part1.y;

		if (length1 >= 4 && board.getValue(2 - d + index1, 0 + index1) != 0) {
			for (int i = 0; i < length1; ++i) {
				Point soln = Point(2 - d + index1 + i, 0 + index1 + i);
				answers.emplace_back(soln);
			}
			return true;
		}

		Point part2 = longestRun(ans2, ans2.size());
		length2 = part2.x;
		index2 = part2.y;

		if (length2 >= 4 && board.getValue(0 + index2, 3 - d + index2) != 0) {
			for (int i = 0; i < length2; ++i) {
				Point soln = Point(0 + index2 + i, 3 - d + index2 + i);
				answers.emplace_back(soln);
			}
			return true;
		}

		ans1.clear();
		ans2.clear();
	}
	return false;
}

Point Game::longestRun(const std::vector<int>& arr, const int size) {
	std::vector<int> best;
	int idx = 0;
	int len = 1;
	int dist;
	for (int i = 0; i < size; ++i) {
		if (i > 0) {
			if (arr[i] == arr[i - 1]) {
				len += 1;
			}
			else {
				best.emplace_back(len);
				len = 1;
			}
		}
	}
	best.emplace_back(len);

	// Find max index and length
	len = *max_element(best.begin(), best.end());

	// to find max index, sum all elements prior to max element
	dist = distance(best.begin(), max_element(best.begin(), best.end()));
	for (int j = 0; j < dist; ++j) {
		idx += best[j];
	}
	Point pInfo = Point(len, idx);
	return pInfo; //remember to delete later...
}

bool Game::isGameOver() {
	wonVert();
	wonHoz();
	wonForwardDiag();
	wonBackwardDiag();
	if (!answers.empty()) {
		for (int i = 0; i < 20; ++i) {
			std::cout << "\n";
		}
		std::cout << (*playerTurn)->getName() << " has won!" << std::endl;
		return true;
	}

	if (board.isFull()) {
		for (int i = 0; i < 20; ++i) {
			std::cout << "\n";
		}
		std::cout << "Draw. No one won!" << std::endl;
		return true;
	}

	return false;
}

void Game::makeMove(int col) {
	// Simulate gravity, look at column and find bottom-most empty spot
	int row;
	for (int i = board.getBoardHeight() - 1; i >= 0; --i) {
		if (board.getValue(i, col) == 0) {
			row = i;
			break;
		}
	}

	int ans;
	if ((*playerTurn)->getToken() == Player1->getToken()) {
		ans = 1;
	}
	else {
		ans = 2;
	}
	board.setValue(row, col, ans);
}

void Game::resetGame() {
	board.Clear();
	answers.clear();
	playerTurn = &Player2;
}