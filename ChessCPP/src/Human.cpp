/*
 * Human.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: jdobrusky
 */

#include "Human.h"

Human::Human() : Player(nsChess::WHITE, 4) {

}
Human::Human(nsChess::Color color) : Player(color,4){

}
Human::~Human() {}
