/*
 * GameBoard.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: jdobrusky
 */

#include "GameBoard.h"
#include "ChessNameSpace.h"
#include <stdlib.h>
#include "Move.h"
GameBoard::GameBoard() {

	queensideCastleW = 0;
	kingsideCastleW = 0;
	queensideCastleB = 0;
	kingsideCastleB = 0;
//	game_board = new gint8*[BOARDSIZE];
//	for(int i=0;i<BOARDSIZE;++i)
//		game_board[i] = new gint8[BOARDSIZE];
	initBoard();
	black_king_pos = 4;
	white_king_pos = 60;
//TODO - delete this after debugging.
	for(int i=0;i<BOARDSIZE;++i){
		for(int j=0;j<BOARDSIZE;++j){
			if(game_board[i][j] == KING){
				white_king_pos = i*BOARDSIZE + j;
			}
			if(game_board[i][j] == -KING){
				black_king_pos = i*BOARDSIZE + j;
			}
		}
	}

}

GameBoard::~GameBoard() {
//	for(int i=0;i<BOARDSIZE;++i)
//		delete game_board[i];
//	delete game_board;
}

gint8 GameBoard::operator()(guint8 x, guint8 y){
	return game_board[x][y];
}
void GameBoard::initBoard(){
//	initBoardDebug();
//	return;
	gint8 gameboard[8][8] =
	{{-ROOK,-KNIGHT,-BISHOP,-QUEEN,-KING,-BISHOP,-KNIGHT,-ROOK},
	{-PAWN,-PAWN  ,-PAWN  ,-PAWN, -PAWN,  -PAWN,  -PAWN,-PAWN},
	{EMPTY,EMPTY  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY},
	{EMPTY,EMPTY  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY},
	{EMPTY,EMPTY  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY},
	{EMPTY,EMPTY  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  EMPTY,EMPTY},
	{PAWN ,PAWN   ,PAWN   ,PAWN ,  PAWN,   PAWN,   PAWN, PAWN},
	{ROOK ,KNIGHT ,BISHOP ,QUEEN ,KING ,BISHOP ,KNIGHT , ROOK}};

	for (guint8 y=0; y<BOARDSIZE; y++)
		for (guint8 x=0; x<BOARDSIZE; x++)
			game_board[x][y] = gameboard[x][y];
}
void GameBoard::initBoardDebug(){
	gint8 gameboard[8][8] =
	{{-ROOK,EMPTY  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  -KING,EMPTY},
	{-PAWN,EMPTY  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  EMPTY,-PAWN},
	{EMPTY,EMPTY  ,-KNIGHT  ,EMPTY, EMPTY,  EMPTY,  -PAWN,EMPTY},
	{EMPTY,-BISHOP  ,EMPTY  ,EMPTY, EMPTY,  EMPTY,  PAWN,EMPTY},
	{EMPTY,EMPTY  ,EMPTY  ,EMPTY, -ROOK,  EMPTY,  EMPTY,PAWN},
	{EMPTY,PAWN  ,EMPTY  ,EMPTY, BISHOP,  EMPTY,  EMPTY,EMPTY},
	{PAWN,EMPTY  ,KING  ,EMPTY, EMPTY,  PAWN,  EMPTY,EMPTY},
	{EMPTY,EMPTY  ,EMPTY  ,EMPTY, -BISHOP,  EMPTY,  EMPTY,EMPTY}};

	for (guint8 y=0; y<BOARDSIZE; y++)
		for (guint8 x=0; x<BOARDSIZE; x++)
			game_board[x][y] = gameboard[x][y];
}
void GameBoard::printBoard(){
	guint8 i = 0, j=0;
	guint8 number = -1;
	printf("\n   A, B, C, D, E, F, G, H\n");
	do{
		j=0;
		printf("%d: ",++number);
		do{
			game_board[i][j] == -PAWN    ? printf("P") :
			game_board[i][j] == -ROOK    ? printf("R") :
			game_board[i][j] == -BISHOP  ? printf("B") :
			game_board[i][j] == -QUEEN   ? printf("Q") :
			game_board[i][j] == -KING    ? printf("K") :
			game_board[i][j] == -KNIGHT  ? printf("N") :
			game_board[i][j] ==  PAWN    ? printf("p") :
			game_board[i][j] ==  ROOK    ? printf("r") :
			game_board[i][j] ==  BISHOP  ? printf("b") :
			game_board[i][j] ==  QUEEN   ? printf("q") :
			game_board[i][j] ==  KING    ? printf("k") :
			game_board[i][j] ==  KNIGHT  ? printf("n") :
			printf("_");
			printf(", ");
			++j;
		}while(j<BOARDSIZE);
		printf("\n");
		++i;
	}while(i<BOARDSIZE);
	printf("\n\n");
}
std::vector<Move> GameBoard::getMoveLog(){
	return move_log;
}
void GameBoard::validMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	/* enum piece_types{EMPTY, ROOK, PAWN, KING, QUEEN, BISHOP, KNIGHT}; */
	/* if position is empty, then nothing to do; return */
	if(!game_board[x_init][y_init])
		return;

	/* The function to call is the same as the enum except for pawns. To combat this,
	 * index 7 covers black pawns.*/
	char function_call = (game_board[x_init][y_init] == -PAWN) ? 7 : abs(game_board[x_init][y_init]);

	if(function_call > 7)
		return;

	//static MemFnc moves[8] = {&GameBoard::validRookMoves,&GameBoard::validRookMoves,&GameBoard::validWPawnMoves,&GameBoard::validKingMoves,&GameBoard::validQueenMoves,&GameBoard::validBishopMoves,&GameBoard::validKnightMoves,&GameBoard::validBPawnMoves};
	/* moves[0] cannot happen, rook is just a space holder */
	static void (GameBoard::*moves[8])(std::vector<Move>&, guint8, guint8) = {&GameBoard::validRookMoves,&GameBoard::validRookMoves,&GameBoard::validWPawnMoves,&GameBoard::validKingMoves,&GameBoard::validQueenMoves,&GameBoard::validBishopMoves,&GameBoard::validKnightMoves,&GameBoard::validBPawnMoves};

	//moves[0](move_list,x_init,y_init);
	/*Redirect call to appropriate function*/
	(*this.*moves[abs(function_call)])(move_list,x_init,y_init);
}

