//============================================================================
// Name        : ChessCPP.cpp
// Author      : Justin Dobrusky and Conner Clark
// Version     :
// Copyright   : Copyright 2016
// Description : Chess
//============================================================================

#include <gtk/gtk.h>
#include "GameBoard.h"
#include "GUI.h"

int main(int argc, char *argv[]){
	GUI *gui = new GUI();

	gtk_init(&argc, &argv);
	gui->createWindow();

	gtk_main();
	delete gui;
	return 0;
}
