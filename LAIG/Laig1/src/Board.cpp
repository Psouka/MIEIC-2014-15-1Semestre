#include "Board.h"

Board::Board()
{
	this->nSpaces = 7;

	float xy1[2] = {0, 0};
	float xy2[2] = {(float)1/nSpaces, (float)1/nSpaces};
	this->rec = new Rect(xy1[0],xy1[1], xy2[0],xy2[1]);

	piece = new Cylinder(0.05,0.05, 0.05, 50, 1);

	vector<char> boardTmp;

	for (int i = 0; i < (this->nSpaces * this->nSpaces * 2); i++){
		boardTmp.push_back(0);
	}

	board.push_back(boardTmp);

	Black = new CGFappearance("textures/black.jpg",1,1);
	White = new CGFappearance("textures/white.jpg",1,1);

	// Appearance(float *a, float *d, float *s, float shi, string id, string textureref);
	float a[4] = {0.4,0.4,0.4,1};
	float d[4] = {0.3,0.3,0.3,1};
	float s[4] = {0.5,0.5,0.5,1};
	PlayerA = new Appearance(a,d,s,50,"PlayerA","none");
	PlayerA->setAppTexture(new Texture("textA","textures/blue.jpg",1,1));
	PlayerB = new Appearance(a,d,s,50,"PlayerB","none");
	PlayerB->setAppTexture(new Texture("textB","textures/red.jpg",1,1));
	vector<vector< char > > item ( 13,vector<char> ( 13, '0' ) );

	for(unsigned int i = 0; i < item.size(); i++)
		for(unsigned int a = 0; a < item[i].size(); a++)
		{
			if(a % 2 != 0)
				item[i][a] = ' ';
			else
				if(i % 2 != 0)
					item[i][a] = ' ';
		}

		item[0][6] = 'A';
		item[12][6] = 'B';

		this->board = item;
}

Board::~Board(void) {
	delete(White);
	delete(Black);
	delete(rec);
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

			glPushName(i);
			glPushName(j);

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

			glPopName();
			glPopName();

			glPopMatrix();

			// DrawPiece
			if(board[i*2][j*2] == 'A' || board[i*2][j*2] == 'B'){

				glPushMatrix();

				glRotated(-90, 1, 0, 0);
				glTranslated(x+0.07, y+0.07, 0);

				if(board[i*2][j*2] == 'A')
				{
					PlayerA->apply();
					piece->draw(PlayerA->APPTexture);
				}
				else
				{
					PlayerB->apply();
					piece->draw(PlayerB->APPTexture);
				}
				glPopMatrix();
			}


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