void GameBoard::validWPawnMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	/* En Passant */
	if(move_log.size()){
		Move last_move = move_log.back();
		if(game_board[last_move.x_final][last_move.y_final] == -PAWN){ //Last piece to move must be enemy pawn
			if(last_move.x_final - last_move.x_init == 2){ //Last piece must move two spaces forward
				if(y_init - 1 >= 0 && last_move.x_final == x_init && last_move.y_final == y_init-1){  //Pawn left of pawn to move
					/* en passant is finally possible */
					moveSafely(move_list,x_init,y_init,x_init-1,y_init-1,EMPTY,0,nsChess::ENP);
				}
				if(y_init + 1 < BOARDSIZE && last_move.x_final == x_init && last_move.y_final == y_init+1){  //Pawn right of pawn to move
					/* en passant is finally possible */
					moveSafely(move_list,x_init,y_init,x_init-1,y_init+1,EMPTY,0,nsChess::ENP);
				}
			}
		}
	}
	/*Can move two spaces forward if on initial rank*/
	if(x_init == 6 && !game_board[x_init-2][y_init] && !game_board[x_init-1][y_init]){
		moveSafely(move_list,x_init,y_init,x_init-2,y_init,EMPTY,0,nsChess::NORMAL);
	}
	if(x_init-1 >= 0){ /*Ensure within board range*/
		if(!game_board[x_init-1][y_init]){ /*Make sure space is empty */
			if(x_init-1 == 0){ /* if file 7 then pawn promotion */
				moveSafely(move_list,x_init,y_init,x_init-1,y_init,EMPTY,0,nsChess::PP);/*Move one forward*/
			}else
				moveSafely(move_list,x_init,y_init,x_init-1,y_init,EMPTY,0,nsChess::NORMAL);/*Move one forward*/
		}
		/*positive == ally piece, negative == enemy piece*/
		/*Check NW*/
		if(y_init-1 >=0 && game_board[x_init-1][y_init-1]*game_board[x_init][y_init] < 0){/*KILLL!!*/
			if(x_init-1 == 0) /* if file 7 then pawn promotion */
				moveSafely(move_list,x_init,y_init,x_init-1,y_init-1,game_board[x_init-1][y_init-1],0,nsChess::PP); /*Move one forward*/
			else
				moveSafely(move_list,x_init,y_init,x_init-1,y_init-1,game_board[x_init-1][y_init-1],0,nsChess::NORMAL); /*Move one forward*/
		}
		/*Check NE*/
		if(y_init+1 <BOARDSIZE && game_board[x_init-1][y_init+1]*game_board[x_init][y_init] < 0){/*KILLL!!*/
			if(x_init-1 == 0) /* if file 7 then pawn promotion */
				moveSafely(move_list,x_init,y_init,x_init-1,y_init+1,game_board[x_init-1][y_init+1],0,nsChess::PP);/*Move one forward*/
			else
				moveSafely(move_list,x_init,y_init,x_init-1,y_init+1,game_board[x_init-1][y_init+1],0,nsChess::NORMAL);/*Move one forward*/
		}
	}
}

