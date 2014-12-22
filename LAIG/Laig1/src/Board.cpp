#include "Board.h"

Board::Board()
{
	this->nSpaces = 7;
	
	float xy1[2] = {0, 0};
	float xy2[2] = {(float)1/nSpaces, (float)1/nSpaces};
	this->rec = new Rect(xy1[0],xy1[1], xy2[0],xy2[1]);

	vector<char> boardTmp;

	for (int i = 0; i < (this->nSpaces * this->nSpaces * 2); i++){
		boardTmp.push_back(0);
	}

	board.push_back(boardTmp);

	Black = new CGFappearance("textures/black.jpg",1,1);
	White = new CGFappearance("textures/white.jpg",1,1);

}


Board::~Board(void) {
}


void Board::draw(Texture* t)
{
	glPushMatrix();		
	glScaled(2.5,1,2.5);
	glTranslated(2.9, 4.35, 3.9);	
	
	// For each line

	int black = 2;

    for(int i = 0; i < nSpaces; i++) {
		float x = (float)i/nSpaces;
        // For each row
        for(int j = 0; j < nSpaces; j++) {

			glPushMatrix();

			glPushName(i+1);
			glPushName(j+1);

			float y = (float)j/nSpaces;			


			// Draw Space
			glPushMatrix();
			glRotated(-90, 1, 0, 0);
			glTranslated(x, y, 0);

			black ++;
	        black %= 2;
			if(black)
				Black->apply();
			else
				White->apply();

			rec->draw(t);
			glPopMatrix();

			glPopName();
			glPopName();

			glPopMatrix();

        }
    }

	glPopMatrix();
}

vector<char> Board::getPositions(){
	return board[this->board.size()-1];
}

void Board::setPositions( vector<char> newPos ){
	this->board.push_back(newPos);
}

void Board::selectSpace(int column, int row)
{
	for(unsigned int i = 0; i < selectedColumns.size(); i++) {
		if(selectedColumns[i] == column 
			&& selectedRows[i] == row) {
				selectedColumns.erase(selectedColumns.begin() + i);
				selectedRows.erase(selectedRows.begin() + i);
				return;
		}
	}

	selectedColumns.push_back(column);
	selectedRows.push_back(row);
}

bool Board::isSelected(int column, int row) {
	for(unsigned int i = 0; i < selectedColumns.size(); i++) {
		if(selectedColumns[i] == column 
			&& selectedRows[i] == row) {
				return true;
		}
	}
	return false;
}

void Board::clearSelected() {
	selectedColumns.clear();
	selectedRows.clear();
}

vector<char> Board::undo() {
	 if(board.size() > 1) {
		 vector<char> ret = board[board.size()-1];
		 board.pop_back();
		 return ret;
	 }
	
	 throw exception();
}