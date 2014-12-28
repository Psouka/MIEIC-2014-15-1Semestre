#ifndef BOARD_H
#define BOARD_H

#include "Appearance.h"
#include "Primitives.h"
#include "Animation.h"
#include <sstream>

typedef struct {
	unsigned int col,line;
	Appearance * Player;
	Animation * animPiece;
	Animation * animWall;
	bool active;
	int wall;
   
} Play;


class Board: public Primitives {
	Cube *wall;
	Cylinder *piece;
	Rect* rec;
	CGFappearance * Black, *White;
	Appearance * PlayerA, *PlayerB, *wallApp;
	

public:	
	vector< vector<char> > board;
	Play playerPlay;
	int nSpaces;
	Board();
	~Board(void);
	void draw(Texture* t);
	void update(unsigned long t);
	string getBoardString();
	Appearance* getPalyerApp(unsigned int  p);
	void resetPlay();
};

#endif