void GameBoard::validBPawnMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	/* En Passant */
	if(move_log.size()){
		Move last_move = move_log.back();
		if(game_board[last_move.x_final][last_move.y_final] == PAWN){ //Last piece to move must be enemy pawn
			if(last_move.x_final - last_move.x_init == -2){ //Last piece must move two spaces forward
				if(y_init - 1 >= 0 && last_move.x_final == x_init && last_move.y_final == y_init-1){  //Pawn left of pawn to move
					/* en passant is finally possible */
					moveSafely(move_list,x_init,y_init,x_init+1,y_init-1,EMPTY,0,nsChess::ENP);
				}
				if(y_init + 1 < BOARDSIZE && last_move.x_final == x_init && last_move.y_final == y_init+1){  //Pawn right of pawn to move
					/* en passant is finally possible */
					moveSafely(move_list,x_init,y_init,x_init+1,y_init+1,EMPTY,0,nsChess::ENP);
				}
			}
		}
	}
	/*Can move two spaces forward if on initial rank*/
	if(x_init == 1 && !game_board[x_init+2][y_init] && !game_board[x_init+1][y_init]){
		moveSafely(move_list,x_init,y_init,x_init+2,y_init,EMPTY,0,nsChess::NORMAL);
	}
	if(x_init+1 < BOARDSIZE){ /*Ensure within board range*/
		if(!game_board[x_init+1][y_init]){ /*Make sure space is empty */
			if(x_init+1 == 7){ /* if file 7 then pawn promotion */
				moveSafely(move_list,x_init,y_init,x_init+1,y_init,EMPTY,0,nsChess::PP);
			}else
				moveSafely(move_list,x_init,y_init,x_init+1,y_init,EMPTY,0,nsChess::NORMAL);
		}
		/*positive == ally piece, negative == enemy piece*/
		/*Check NW*/
		if(y_init-1 >=0 && game_board[x_init+1][y_init-1]*game_board[x_init][y_init] < 0){/*KILLL!!*/
			if(x_init+1 == 7) /* if file 7 then pawn promotion */
				moveSafely(move_list,x_init,y_init,x_init+1,y_init-1,game_board[x_init+1][y_init-1],0,nsChess::PP);
			else
				moveSafely(move_list,x_init,y_init,x_init+1,y_init-1,game_board[x_init+1][y_init-1],0,nsChess::NORMAL);
		}
		/*Check NE*/
		if(y_init+1 <BOARDSIZE && game_board[x_init+1][y_init+1]*game_board[x_init][y_init] < 0){/*KILLL!!*/
			if(x_init+1 == 7) /* if file 7 then pawn promotion */
				moveSafely(move_list,x_init,y_init,x_init+1,y_init+1,game_board[x_init+1][y_init+1],0,nsChess::PP);
			else
				moveSafely(move_list,x_init,y_init,x_init+1,y_init+1,game_board[x_init+1][y_init+1],0,nsChess::NORMAL);
		}
	}
}
void GameBoard::moveSafely(std::vector<Move> &move_list,guint8 x_init,guint8 y_init,guint8 x_final,
		guint8 y_final,gint8 captured,int score,nsChess::Special move_type){

	Move move(x_init,y_init,x_final,y_final,captured,score,move_type);

	/* make the move */
	makeMove(move_list,move);

	char king_safe = kingIsSafe(game_board[x_final][y_final]);

	/* undo the move. If king is safe then move is valid and stays on list
	 * else move gets removed from list*/
	undoMove(move_list,!king_safe);
}
guint8 GameBoard::checkIssuesAddMove(std::vector<Move> &move_list,guint8 x_init, guint8 y_init,guint8 x_final,
		guint8 y_final,int score, nsChess::Special move_type){
	if(game_board[x_final][y_final] * game_board[x_init][y_init] <= 0){
		moveSafely(move_list,x_init,y_init,x_final,y_final,game_board[x_final][y_final],score,move_type);
		if(game_board[x_final][y_final]) /* If you run in to something, stop */
			return 0;
	}
	else /* ran into ally piece */
		return 0;
	return 1;
}
void GameBoard::makeMove(std::vector<Move> &move_list,Move move){
	/* Update Castle flags */
	/* If left castle moved then queenside castle no longer possible, etc..*/
	if(game_board[move.x_init][move.y_init] == -KING){
		black_king_pos = move.x_final * 8 + move.y_final;
		++queensideCastleB;
		++kingsideCastleB;
	}
	if(game_board[move.x_init][move.y_init] == KING){
		white_king_pos = move.x_final * 8 + move.y_final;
		++queensideCastleW;
		++kingsideCastleW;
	}
	if(game_board[move.x_init][move.y_init] == -ROOK){
		if(move.x_init == 0 && move.y_init == 0){
			++queensideCastleB;
		}
		if(move.x_init == 0 && move.y_init == 7){
			++kingsideCastleB;
		}
	}
	if(game_board[move.x_init][move.y_init] == ROOK){
		if(move.x_init == 7 && move.y_init == 0){
			++queensideCastleW;
		}
		if(move.x_init == 7 && move.y_init == 7){
			++kingsideCastleW;
		}
	}

	/* Castle is special move. Move king, delete rook, create rook to left/right of king */
	if(move.move_type == nsChess::CASTLE){
		if(game_board[move.x_init][move.y_init] < 0 && game_board[move.x_init][move.y_init] == -KING){
			if(move.y_init < move.y_final){
				/* kingside castle */
				game_board[0][7] = EMPTY;
				game_board[0][5] = -ROOK;
			}else{
				/* queenside castle */
				game_board[0][0] = EMPTY;
				game_board[0][3] = -ROOK;
			}
		}else if(game_board[move.x_init][move.y_init] > 0 && game_board[move.x_init][move.y_init] == KING){
			if(move.y_init < move.y_final){
				/* kingside castle */
				game_board[7][7] = EMPTY;
				game_board[7][5] = ROOK;
			}else{
				/* queenside castle */
				game_board[7][0] = EMPTY;
				game_board[7][3] = ROOK;
			}
		}
	}

	/* En Passant */
	if(move.move_type == nsChess::ENP){
		if(game_board[move.x_init][move.y_init] == -PAWN){   //Black en passant
			game_board[move.x_final-1][move.y_final] = EMPTY;
		}else{                                               //White en passant
			game_board[move.x_final+1][move.y_final] = EMPTY;
		}
	}
	/* Pawn Promotion */
	/* auto assumes a queen */
	if(move.move_type == nsChess::PP){
		if(game_board[move.x_init][move.y_init] > 0)
			game_board[move.x_init][move.y_init] = QUEEN;
		else
			game_board[move.x_init][move.y_init] = -QUEEN;
	}
	/* update game board */
	game_board[move.x_final][move.y_final] = game_board[move.x_init][move.y_init];
	game_board[move.x_init][move.y_init] = EMPTY;
	move_list.push_back(move);
}
void GameBoard::makeMove(Move move){
	makeMove(move_log,move);
}
void GameBoard::undoMove(std::vector<Move> &move_list,guint8 trash){

	/* Ensure there is a move to undo */
	if(move_list.size()){
		Move move = move_list.back();
		/* update castle flags. AI checks many moves into future so these must update */
		if(game_board[move.x_final][move.y_final] == -KING){
			black_king_pos = move.x_init * 8 + move.y_init;
			--queensideCastleB;
			--kingsideCastleB;
		}
		if(game_board[move.x_final][move.y_final] == KING){
			white_king_pos = move.x_init * 8 + move.y_init;
			--queensideCastleW;
			--kingsideCastleW;
		}
		if(abs((int)game_board[move.x_final][move.y_final]) == ROOK){
			if(move.x_init == 0){
				if(move.y_init == 0)
					--queensideCastleB;
				if(move.y_init == 7)
					--kingsideCastleB;
			}
			if(move.x_init == 7){
				if(move.y_init == 0)
					--queensideCastleW;
				if(move.y_init == 7)
					--kingsideCastleW;
			}

		}

		/* Castle. Put rook back in corner move king back to original location */
		if(move.move_type == nsChess::CASTLE){
			if(game_board[move.x_final][move.y_final] < 0 && game_board[move.x_final][move.y_final] == -KING){
				if(move.y_init < move.y_final){
					/* kingside castle */
					game_board[0][5] = EMPTY;
					game_board[0][7] = -ROOK;
				}else{
					/* queenside castle */
					game_board[0][3] = EMPTY;
					game_board[0][0] = -ROOK;
				}
			}else if(game_board[move.x_final][move.y_final] > 0 && game_board[move.x_final][move.y_final] == KING){
				if(move.y_init < move.y_final){
					/* kingside castle */
					game_board[7][5] = EMPTY;
					game_board[7][7] = ROOK;
				}else{
					/* queenside castle */
					game_board[7][3] = EMPTY;
					game_board[7][0] = ROOK;
				}
			}
			/* Castle needs to change old pos specifically to EMPTY else have CASTLE flag on board
			 * which does not render!*/
			game_board[move.x_init][move.y_init] = game_board[move.x_final][move.y_final];
			game_board[move.x_final][move.y_final] = EMPTY;
		}else{

			/* En Passant */
			if(move.move_type == nsChess::ENP){
				if(game_board[move.x_final][move.y_final] == -PAWN){ //Black en passant
					game_board[move.x_final-1][move.y_final] = PAWN;
				}else{                                               //White en passant
					game_board[move.x_final+1][move.y_final] = -PAWN;
				}
			}
			/* Pawn Promotion */
			if(move.move_type == nsChess::PP){
				if(game_board[move.x_final][move.y_final] > 0)
					game_board[move.x_final][move.y_final] = PAWN;
				else
					game_board[move.x_final][move.y_final] = -PAWN;
			}
			/* Set old pos back to par*/
			game_board[move.x_init][move.y_init] = game_board[move.x_final][move.y_final];
			game_board[move.x_final][move.y_final] = move.captured;
		}

		/* trash removes move from list. move_log is a list of all moves currently
		 * available. In order to check if move is valid, the move must be made, then undone.
		 * If the king wasn't safe then the trash flag will be set.*/
		if(trash){
			move_list.pop_back();
		}
	}
}
void GameBoard::undoLastMove(){
	undoMove(move_log,1);
}
void GameBoard::validKnightMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	/* Check one above to ensure within board*/
	if(x_init - 1 >= 0){
		/* Check left to ensure within board*/
		if(y_init-2 >= 0)
			checkIssuesAddMove(move_list,x_init,y_init,x_init-1,y_init-2,0,nsChess::NORMAL);
		/* Check right to ensure within board */
		if(y_init+2 < BOARDSIZE )
			checkIssuesAddMove(move_list,x_init,y_init,x_init-1,y_init+2,0,nsChess::NORMAL);
		/* Check two above to ensure within board*/
		if(x_init - 2 >= 0){
			/* Check left to ensure within board*/
			if(y_init-1 >= 0)
				checkIssuesAddMove(move_list,x_init,y_init,x_init-2,y_init-1,0,nsChess::NORMAL);
			/* Check right to ensure within board */
			if(y_init+1 < BOARDSIZE )
				checkIssuesAddMove(move_list,x_init,y_init,x_init-2,y_init+1,0,nsChess::NORMAL);
		}
	}
	/* Check one below to ensure within board*/
	if(x_init + 1 < BOARDSIZE){
		/* Check left to ensure within board*/
		if(y_init-2 >= 0)
			checkIssuesAddMove(move_list,x_init,y_init,x_init+1,y_init-2,0,nsChess::NORMAL);
		/* Check right to ensure within board */
		if(y_init+2 < BOARDSIZE )
			checkIssuesAddMove(move_list,x_init,y_init,x_init+1,y_init+2,0,nsChess::NORMAL);
		/* Check two below to ensure within board*/
		if(x_init + 2 < BOARDSIZE){
			/* Check left to ensure within board*/
			if(y_init-1 >= 0){
				checkIssuesAddMove(move_list,x_init,y_init,x_init+2,y_init-1,0,nsChess::NORMAL);
			}
			/* Check right to ensure within board */
			if(y_init+1 < BOARDSIZE )
				checkIssuesAddMove(move_list,x_init,y_init,x_init+2,y_init+1,0,nsChess::NORMAL);
		}
	}
}

