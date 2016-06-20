/*
 * GUI.h
 *
 *  Created on: Jun 15, 2016
 *      Author: jdobrusky
 */

#ifndef GUI_H_
#define GUI_H_

#include <gtk/gtk.h>
#include "GameBoard.h"
#include "Player.h"

class GUI {
private:

	/* GUI variables */
	GtkWidget *window ;
	GtkWidget *fixed ;
	GtkWidget *chess_icon ;
	GtkWidget *table ;

	guint MAX_MSGLEN;
	guint SQUARE_SIZE;
	guint WINDOW_BORDER;
	guint BOARD_BORDER;
	guint BOARD_WIDTH;
	guint BOARD_HEIGHT;
	guint WINDOW_WIDTH;
	guint WINDOW_HEIGHT;


	/* Game variables */
	GameBoard *board;
	Player *players[2];
	guint8 turn;
	gint8 click_count;
	gint user_clicks[2];

public:
	GUI();
	virtual ~GUI();
	void createWindow();
	void DrawBoard();
	void UpdateBoard();
	void DeleteBoard();
	void AssignHandlers();
	static void humanClick(GtkWidget *widget, GdkEvent  *event, gpointer  data);
	void startGame();
	void aiMove();
	void humanMove(gint,gint);
	void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y);
	void checkGameOver();
	void clearUserClicks();
	static gboolean on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer data);
	static gboolean on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data);
	void undoMove();

};

#endif /* GUI_H_ */
