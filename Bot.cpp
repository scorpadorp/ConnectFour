#include "stdafx.h"
#include "Bot.h"
#include <string>
#include <iostream>
#include <random>
#include <math.h>

Bot::Bot(const std::string& name, std::string token, int value) : Human(name, token, value) {}
Bot::~Bot() {}
void Bot::checkStatusAll(Game& game, Board& board, std::vector<int>& p_me, std::vector<int>& p_enemy, int player) {
	std::vector<int> vert = game.wonVert(true, player);
	std::vector<int> hoz = game.wonHoz(true, player);
	std::vector<int> fdiag = game.wonForwardDiag(true, player);
	std::vector<int> bdiag = game.wonBackwardDiag(true, player);

	for (int i = 0; i < p_me.size(); ++i) {
		if (player == 1) {
			p_me.at(i) = vert.at(i) + hoz.at(i) + fdiag.at(i) + bdiag.at(i);
			p_enemy.at(i) = vert.at(i + 3) + hoz.at(i + 3) + fdiag.at(i + 3) + bdiag.at(i + 3);
		}
		else {
			p_me.at(i) = vert.at(i + 3) + hoz.at(i + 3) + fdiag.at(i + 3) + bdiag.at(i + 3);
			p_enemy.at(i) = vert.at(i) + hoz.at(i) + fdiag.at(i) + bdiag.at(i);
		}
	}
}
int Bot::rating(Game& game, Board& board) {
	// this only considers the CURRENT board state and evaluates the score, it DOES NOT lookahead
	int p_me = 0, p_enemy = 0, score = 0;
	p_me = ((*game.getPlayerTurn())->getValue());
	(p_me == 2) ? p_enemy = 1 : p_enemy = 2;
	std::vector<int> num_of_234_p_me(3, 0);
	std::vector<int> num_of_234_p_enemy(3, 0);

	//for now, only check if player has won
	checkStatusAll(game, board, num_of_234_p_me, num_of_234_p_enemy, p_me);
	if (num_of_234_p_me.at(2)) {
		return 1000;
	}
	/*
	//check chains of 2 and 3 for both players
	for (int i = 0; i < num_of_234_p_me.size() - 1; ++i) {
		score += (num_of_234_p_me.at(i) * pow(i + 1, 2)); //# of each chain * weight
		score -= (num_of_234_p_enemy.at(i) * pow(i + 1, 2)); //make it value lower positions (towards floor)
	}
	*/
	return score;
}
int Bot::getInput(Game& game, Board& board) {
	int depth = 4;
	Node bestMove = minimax(game, board, (*game.getPlayerTurn())->getValue(), depth);
	return bestMove.y; 
}
Node Bot::minimax(Game& game, Board& board, int player, int depth) {
	int enemy = 0;
	(player == 1) ? enemy = 2 : enemy = 1;
	game.wonVert(true, player);
	game.wonHoz(true, player);
	game.wonForwardDiag(true, player);
	game.wonBackwardDiag(true, player);

	//base case (getPlayerTurn does not change in this recursive process)
	int rate = rating(game, board);
	if (depth == 0 || rate >= 1000) {
		if ((*game.getPlayerTurn())->getValue() == player) {
			std::cout << "1000\n";
			system("pause");
			return Node(1000 - depth);
		}
		else {
			std::cout << "-1000\n";
			system("pause");
			return Node(depth - 1000);
		}
	}
	if (board.isFull()) { //why does program crash if I remove this part?
		std::cout << "full!\n";
		system("pause");
		return Node(0);
	}

	std::vector<Node> moves;

	for (int i = 0; i < board.getBoardWidth(); ++i) {
		if (board.isLegal(i, true)) {
			Point point(game.pointToMove(i));
			Node node;
			node.x = point.x;
			node.y = point.y;
			board.setValue(node.x, node.y, player);
			++depth;
			node.score = minimax(game, board, enemy, depth - 1).score;
			moves.emplace_back(node);
			board.setValue(node.x, node.y, 0);
		}
	}

	int bestMove = 0;
	if ((*game.getPlayerTurn())->getValue() == player) {
		int bestScore = -100000;
		for (int i = 0; i < moves.size(); ++i) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else { //enemy
		int bestScore = 100000;
		for (int i = 0; i < moves.size(); ++i) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}
