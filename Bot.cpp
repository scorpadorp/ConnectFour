#include "Bot.h"
#include <string>
#include <iostream>
#include <random>
#include <math.h>

Bot::Bot(const std::string& name, std::string token, const int value, double mode) : Human(name, token, value), depth(mode) {}
void Bot::checkStatusAll(Game& game, Board& board, std::vector<double>& p_me, std::vector<double>& p_enemy, int player, int enemy) {
	std::vector<int> vert_me = game.wonVert(true, player);
	std::vector<int> hoz_me = game.wonHoz(true, player);
	std::vector<int> fdiag_me = game.wonForwardDiag(true, player);
	std::vector<int> bdiag_me = game.wonBackwardDiag(true, player);
	std::vector<int> vert_enemy = game.wonVert(true, enemy);
	std::vector<int> hoz_enemy = game.wonHoz(true, enemy);
	std::vector<int> fdiag_enemy = game.wonForwardDiag(true, enemy);
	std::vector<int> bdiag_enemy = game.wonBackwardDiag(true, enemy);

	for (int i = 0; i < p_me.size(); ++i) {
		p_me.at(i) = vert_me.at(i)*1.0 + hoz_me.at(i)*1.14 + fdiag_me.at(i)*1.0 + bdiag_me.at(i)*1.0;
		p_enemy.at(i) = vert_enemy.at(i)*1.0 + hoz_enemy.at(i)*1.1 + fdiag_enemy.at(i)*1.0 + bdiag_enemy.at(i)*1.0;
	}
}
double Bot::rating(Game& game, Board& board, int player) {
	// this only considers the CURRENT board state and evaluates the score
	double score = 0;
	int enemy = 0, maximize;
	((*game.getPlayerTurn())->getValue() == player) ? maximize = 1 : maximize = -1;
	(player == 1) ? enemy = 2 : enemy = 1;
	std::vector<double> num_of_234_p_me(4, 0);
	std::vector<double> num_of_234_p_enemy(4, 0);

	if ((*game.getPlayerTurn())->getValue() == player)
		checkStatusAll(game, board, num_of_234_p_me, num_of_234_p_enemy, player, enemy);
	else
		checkStatusAll(game, board, num_of_234_p_enemy, num_of_234_p_me, enemy, player);

	//check the lengths of chain (2, 3, 4)
	for (int i = 1; i < num_of_234_p_me.size(); ++i) {
		score += (num_of_234_p_me.at(i) * weights[i]);
		score -= (num_of_234_p_enemy.at(i) * weights[i]);
	}

	//count and then add singles
	int me_count[7] = { 0 }, enemy_count[7] = { 0 };
	for (int x = 0; x < board.getBoardHeight(); ++x) {
		for (int y = 0; y < board.getBoardWidth(); ++y) {
			if (board.getValue(x, y) == player)
				++me_count[y];
			else if (board.getValue(x, y) == enemy)
				++enemy_count[y];
		}
	}
	for (int i = 0; i < board.getBoardWidth(); ++i) {
		score += (me_count[i]);
		score -= (enemy_count[i]);
	}

	return score*maximize;
}
int Bot::getInput(Game& game, Board& board) {
	//initial case (play best move if available)
	if (board.getValue(5, 3) == 0)
		return 3;
	else {
		Node bestMove = minimax(game, board, (*game.getPlayerTurn())->getValue(), depth);
		return bestMove.y;
	}
}
Node Bot::minimax(Game& game, Board& board, int player, double depth) {
	int enemy = 0;
	(player == 1) ? enemy = 2 : enemy = 1;

	double score = rating(game, board, player);
	if (depth == 0 || score >= 750)
		return Node(score - depth);
	else if (depth == 0 || score <= -750)
		return Node(score + depth);
	if (board.isFull())
		return Node(0);

	std::vector<Node> moves;
	for (int i = 0; i < board.getBoardWidth(); ++i) {
		if (board.isLegal(i, true)) {
			Point point(game.pointToMove(i));
			Node node;
			node.x = point.x;
			node.y = point.y;
			board.setValue(node.x, node.y, player);
			node.score = minimax(game, board, enemy, depth - 1).score;
			moves.emplace_back(node);
			board.setValue(node.x, node.y, 0);
		}
	}

	int bestMove = 0;
	if ((*game.getPlayerTurn())->getValue() == player) {
		double bestScore = -100000;
		for (int i = 0; i < moves.size(); ++i) {
			if (moves[i].score > bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}
	else { //enemy
		double bestScore = 100000;
		for (int i = 0; i < moves.size(); ++i) {
			if (moves[i].score < bestScore) {
				bestMove = i;
				bestScore = moves[i].score;
			}
		}
	}

	return moves[bestMove];
}
