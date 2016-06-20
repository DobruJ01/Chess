/*
 * Rating.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: jdobrusky
 */

#include "Rating.h"
#include <stdlib.h>
#include <math.h>
Rating::Rating() {
	// TODO Auto-generated constructor stub

}

Rating::~Rating() {
	// TODO Auto-generated destructor stub
}

int Rating::white_ratings[7][8][8] =
/* empty board */
		{{{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}},
		/* rook board */
		{{0,0,0,0,0,0,0,0},
		{0,5,5,5,5,5,5,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,5,0,5,0,0}},
		/* pawn board */
		{{50,50,50,50,50,50,50,50},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,50,50,50,50,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,-5,-5,0,0,0},
		{0,0,0,0,0,0,0,0}},
		/* king board */
		{{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,-10,-10,-10,0,0,0},
		{0,0,50,0,0,0,500,0}},
		/* queen board */
		{{0,0,0,0,0,0,0,0},
		{0,10,10,10,10,10,10,0},
		{0,10,10,10,10,10,10,0},
		{0,10,10,10,10,10,10,0},
		{0,10,10,10,10,10,10,0},
		{0,10,10,10,10,10,10,0},
		{0,10,10,10,10,10,10,0},
		{0,0,0,0,0,0,0,0}},
		/* bishop board */
		{{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,5,0,0,0,0,5,5},
		{0,5,5,0,0,5,5,5},
		{0,5,5,5,5,5,5,0},
		{0,5,5,5,5,5,5,0},
		{0,0,0,0,0,0,0,0}},
		/* knight board */
		{{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,10,10,10,10,10,0},
		{0,0,10,10,10,10,10,0},
		{0,0,10,10,10,10,10,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}}};

int Rating::rating(GameBoard game_board, Move best_move, gint8 player,std::vector<Move> curr_moves){
	int score = 0;
	score += material(game_board,best_move,player) - material(game_board,best_move,-player);
	score += boardPosition(game_board, best_move,player);
	score += game_board.kingIsSafe(-player)*50;
	score -= boardPosition(game_board, best_move,-player);

	return score;
}
//
int Rating::boardPosition(GameBoard game_board, Move best_move, int player){
	int score = 0;
	int i=0,j=0;
	/* parse through board and tally all piece locations */
	for(i=0;i<8;++i){
		for(j=0;j<8;j++){

			if(player > 0 && game_board(i,j)*player > 0){
				score += white_ratings[abs(game_board(i,j))][i][j];
			}
			if(player < 0 && game_board(i,j)*player > 0){
				score += white_ratings[abs(game_board(i,j))][7-i][j];
			}
		}
	}
	return score;

}

int Rating::material(GameBoard game_board, Move best_move, gint8 player){
	/*enum piece_types{EMPTY, ROOK, PAWN, KING, QUEEN, BISHOP, KNIGHT};*/

	int arr[7] = {0,700,50,500,1000,500,500};
	int x,y;
	int score = 0;

	for(x=0;x<8;++x){
		for(y=0;y<8;++y){
			if(game_board(x,y)*player > 0)
				score += arr[abs(game_board(x,y))];
		}
	}
	return score;
}
