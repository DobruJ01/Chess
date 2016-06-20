/*
 * AI.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: jdobrusky
 */

#include "AI.h"
#include "Rating.h"
#include "ChessNameSpace.h"
AI::AI() {
	Player(nsChess::BLACK,4);
	difficulty = nsChess::EASY;

}
AI::AI(nsChess::Color color,nsChess::Difficulty difficulty) : Player(color,4){
	this->difficulty = difficulty;
}
AI::~AI() {
	// TODO Auto-generated destructor stub
}

