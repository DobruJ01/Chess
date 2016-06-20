/*
 * GUI.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: jdobrusky
 */

#include "GUI.h"
#include "ChessNameSpace.h"
#include "AI.h"
#include "Human.h"
#include <gdk/gdkkeysyms.h>

GUI::GUI() {
	window = NULL;
	table = NULL;
	chess_icon = NULL;
	fixed = NULL;
	MAX_MSGLEN  = 400;
	SQUARE_SIZE = 50;
	WINDOW_BORDER = 10;
	BOARD_BORDER = 10;
	BOARD_WIDTH  = (8*SQUARE_SIZE);
	BOARD_HEIGHT = (8*SQUARE_SIZE);
	WINDOW_WIDTH  = (BOARD_WIDTH + 2*BOARD_BORDER);
	WINDOW_HEIGHT = (BOARD_HEIGHT + 2*BOARD_BORDER);
	players[1] = new AI(nsChess::BLACK,nsChess::EASY);
	players[0] = new Human(nsChess::WHITE);
	turn = 0;
	board = new GameBoard();
	user_clicks[0] = INT_MIN;
	user_clicks[1] = INT_MIN;
	click_count = 0;
}

GUI::~GUI() {
	delete players[0];
	delete players[1];
	delete board;
}

void GUI::createWindow(){
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
  gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ;
  gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ;
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ;
  gtk_window_set_title(GTK_WINDOW(window), "The C Team: Chess!") ;
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE) ;
  AssignHandlers();
  UpdateBoard();