void GameBoard::validQueenMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	validBishopMoves(move_list,x_init,y_init);
	validRookMoves(move_list,x_init,y_init);
}

void GameBoard::validBishopMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	int x,y;

	/* Starting position moving SW */
	for(x=x_init+1, y=y_init-1; x<BOARDSIZE && y>=0; x++, y--){
		if(!checkIssuesAddMove(move_list,x_init,y_init,x,y,0,nsChess::NORMAL))
			break;
	}

	/* starting position moving SE */
	for(x=x_init+1, y=y_init+1; x<BOARDSIZE && y<BOARDSIZE; x++, y++){
		if(!checkIssuesAddMove(move_list,x_init,y_init,x,y,0,nsChess::NORMAL))
			break;
	}
	/* starting position moving NW */
	for(x=x_init-1, y=y_init-1; x>=0 && y>=0; x--, y--){
		if(!checkIssuesAddMove(move_list,x_init,y_init,x,y,0,nsChess::NORMAL))
			break;
	}
	/* starting position moving NE */
	for(x=x_init-1, y=y_init+1; x>=0 && y<BOARDSIZE; x--, y++){
		if(!checkIssuesAddMove(move_list,x_init,y_init,x,y,0,nsChess::NORMAL))
			break;
	}
}

void GameBoard::validRookMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	guint8 x=0,y=0;

	/* Starting position moving down */
	for(x=x_init+1;x<BOARDSIZE;x++){
		/* Add all positions along the way unless king is not safe */
		if(!checkIssuesAddMove(move_list,x_init,y_init,x,y_init,0,nsChess::NORMAL))
			break;
	}
	/* Starting position moving up */
	for(x=x_init-1;x<255;--x){
		/* Add all positions along the way unless king is not safe */
		if(!checkIssuesAddMove(move_list,x_init,y_init,x,y_init,0,nsChess::NORMAL))
				  break;
	}

	/* starting position moving right */
	for(y=y_init+1;y<BOARDSIZE;y++){
		/* Add all positions along the way unless king is not safe */
		if(!checkIssuesAddMove(move_list,x_init,y_init,x_init,y,0,nsChess::NORMAL))
			break;
	}
	/* starting position moving left */
	for(y=y_init-1;y<255;--y){
		/* Add all positions along the way unless king is not safe */
		if(!checkIssuesAddMove(move_list,x_init,y_init,x_init,y,0,nsChess::NORMAL))
			break;
	}
}

