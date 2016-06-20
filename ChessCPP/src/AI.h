/*
 * AI.h
 *
 *  Created on: Jun 14, 2016
 *      Author: jdobrusky
 */

#ifndef AI_H_
#define AI_H_

#include "Player.h"
#include "ChessNameSpace.h"
class AI: public Player {
private:
	nsChess::Difficulty difficulty;
public:
	AI();
	AI(nsChess::Color color,nsChess::Difficulty difficulty);
	virtual ~AI();
};

#endif /* AI_H_ */
