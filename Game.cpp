#include "Game.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>

Game::Game(const std::string& p1name, bool p1human, const std::string& p2name, bool p2human, double diff1, double diff2) :
	Player1(p1human ? std::make_unique<Human>(p1name, "X", 1) : std::make_unique<Bot>(p1name, "X", 1, diff1)),
	Player2(p2human ? std::make_unique<Human>(p2name, "O", 2) : std::make_unique<Bot>(p2name, "O", 2, diff2)) {
	playerTurn = &Player2;
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
		ans = (*playerTurn)->getInput(*this, board);
		bool legalMove = board.isLegal(ans);

		while (!legalMove) {
			ans = (*playerTurn)->getInput(*this, board);
			legalMove = board.isLegal(ans);
		}
		Point move = pointToMove(ans);
		makeMove(move);
	}

	board.drawBoard(answers, Player1, Player2, hConsole);
	std::cout << std::endl << Player1->getName() << " wins: " << p1Wins << std::endl;
	std::cout << Player2->getName() << " wins: " << p2Wins << std::endl;
	std::cout << "Draws: " << draws << std::endl;
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

std::vector<int> Game::wonVert(bool pm, int player) {
	std::vector<int> num_of_234(4, 0);
	std::vector<int> temp;
	for (int row = 0; row < board.getBoardWidth(); ++row) {
		for (int col = 0; col < board.getBoardHeight(); ++col) {
			temp.emplace_back(board.getValue(col, row));
		}

		Point info = longestRun(temp, board.getBoardHeight(), player);
		int length = info.x;
		int index = info.y;

		for (int len = 2; len < 4; ++len) { //check for lengths of 2 and 3
			if (length == len)
				++num_of_234.at(len - 1);
		}

		if (length >= 4) {
			for (int i = 0; i < length; ++i) {
				if (!pm && length >= 4) {
					Point soln = Point(index + i, row);
					answers.emplace_back(soln);
				}
			}
			++num_of_234.at(3);
		}
		temp.clear();
	}
	return num_of_234;
}

std::vector<int> Game::wonHoz(bool pm, int player) {
	std::vector<int> num_of_1234(4, 0);
	std::vector<int> temp;
	for (int row = 0; row < board.getBoardHeight(); ++row) {
		for (int k = 0; k < board.getBoardWidth(); ++k) {
			temp.emplace_back(board.getValue(row, k));
		}

		Point info = longestRun(temp, board.getBoardWidth(), player);
		int length = info.x;
		int index = info.y;

		for (int len = 2; len < 4; ++len) { //check for lengths of 2 and 3
			if (length == len)
				++num_of_1234.at(len - 1);
		}

		if (length >= 4) {
			for (int i = 0; i < length; ++i) {
				if (!pm) {
					Point soln = Point(row, 0 + index + i);
					answers.emplace_back(soln);
				}
			}
			++num_of_1234.at(3);
		}
		temp.clear();
	}
	return num_of_1234;
}

std::vector<int> Game::wonForwardDiag(bool pm, int player) {
	/*
	There are three different lengths of diagonals: (4,5,6).
	The forward diagonals of length 4 start at board[3][0] & board[5][3].
	Each dimension (d) after, the starting positions get closer to the
	bottom-left corner of the board, hence board[3+d][0] and board[5][3-d]
	*/
	std::vector<int> num_of_234(4, 0);
	int length1, index1;
	int length2, index2;
	std::vector<int> ans1;
	std::vector<int> ans2;

	for (int d = 0; d < 3; ++d) {
		for (int i = 0; i < (4 + d); ++i) {
			ans1.emplace_back(board.getValue(3 + d - i, 0 + i));
			ans2.emplace_back(board.getValue(5 - i, 3 - d + i));
		}

		Point part1 = longestRun(ans1, ans1.size(), player);
		length1 = part1.x;
		index1 = part1.y;

		for (int len = 2; len < 4; ++len) { //check for lengths of 2 and 3
			if (length1 == len)
				++num_of_234.at(len - 1);
		}

		if (length1 >= 4) {
			for (int i = 0; i < length1; ++i) {
				if (!pm) {
					Point soln = Point(3 + d - index1 - i, 0 + index1 + i);
					answers.emplace_back(soln);
				}
			}
			++num_of_234.at(3);
		}

		Point part2 = longestRun(ans2, ans2.size(), player);
		length2 = part2.x;
		index2 = part2.y;

		for (int len = 2; len < 4; ++len) { //check for lengths of 2 and 3
			if (length2 == len)
				++num_of_234.at(len - 1);
		}

		if (length2 >= 4) {
			for (int i = 0; i < length2; ++i) {
				if (!pm) {
					Point soln = Point(5 - index2 - i, 3 - d + index2 + i);
					answers.emplace_back(soln);
				}
			}
			++num_of_234.at(3);
		}

		ans1.clear();
		ans2.clear();
	}
	return num_of_234;
}