//TODO - startGame() will come from user starting game from GUI
  startGame();
}
void GUI::clearUserClicks(){
	user_clicks[0] = INT_MIN;
	user_clicks[1] = INT_MIN;
	click_count = 0;
}
void GUI::UpdateBoard()
{
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard();

    fixed = gtk_fixed_new() ;
//Begin ghetto color hack
    GdkColor color;

    color.red = 65535;
    color.green = 0;
    color.blue = 0;

    gtk_widget_modify_bg (window, GTK_STATE_NORMAL, &color);
// End ghetto color hack
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ;

}
void GUI::DeleteBoard(){
	gtk_container_remove(GTK_CONTAINER(window), fixed) ;
}
void GUI::AssignHandlers()
{
  g_signal_connect(window, "delete_event", G_CALLBACK(on_delete_event), NULL) ;
  gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ;
  g_signal_connect(window, "button_press_event", G_CALLBACK(humanClick), (gpointer) this) ;
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), (gpointer)this);
}
gboolean GUI::on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer data)
{
	if(event->keyval == GDK_u){
		GUI *gui = (GUI*)data;
		gui->undoMove();
      printf("key pressed: %s\n", "u");
	}
	return FALSE;
}
void GUI::undoMove(){
	if(dynamic_cast<Human*>(players[turn])){
		board->undoLastMove();
		board->undoLastMove();
		DeleteBoard();
		UpdateBoard();
	}
}
void GUI::humanClick(GtkWidget *widget, GdkEvent  *event, gpointer data){
	int coord_x, coord_y, grid_x, grid_y;
	GUI *gui = (GUI*) data;

	GdkModifierType state;
	gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ;
	gui->CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);
	gui->humanMove(grid_x,grid_y);
}
void GUI::startGame(){
	/* if two AI are playing */
	if (dynamic_cast<AI*>(players[0]) && dynamic_cast<AI*>(players[1])){
//TODO - make both threaded - maybe loop here

	/* AI vs Human*/
	}else if(dynamic_cast<AI*>(players[turn]))
		aiMove();
	/* else human clicks will dictate the game */
}
void GUI::aiMove(){
	players[turn]->findBestMove(*board);
	players[turn]->performMove(*board);
	++turn %= 2;
#ifdef JUSTIN
	printf("AI just moved\n");
	board->printBoard();
#endif
	DeleteBoard();
	UpdateBoard();
	checkGameOver();
}
void GUI::checkGameOver(){
	//TODO - checkmate display logic
	bool has_moves = players[turn]->hasMoves(*board);
	bool in_check = players[turn]->isInCheck(*board);

	if(has_moves && in_check){
		printf("*************************************************\n");
		printf("*                     Check                     *\n");
		printf("*************************************************\n");
	}else if(!has_moves && in_check){
		printf("*************************************************\n");
		printf("*                   Checkmate                   *\n");
		printf("*************************************************\n");
	}else if(!has_moves && !in_check){
		printf("*************************************************\n");
		printf("*                   Stalemate                   *\n");
		printf("*************************************************\n");
	}
}
void GUI::humanMove(gint x, gint y){
printf("click count: %d\n",click_count);
	/* If comes here while AI turn then don't allow */
	if (dynamic_cast<AI*>(players[turn]))
		return;
	/* first click */
	if(!click_count){
		/* Check that player clicks on his/her own piece */
		if((*board)(x,y) && ((players[turn]->getColor()<0) == ((*board)(x,y)<0))){
			user_clicks[0] = x;
			user_clicks[1] = y;
			++click_count;
//TODO - highlight the board to show available moves
			/* probably should be a class variable */
			std::vector<Move> available_moves = players[turn]->generateMoves(*board,x,y);
			DeleteBoard();
			UpdateBoard();
		}else{
			clearUserClicks();
		}
	/* second click */
	}else{
		/* make piece move */
		players[turn]->updateNextMove(*board,user_clicks[0],user_clicks[1],x,y);
		if(players[turn]->performMove(*board)){

			/* if a pawn promotion let user choose which piece */
			if(board->getLastMove().move_type == nsChess::PP){
//TODO - Pawn promotion display
				/* show a user dialog */
				gint8 chosen_piece= nsChess::QUEEN;
				board->changePiece(board->getLastMove().x_final,board->getLastMove().y_final,chosen_piece*players[turn]->getColor());
			}
#ifdef JUSTIN
			printf("Human just moved\n");
			board->printBoard();
#endif
			++turn %= 2;
		}
//TODO - check/mate logic

		clearUserClicks();
		DeleteBoard();
		UpdateBoard();
	}
//TODO - make threaded AI

	/* Check if AI's turn to move (otherwise wait for another human click )*/
	if (dynamic_cast<AI*>(players[turn])){
#ifdef JUSTIN
		printf("AI's turn\n");
#endif
		checkGameOver();
		aiMove();
	}
}
void GUI::CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	*g_y = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	*g_x = (c_y - BOARD_BORDER) / SQUARE_SIZE;

	printf("Coordinates: %d,%d\n",*g_x,*g_y);
}
gboolean GUI::on_delete_event (GtkWidget *widget, GdkEvent  *event, gpointer   data)
{
	g_print ("delete event occurred\n");
	gtk_main_quit();
	return TRUE;
}
void GUI::DrawBoard(){
	using namespace nsChess;

	int x, y;

	for(x = 0; x < 8; x ++)
	{
		for(y = 0; y  < 8; y ++)
		{
			switch((*board)(y,x))
			{

				case -KING:
					chess_icon = gtk_image_new_from_file("./icons/Black_Queen.png") ;
					break;
				case -PAWN:
					chess_icon = gtk_image_new_from_file("./icons/Black_Pawn.png") ;
					break;
				case -ROOK:
					chess_icon = gtk_image_new_from_file("./icons/Black_Rook.png") ;
					break;
				case -KNIGHT:
					chess_icon = gtk_image_new_from_file("./icons/Black_Knight.png") ;
					break;
				case -BISHOP:
					chess_icon = gtk_image_new_from_file("./icons/Black_Bishop.png") ;
					break;
				case -QUEEN:
					chess_icon = gtk_image_new_from_file("./icons/Queen_Bee.png") ;
					break;
				case KING:
					chess_icon = gtk_image_new_from_file("./icons/White_Queen.png") ;
					break;
				case PAWN:
					chess_icon = gtk_image_new_from_file("./icons/White_Pawn.png") ;
					break;
				case ROOK:
					chess_icon = gtk_image_new_from_file("./icons/White_Rook.png") ;
					break;
				case KNIGHT:
					chess_icon = gtk_image_new_from_file("./icons/White_Knight.png") ;
					break;
				case BISHOP:
					chess_icon = gtk_image_new_from_file("./icons/White_Bishop.png") ;
					break;
				case QUEEN:
					chess_icon = gtk_image_new_from_file("./icons/White_King.png") ;
					break;
				case EMPTY:
					if((y+2)%2==0){
						if((x+2)%2==0){
							chess_icon = gtk_image_new_from_file("./icons/Wsquare.jpg") ;
						}
						else{
							chess_icon = gtk_image_new_from_file("./icons/Bsquare.jpg") ;
						}
                     }
					else{
						if((x+2)%2==0){
							chess_icon = gtk_image_new_from_file("./icons/Bsquare.jpg") ;
						}
						else   {
							chess_icon = gtk_image_new_from_file("./icons/Wsquare.jpg") ;
						}
					}
					break;
//          case ENP:
//            if((y+2)%2==0){
//           if((x+2)%2==0){
//                chess_icon = gtk_image_new_from_file("./icons/Wsquare.jpg") ;
//                       }
//           else{
//                chess_icon = gtk_image_new_from_file("./icons/Bsquare.jpg") ;
//               }
//                     }
//      else{
//           if((x+2)%2==0){
//              chess_icon = gtk_image_new_from_file("./icons/Bsquare.jpg") ;
//                       }
//           else   {
//              chess_icon = gtk_image_new_from_file("./icons/Wsquare.jpg") ;
//                  }
//          }
//          break;
				default:
					break;

			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, x, x + 1, y, y + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
}

