#ifndef BOARD_H
#define BOARD_H

#include "Appearance.h"
#include "Primitives.h"


class Board: public Primitives {
	vector< vector<char> > board;
	Cube *wall;
	Cylinder *piece;
	Rect* rec;
	CGFappearance * Black, *White;
	Appearance * PlayerA, *PlayerB, *wallApp;

public:	
	int nSpaces;
	Board();
	~Board(void);
	void draw(Texture* t);
	void update(unsigned long t){};
};

#endif