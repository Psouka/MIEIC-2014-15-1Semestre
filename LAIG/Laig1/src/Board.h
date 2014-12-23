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

	bool isSelected(int column, int row);

public:	
	vector<int> selectedColumns;
	vector<int> selectedRows;

	int nSpaces;
	Board();
	~Board(void);

	vector<char> getPositions();
	void setPositions(vector<char> newPos);

	vector<char> undo();

	void selectSpace(int column, int row);
	void clearSelected();

	void draw(Texture* t);
	void update(unsigned long t){};
};

#endif