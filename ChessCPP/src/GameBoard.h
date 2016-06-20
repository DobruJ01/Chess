/*
 * GameBoard.h
 *
 *  Created on: Jun 12, 2016
 *      Author: jdobrusky
 */

#ifndef GAMEBOARD_H_
#define GAMEBOARD_H_

#include "ChessNameSpace.h"
#include <gtk/gtk.h>
#include "Move.h"
#include <vector>

class GameBoard {
	public:
    static const gint8		   BOARDSIZE = 8;
private:
	typedef  void (GameBoard::*MemFnc)(std::vector<Move*> *move_list, guint8 x_init, guint8 y_init);
	enum {EMPTY, ROOK, PAWN, KING, QUEEN, BISHOP, KNIGHT};
    gint8              black_king_pos;
    gint8              white_king_pos;
    guint8             queensideCastleW;
    guint8             kingsideCastleW;
    guint8             queensideCastleB;
    guint8             kingsideCastleB;
    gint8              game_board[BOARDSIZE][BOARDSIZE];
    std::vector<Move>  move_log;
    MemFnc moves[8];
public:
	GameBoard();
	void initBoard();
	void initBoardDebug();
	gint8 operator()(guint8 x, guint8 y);
	void printBoard();
	std::vector<Move> getMoveLog();
	virtual ~GameBoard();
	void validMoves        (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validWPawnMoves   (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validBPawnMoves   (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validKnightMoves  (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validQueenMoves   (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validBishopMoves  (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validRookMoves    (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);
	void validKingMoves    (std::vector<Move> &move_list, guint8 x_init, guint8 y_init);

	void moveSafely(std::vector<Move> &move_list,guint8 x_init,guint8 y_init,guint8 x_final,
			guint8 y_final,gint8 captured,int score,nsChess::Special move_type);
	guint8 checkIssuesAddMove(std::vector<Move> &move_list,guint8 x_init, guint8 y_init,guint8 x_final,
			guint8 y_final,int score, nsChess::Special move_type);
	void makeMove(std::vector<Move> &move_list,Move move);
	void undoMove(std::vector<Move> &move_list,guint8 trash);
	Move getLastMove();
	void makeMove(Move move);
	void undoLastMove();
	void changePiece(guint8 x, guint8 y, gint8 piece);
	gint8 kingIsSafe(gint8 player);
};

#endif /* GAMEBOARD_H_ */
