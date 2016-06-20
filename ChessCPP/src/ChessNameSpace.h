#ifndef CHESSNAMESPACE_H_
#define CHESSNAMESPACE_H_

#define JUSTIN //undefine this to get rid of my printf's
namespace nsChess{
	typedef enum {EASY,MEDIUM,HARD} Difficulty;
	typedef enum {WHITE=1,BLACK=-1} Color;
	typedef enum {NORMAL,CASTLE,ENP,PP} Special;
	enum {EMPTY, ROOK, PAWN, KING, QUEEN, BISHOP, KNIGHT};
}

#endif
