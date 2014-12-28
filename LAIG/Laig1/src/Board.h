#ifndef BOARD_H
#define BOARD_H

#include "Appearance.h"
#include "Primitives.h"
#include "Animation.h"
#include <sstream>

typedef struct {
	Appearance * Player;
	Animation * animPiece;
	Animation * animWall;
	bool active;
	bool wall;
   
} Play;


class Board: public Primitives {
	Cube *wall;
	Cylinder *piece;
	Rect* rec;
	CGFappearance * Black, *White;
	Appearance * PlayerA, *PlayerB, *wallApp;
	Play playerPlay;

public:	
	vector< vector<char> > board;
	int nSpaces;
	Board();
	~Board(void);
	void draw(Texture* t);
	void update(unsigned long t);
	string getBoardString();
};

#endif