void GameBoard::validKingMoves(std::vector<Move> &move_list, guint8 x_init, guint8 y_init){
	char x,y;

	/* black castle moves - kingside and queenside*/
	if(game_board[x_init][y_init] < 0 && x_init == 0 && y_init == 4){
		if(!kingsideCastleB){
			if(game_board[0][7] == -ROOK)
				if(game_board[0][5] == EMPTY && game_board[0][6] == EMPTY){
					moveSafely(move_list,x_init,y_init,x_init,y_init+2,EMPTY,0,nsChess::CASTLE);
				}
		}
		if(!queensideCastleB){
			if(game_board[0][0] == -ROOK)
				if(game_board[0][1] == EMPTY && game_board[0][2] == EMPTY && game_board[0][3] == EMPTY){
					moveSafely(move_list,x_init,y_init,x_init,y_init-2,EMPTY,0,nsChess::CASTLE);
				}
		}
	/* white castle moves - kingside and queenside */
	}else if(game_board[x_init][y_init] > 0 && x_init == 7 && y_init == 4){
		if(!kingsideCastleW){
			if(game_board[7][7] == ROOK)
				if(game_board[7][5] == EMPTY && game_board[7][6] == EMPTY){
					moveSafely(move_list,x_init,y_init,x_init,y_init+2,EMPTY,0,nsChess::CASTLE);
				}
		}
		if(!queensideCastleW){
			if(game_board[7][0] == ROOK)
				if(!game_board[7][1] && !game_board[7][2] && !game_board[7][3]){
					moveSafely(move_list,x_init,y_init,x_init,y_init-2,EMPTY,0,nsChess::CASTLE);
				}
		}
	}


	for(x=-1;x<=1;++x){
		for(y=-1;y<=1;++y){
			if(x_init+x < 0 || y_init+y < 0 || x_init+x >= BOARDSIZE || y_init+y >= BOARDSIZE)
				continue;
			if(game_board[x_init+x][y_init+y] * game_board[x_init][y_init] <= 0){
				moveSafely(move_list,x_init,y_init,x_init+x,y_init+y,game_board[x_init+x][y_init+y],0,nsChess::NORMAL);
			}
		}
	}
}
gint8 GameBoard::kingIsSafe(gint8 player){
	player = player < 0 ? -1 : 1;
	int pos = player < 0 ? black_king_pos : white_king_pos;
	int king_x = pos / 8;
	int king_y = pos % 8;
	int x=0,y=0;

	/* Check for pawns */
	if(player == 1){
		/**/
		if(king_x -1 >=0){
			if(king_y-1 >=0 && game_board[king_x-1][king_y-1] == -PAWN){
				return 0;
			}
			if(king_y+1 < BOARDSIZE && game_board[king_x-1][king_y+1] == -PAWN){
				return 0;
			}
		}
	}else{
		if(king_x +1 < BOARDSIZE){
			if(king_y-1 >=0 && game_board[king_x+1][king_y-1] == PAWN){
				return 0;
			}
			if(king_y+1 < BOARDSIZE && game_board[king_x+1][king_y+1] == PAWN){
				return 0;
			}
		}
	}
	/* Check UDLR threat*/
	/* Starting position moving down */
	x = king_x;
	while(++x < BOARDSIZE && !game_board[x][king_y]);
	if(x > 7){x=7;}
	if(player * game_board[x][king_y] < 0  && (abs((gint8)game_board[x][king_y]) == ROOK || abs((gint8)game_board[x][king_y]) == QUEEN))
		return 0;
	x = king_x;
	while(--x > 0 && !game_board[x][king_y]);
	if(x<0){x=0;}
	if(player * game_board[x][king_y] < 0 && (abs((gint8)game_board[x][king_y]) == ROOK || abs((gint8)game_board[x][king_y]) == QUEEN))
		return 0;
	y = king_y;
	while(++y < BOARDSIZE && !game_board[king_x][y]);
	if(y>=BOARDSIZE){y=BOARDSIZE-1;}
	if(player * game_board[king_x][y] < 0 && (abs((gint8)game_board[king_x][y]) == ROOK || abs((gint8)game_board[king_x][y]) == QUEEN))
		return 0;
	y = king_y;
	while(--y > 0 && !game_board[king_x][y]);
	if(y<0){y=0;}
	if(player * game_board[king_x][y] < 0 && (abs((gint8)game_board[king_x][y]) == ROOK || abs((gint8)game_board[king_x][y]) == QUEEN))
		return 0;

	/* Check Diagonals */
	x = king_x+1;
	y = king_y+1;

	/* down and to the right */
	while(!game_board[x][y]){
		if(x+1 < BOARDSIZE){
			if(y+1 < BOARDSIZE){
				++x; ++y;
			}
			else
				break;
		}else break;
	}
	if(x<BOARDSIZE && y<BOARDSIZE)
		if(player * game_board[x][y] < 0 && (abs(game_board[x][y]) == BISHOP || abs(game_board[x][y]) == QUEEN))
			return 0;


	/* up and to the left */
	x = king_x-1;
	y = king_y-1;
	while(!game_board[x][y]){
		if(x-1 >= 0){ if(y-1 >= 0){ --x; --y;} else break; }else break;
	}
	if(x>=0 && y>=0)
		if(player * game_board[x][y] < 0 && (abs((gint8)game_board[x][y]) == BISHOP || abs((gint8)game_board[x][y]) == QUEEN))
			return 0;

	/* down and to the left */
	x = king_x+1;
	y = king_y-1;
	while(!game_board[x][y]){
		if(x+1 < BOARDSIZE){
			if(y-1 >=0){
				++x; --y;
			}
			else
				break;
		}else break;
	}
	if(x<BOARDSIZE && y>=0)
		if(player * game_board[x][y] < 0 && (abs((int)game_board[x][y]) == BISHOP || abs((gint8)game_board[x][y]) == QUEEN))
			return 0;

	/* up and to the right */
	x = king_x-1;
	y = king_y+1;
	while(!game_board[x][y]){
		if(x-1 >= 0){
			if(y+1 < BOARDSIZE){
				--x; ++y;
			}
			else
				break;
		}else break;
	}
	if(y<BOARDSIZE && x>=0)
		if(player * game_board[x][y] < 0 && (abs((int)game_board[x][y]) == BISHOP || abs((gint8)game_board[x][y]) == QUEEN))
			return 0;

	/* Check for king */
	for(x=-1;x<=1;++x){
		for(y=-1;y<=1;++y){
			if(king_x+x < 0 || king_y+y < 0 || king_x+x >= BOARDSIZE || king_y+y >= BOARDSIZE)
				continue;
			if(game_board[king_x+x][king_y+y] * player < 0 && abs((gint8)game_board[king_x+x][king_y+y]) == KING)
				return 0;
		}
	}

/* Check for Knight */
	/* Check one above to ensure within board*/
		if(king_x - 1 >= 0){
			/* Check left to ensure within board*/
			if(king_y-2 >= 0)
				if(game_board[king_x-1][king_y-2]*player < 0 && abs((gint8)game_board[king_x-1][king_y-2]) == KNIGHT)
					return 0;
			/* Check right to ensure within board */
			if(king_y+2 < BOARDSIZE )
				if(game_board[king_x-1][king_y+2]*player < 0 && abs((gint8)game_board[king_x-1][king_y+2]) == KNIGHT)
					return 0;
			/* Check two above to ensure within board*/
			if(king_x - 2 >= 0){
				/* Check left to ensure within board*/
				if(king_y-1 >= 0)
					if(game_board[king_x-2][king_y-1]*player < 0 && abs((gint8)game_board[king_x-2][king_y-1]) == KNIGHT)
						return 0;
				/* Check right to ensure within board */
				if(king_y+1 < BOARDSIZE )
					if(game_board[king_x-2][king_y+1]*player < 0 && abs((gint8)game_board[king_x-2][king_y+1]) == KNIGHT)
						return 0;
			}
		}
		/* Check one below to ensure within board*/
		if(king_x + 1 < BOARDSIZE){
			/* Check left to ensure within board*/
			if(king_y-2 >= 0)
				if(game_board[king_x+1][king_y-2]*player < 0 && abs((gint8)game_board[king_x+1][king_y-2]) == KNIGHT)
					return 0;
			/* Check right to ensure within board */
			if(king_y+2 < BOARDSIZE )
				if(game_board[king_x+1][king_y+2]*player < 0 && abs((gint8)game_board[king_x+1][king_y+2]) == KNIGHT)
					return 0;
			/* Check two below to ensure within board*/
			if(king_x + 2 < BOARDSIZE){
				/* Check left to ensure within board*/
				if(king_y-1 >= 0)
					if(game_board[king_x+2][king_y-1]*player < 0 && abs((gint8)game_board[king_x+2][king_y-1]) == KNIGHT)
						return 0;
				/* Check right to ensure within board */
				if(king_y+1 < BOARDSIZE )
					if(game_board[king_x+2][king_y+1]*player < 0 && abs((gint8)game_board[king_x+2][king_y+1]) == KNIGHT)
						return 0;
			}
		}
	return 1;
}
Move GameBoard::getLastMove(){
	return move_log.back();
}
void GameBoard::changePiece(guint8 x, guint8 y, gint8 piece){
	game_board[x][y] = piece;
}
