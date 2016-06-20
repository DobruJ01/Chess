/*
 * Move.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: Justin Dobrusky and Conner Clark
 */

#include "Move.h"

Move::Move() {
	this->x_init = 0;
	this->y_init = 0;
	this->x_final = 0;
	this->y_final = 0;
	this->captured = 0;
	this->score = 0;
	this->move_type = nsChess::NORMAL;

}
Move::Move(guint8 x_init,guint8 y_init,guint8 x_final,guint8 y_final,gint8 captured,int score,nsChess::Special move_type){
	this->x_init = x_init;
	this->y_init = y_init;
	this->x_final = x_final;
	this->y_final = y_final;
	this->captured = captured;
	this->score = score;
	this->move_type = move_type;
}
Move::Move(const Move &other){
	this->x_init = other.x_init;
	this->y_init = other.y_init;
	this->x_final = other.x_final;
	this->y_final = other.y_final;
	this->captured = other.captured;
	this->score = other.score;
	this->move_type = other.move_type;
}
bool Move::operator==(const Move &other) const{
	return
	this->x_init    == other.x_init     &&
	this->y_init    == other.y_init     &&
	this->x_final   == other.x_final    &&
	this->y_final   == other.y_final;
}
Move& Move::operator=(const Move &other){
	this->x_init = other.x_init;
	this->y_init = other.y_init;
	this->x_final = other.x_final;
	this->y_final = other.y_final;
	this->captured = other.captured;
	this->score = other.score;
	this->move_type = other.move_type;

	return *this;
}
bool Move::isValid(){
	return this->x_init != 255;
}
void Move::clear(){
	x_init = 255;
	x_final = 255;
	y_init = 255;
	y_final = 255;
	captured = 127;
	score = INT_MIN;
	move_type = nsChess::NORMAL;
}
bool Move::equals(guint8 x_init,guint8 y_init,guint8 x_final,guint8 y_final){
	return
	this->x_init == x_init   &&
	this->y_init == y_init   &&
	this->x_final == x_final &&
	this->y_final == y_final;
}
void Move::print(){
	printf("%c%d%c%d,%d T%d, ",y_init + 'a',x_init , y_final +'a',x_final, captured,move_type);
}
bool Move::sortCaptured(const Move &one, const Move &two){
	return one.captured < two.captured;
}
Move::~Move() {
	// TODO Auto-generated destructor stub
}

