/*
 * Move.h
 *
 *  Created on: Jun 13, 2016
 *      Author: jdobrusky
 */

#ifndef MOVE_H_
#define MOVE_H_
#include <gtk/gtk.h>
#include "ChessNameSpace.h"

class Move {
public:

	guint8 x_init;
	guint8 y_init;
	guint8 x_final;
	guint8 y_final;
	gint8 captured;
	int score;
	nsChess::Special move_type;
	Move();
	Move(guint8 x_init,guint8 y_init,guint8 x_final,guint8 y_final,gint8 captured,int score,nsChess::Special move_type);
	Move(const Move &other);
	Move& operator=(const Move &other);
	void print();
	virtual ~Move();
	bool operator==(const Move &other) const;
	bool equals(guint8 x_init,guint8 y_init,guint8 x_final,guint8 y_final);
	void clear();
	static bool sortCaptured(const Move &one, const Move &two);
	bool isValid();

};

#endif /* MOVE_H_ */
