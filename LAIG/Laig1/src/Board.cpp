#include "Board.h"

Board::Board()
{
	this->nSpaces = 7;

	float xy1[2] = {0, 0};
	float xy2[2] = {(float)1/nSpaces, (float)1/nSpaces};
	this->rec = new Rect(xy1[0],xy1[1], xy2[0],xy2[1]);

	piece = new Cylinder(0.05,0.05, 0.05, 50, 1);
	wall = new Cube();

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

	wallApp = new Appearance(a,d,s,50,"wall","none");
	wallApp->setAppTexture(new Texture("textB","textures/yellow.jpg",1,1));

	vector<vector< char > > item ( 13,vector<char> ( 13, '0' ) );

	for(unsigned int i = 0; i < item.size(); i++)
		for(unsigned int a = 0; a < item[i].size(); a++)
		{
			if(i % 2 != 0)
					item[i][a] = ' ';
			else if(a % 2 != 0)
				item[i][a] = ' ';
				
		}

		item[0][6] = 'A';
		item[0][0] = 'A';
		item[1][0] = '|';
		item[1][2] = '|';
		item[0][1] = '-';
		item[12][6] = 'B';

		this->board = item;
}

Board::~Board(void) {
	delete(White);
	delete(Black);
	delete(rec);

	delete(wall);
	delete(piece);
	delete(PlayerA);
	delete(PlayerB);
	delete(wallApp);
}

void Board::draw(Texture* t)
{
	glPushMatrix();		
	glScaled(2.5,1,2.5);
	glTranslated(3, 4.25, 3);
	glRotated(180, 1, 0, 0);

	// For each line
	int black = 2;
	glRotated(-90, 1, 0, 0);
	for(int i = 0; i < nSpaces; i++) {
		float x = (float)i/nSpaces;
		for(int j = 0; j < nSpaces; j++) {
			float y = (float)j/nSpaces;		

			glPushMatrix();

			glPushName(i);
			glPushName(j);

			glPushMatrix();
			
			glTranslated(x,y, 0);
			glScaled(5.75,5.75,1);

			black ++;
			black %= 2;
			if(black)
				Black->apply();
			else
				White->apply();

			wall->draw(t); 

			glPopName();
			glPopName();

			glPopMatrix();
			glPopMatrix();
			// DrawPiece


			if(board[i*2][j*2] == 'A' || board[i*2][j*2] == 'B'){

				glPushMatrix();

				glTranslated(x, y, -0.05);

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

			if(j+1 < nSpaces){

				if(board[i*2][j*2+1] == '-' )
				{
					glPushMatrix();
					glTranslated(x, y+0.07, -0.03);
					glScaled(5,1,1);

					wallApp->apply();
					wall->draw(t);

					glPopMatrix();
				}
			}

			if(i+1 < nSpaces){

				if(board[i*2+1][j*2] == '|')
				{
					glPushMatrix();
					glRotated(90, 0, 0, 1);
					glTranslated(y, -x-0.07, -0.03);
					glScaled(5,1,1);

					wallApp->apply();
					wall->draw(t);

					glPopMatrix();
				}
			} 
		}
	}

	glPopMatrix();
}