std::vector<int> Game::wonBackwardDiag(bool pm, int player) {
	/*
	Same idea as the forward diagonal, but the starting positions differ
	and after each dimension the starting positions get closer to the
	top-left of the board
	*/
	std::vector<int> num_of_234(4, 0);
	int length1, index1;
	int length2, index2;
	std::vector<int> ans1;
	std::vector<int> ans2;

	for (int d = 0; d < 3; ++d) {
		for (int i = 0; i < (4 + d); ++i) {
			ans1.emplace_back(board.getValue(2 - d + i, 0 + i));
			ans2.emplace_back(board.getValue(0 + i, 3 - d + i));
		}

		Point part1 = longestRun(ans1, ans1.size(), player);
		length1 = part1.x;
		index1 = part1.y;

		for (int len = 2; len < 4; ++len) { //check for lengths of 2 and 3
			if (length1 == len)
				++num_of_234.at(len - 1);
		}

		if (length1 >= 4) {
			for (int i = 0; i < length1; ++i) {
				if (!pm) {
					Point soln = Point(2 - d + index1 + i, 0 + index1 + i);
					answers.emplace_back(soln);
				}
			}
			++num_of_234.at(3);
		}

		Point part2 = longestRun(ans2, ans2.size(), player);
		length2 = part2.x;
		index2 = part2.y;

		for (int len = 2; len < 4; ++len) { //check for lengths of 2 and 3
			if (length2 == len)
				++num_of_234.at(len - 1);
		}

		if (length2 >= 4) {
			for (int i = 0; i < length2; ++i) {
				if (!pm) {
					Point soln = Point(0 + index2 + i, 3 - d + index2 + i);
					answers.emplace_back(soln);
				}
			}
			++num_of_234.at(3);
		}

		ans1.clear();
		ans2.clear();
	}
	return num_of_234;
}

Point Game::longestRun(const std::vector<int>& arr, const int size, int player) {
	std::vector<int> best;
	int idx = 0, len = 1, dist;

	// check missing case (all 0's)
	if (std::equal(arr.begin() + 1, arr.end(), arr.begin()) && arr[0] == 0) {
		Point pInfo = Point(0, 0);
		return pInfo;
	}

	for (int i = 0; i < size; ++i) {
		if (i > 0) {
			if (!player) {
				if (arr[i] == arr[i - 1] && arr[i] != 0) {
					len += 1;
				}
				else {
					best.emplace_back(len);
					len = 1;
				}
			}
			else {
				if (arr[i] == arr[i - 1] && arr[i] == player) {
					len += 1;
				}
				else {
					best.emplace_back(len);
					len = 1;
				}
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
	return pInfo;
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
		((*playerTurn)->getName() == Player1->getName()) ? p1Wins++ : p2Wins++;
		return true;
	}

	if (board.isFull()) {
		for (int i = 0; i < 20; ++i) {
			std::cout << "\n";
		}
		std::cout << "Draw. No one won!" << std::endl;
		draws++;
		return true;
	}

	return false;
}

Point Game::pointToMove(const int col) {
	// Simulate gravity, look at column and find bottom-most empty spot
	int row;
	for (int i = board.getBoardHeight() - 1; i >= 0; --i) {
		if (board.getValue(i, col) == 0) {
			row = i;
			break;
		}
	}
	return Point(row, col);
}

void Game::makeMove(Point& point) {
	board.setValue(point.x, point.y, (*playerTurn)->getValue());
}

void Game::resetGame() {
	board.Clear();
	answers.clear();
	playerTurn = &Player2;
}
