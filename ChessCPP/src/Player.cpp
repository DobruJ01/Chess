/*
 * Player.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: jdobrusky
 */

#include "Player.h"
#include "Rating.h"
#include <algorithm>
#include <ctime>

Player::Player() {
	color = nsChess::BLACK;
	max_depth = 4;
	next_move.clear();
}
Player::Player(nsChess::Color color,gint max_depth){
	this->max_depth = max_depth;
	this->color = color;
	next_move.clear();
}
Player::~Player() {
	// TODO Auto-generated destructor stub
}
std::vector<Move> Player::generateMoves(GameBoard game_board){
	unsigned char x=0,y=0;
	std::vector<Move> possible_moves;
	for(y=0;y<GameBoard::BOARDSIZE;++y){
		for(x=0;x<GameBoard::BOARDSIZE;++x){
			if(color*game_board(x,y)>0){
				game_board.validMoves(possible_moves,x,y);
			}
		}
	}
	return possible_moves;
}
std::vector<Move> Player::generateMoves(GameBoard game_board,gint8 player){
	unsigned char x=0,y=0;
	std::vector<Move> possible_moves;
	for(y=0;y<GameBoard::BOARDSIZE;++y){
		for(x=0;x<GameBoard::BOARDSIZE;++x){
			if(player*game_board(x,y)>0){
				game_board.validMoves(possible_moves,x,y);
			}
		}
	}
	return possible_moves;
}
std::vector<Move> Player::generateMoves(GameBoard game_board,guint8 x,guint8 y){
	std::vector<Move> possible_moves;

	if(color*game_board(x,y)>0){
		game_board.validMoves(possible_moves,x,y);
	}
#ifdef JUSTIN
	for(guint i=0;i<possible_moves.size();++i){
		possible_moves[i].print();
	}
#endif
	return possible_moves;
}
bool Player::hasMoves(GameBoard game_board){
	unsigned char x=0,y=0;
	std::vector<Move> possible_moves = generateMoves(game_board);

	return possible_moves.size();
}
bool Player::isInCheck(GameBoard game_board){
	return !game_board.kingIsSafe(color);
}
bool Player::isInCheckMate(GameBoard game_board){
	bool has_moves = hasMoves(game_board);
	bool check = isInCheck(game_board);

	return !has_moves && check;
}

int Player::alphaBetaMin(int depth, Move &best_move, int alpha, int beta, GameBoard game_board,gint8 player){
	int value = 0;
	/* Create list of possible moves */
	std::vector<Move> moves = generateMoves(game_board,player);

	if(!moves.size()){ //Checkmate
		return 30000;
	}
	if (depth == max_depth){ /*list is empty or depth == MAXDEPTH*/
		value = -Rating::rating(game_board,best_move,player,moves);
		return value;
	}
	std::stable_sort(moves.begin(),moves.end(),Move::sortCaptured);
	while(moves.size()){
		Move new_move = moves.back();
		moves.pop_back();
		game_board.makeMove(new_move);
		int value = alphaBetaMax(depth+1,best_move,alpha,beta,game_board,player*-1);
		if (value <= beta){
			beta = value;
			if(!depth){
				best_move.x_init = new_move.x_init;
				best_move.y_init = new_move.y_init;
				best_move.x_final = new_move.x_final;
				best_move.y_final = new_move.y_final;
				best_move.score = value;
				best_move.captured = new_move.captured;
				best_move.move_type = new_move.move_type;
#ifdef JUSTIN
				printf("\nBest move Min: ");
				best_move.print();
				printf("\n");
#endif
			}
		}
		game_board.undoLastMove();
		if (alpha >= beta){
			moves.clear();
			return beta;
		}
	}
	moves.clear();
	return beta;
}
int Player::alphaBetaMax(int depth, Move &best_move, int alpha, int beta, GameBoard game_board,gint8 player){
	int value = 0;

	/* Create list of possible moves */
	std::vector<Move> moves = generateMoves(game_board,player);

	if(!moves.size()){ //Checkmate
		return -30000;
	}
	if (depth == max_depth){ /*list is empty or depth == MAXDEPTH*/
		value = Rating::rating(game_board,best_move,player,moves);
		moves.clear();
		return value;
	}

	while(moves.size()){
		Move new_move = moves.back();
		moves.pop_back();
		game_board.makeMove(new_move);

		int value = alphaBetaMin(depth+1,best_move,alpha,beta,game_board,player*-1);

		if (value > alpha){
			alpha = value;
			if(!depth){
				best_move.x_init = new_move.x_init;
				best_move.y_init = new_move.y_init;
				best_move.x_final = new_move.x_final;
				best_move.y_final = new_move.y_final;
				best_move.captured = new_move.captured;
				best_move.score = value;
				best_move.move_type = new_move.move_type;
#ifdef JUSTIN
				printf("\nBest move Max: ");
				best_move.print();
				printf(": Score = %d\n",value);
#endif
			}
		}
		game_board.undoLastMove();
		if (alpha >= beta){
			moves.clear();
			return alpha;
		}
	}
	moves.clear();
	return alpha;

}
bool Player::findBestMove(GameBoard game_board){
	next_move.clear();

	/* pick best move and store it in best_move */
#ifdef JUSTIN
	printf("Going in as player %d\n",color);

	std::clock_t start;
	double duration;

	start = clock();
#endif
	alphaBetaMax(0,next_move,INT_MIN,INT_MAX,game_board,color);

#ifdef JUSTIN
	duration = double( clock() - start ) / CLOCKS_PER_SEC;

	printf("Storing this move: ");
	next_move.print();
	printf("\n");
	printf("move found in %2.10f seconds\n",duration);
#endif
	if(next_move.isValid()){
		return 1;
	}

	return 0; /* 0 means no move found */
}
nsChess::Color Player::getColor(){
	return color;
}

bool Player::updateNextMove(GameBoard game_board,guint8 x_init,guint8 y_init,guint8 x_final,guint8 y_final){
	std::vector<Move> moves = generateMoves(game_board,x_init,y_init);
	guint counter = -1;
	bool valid = false;

	next_move.clear();
	if(moves.size()){
		while(++counter < moves.size())
			if(moves[counter].equals(x_init,y_init,x_final,y_final)){
				valid = true;
				break;
			}
	}
#ifdef JUSTIN
	printf("\nMove to be performed:\n");

	next_move.print();
#endif
	if(valid)
		next_move = moves[counter];

	return valid;
}
bool Player::performMove(GameBoard &game_board){
	if(!next_move.isValid())
		return false;
	game_board.makeMove(next_move);

	return true;
}

