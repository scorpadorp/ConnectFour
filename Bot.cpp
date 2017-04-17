#include "stdafx.h"
#include "Bot.h"
#include <string>
#include <iostream>
#include <random>
#include <chrono>

Bot::Bot(const std::string& name, std::string token) : Human(name, token) {}
Bot::~Bot() {}
int Bot::rating(Game& game, Board& board, Point& point) {

	//check if bot can win
	board.setValue(point.x, point.y, 2);
	if (game.wonBackwardDiag(true) || game.wonForwardDiag(true) ||
		game.wonHoz(true) || game.wonVert(true)) {
		board.setValue(point.x, point.y, 0);
		return 1000;
	}
	//if not, check if can block player
	board.setValue(point.x, point.y, 1);
	if (game.wonBackwardDiag(true) || game.wonForwardDiag(true) ||
		game.wonHoz(true) || game.wonVert(true)) {
		board.setValue(point.x, point.y, 0);
		return 500;
	}
	board.setValue(point.x, point.y, 0);
	return 0;
}
int Bot::getInput(Game& game, Board& board) {
	//return (rand() % 7);

	int best_move, score, best_score = 0;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::binomial_distribution<int> dist(6, 0.4);
	do { best_move = dist(generator);
	} while (!board.isLegal(best_move, true));

	for (int move = 0; move < board.getBoardWidth(); ++move) {
		if (board.isLegal(move, true)) {
			Point now = game.pointToMove(move);
			score = rating(game, board, now);
			if (score > best_score) {
				best_score = score;
				best_move = move;
			}
		}
	}
	return best_move;
}