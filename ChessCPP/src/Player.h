/*
 * Player.h
 *
 *  Created on: Jun 13, 2016
 *      Author: jdobrusky
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <gtk/gtk.h>
#include "GameBoard.h"
#include "Move.h"
#include "ChessNameSpace.h"

class Player {
protected:

	Move next_move;
	int max_depth;
	nsChess::Color color;
public:
	Player();
	virtual ~Player();
	Player(nsChess::Color color,gint max_depth);
	std::vector<Move> generateMoves(GameBoard,guint8,guint8);
	std::vector<Move> generateMoves(GameBoard);
	std::vector<Move> generateMoves(GameBoard,gint8 player);
	bool isInCheck(GameBoard);
	bool isInCheckMate(GameBoard);
	virtual bool findBestMove(GameBoard);
	virtual bool performMove(GameBoard &);
	nsChess::Color getColor();
	bool updateNextMove(GameBoard game_board,guint8 x_init,guint8 y_init,guint8 x_final,guint8 y_final);
	int alphaBetaMin(int depth, Move &best_move, int alpha, int beta, GameBoard game_board,gint8 player);
	int alphaBetaMax(int depth, Move &best_move, int alpha, int beta, GameBoard game_board,gint8 player);
	int alphaBeta(int depth, Move &best_move, int alpha, int beta, GameBoard game_board,gint8 player);
	bool hasMoves(GameBoard game_board);
};

#endif /* PLAYER_H_ */
