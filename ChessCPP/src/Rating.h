/*
 * Rating.h
 *
 *  Created on: Jun 14, 2016
 *      Author: Justin Dobrusky and Conner Clark
 */

#ifndef RATING_H_
#define RATING_H_
#include "GameBoard.h"
class Rating {
private:
	static int white_ratings[7][8][8];
public:
	Rating();
	virtual ~Rating();
	static int rating(GameBoard game_board, Move best_move, gint8 player,std::vector<Move> curr_moves);
	static int material(GameBoard game_board, Move best_move, gint8 player);
	static int boardPosition(GameBoard game_board, Move best_move, int player);
};

#endif /* RATING_H_ */
