/*
 * Human.h
 *
 *  Created on: Jun 14, 2016
 *      Author: jdobrusky
 */

#ifndef HUMAN_H_
#define HUMAN_H_

#include "Player.h"
#include "GameBoard.h"
#include "Move.h"

class Human: public Player {
public:
	Human();
	Human(nsChess::Color color);
	virtual ~Human();
};

#endif /* HUMAN_H_ */
