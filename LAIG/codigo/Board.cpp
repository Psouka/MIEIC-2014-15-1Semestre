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
		item[12][6] = 'B';

		this->board = item;

		playerPlay.active = false;
		playerPlay.wallFalling = false;
		playerPlay.wall = 0;
		playerPlay.Player = PlayerA;

		playerPlay.animPiece = new NoAnimation();
		playerPlay.animWall = new NoAnimation();
		playerPlay.col = playerPlay.line = 0;

		selectetPos.col = -1;
		selectetPos.line = -1;
		selectetPos.Player = -1;

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

	if(playerPlay.active)
		delete(playerPlay.animPiece);

	if(playerPlay.wall)
		delete(playerPlay.animWall);

	delete(playerPlay.Player);
}

void Board::draw(Texture* t)
{
	glPushMatrix();		
	glScaled(2.5,1,2.5);
	glTranslated(3, 4.25, 3);
	glRotated(90, 1, 0, 0);

	// For each line
	int black = 2;
	for(int i = 0; i < nSpaces; i++) {
		float x = (float)i/nSpaces;
		for(int j = 0; j < nSpaces; j++) {
			float y = (float)j/nSpaces;		

			glPushMatrix();

			glPushName(i);
			glPushName(j);

			glPushMatrix();

			glTranslated(x,y, -0.05);
			glScaled(0.14,0.14,0.075);

			black ++;
			black %= 2;
			if(selectetPos.col == i && selectetPos.line == j)
			{
				if(selectetPos.Player == 1)
					PlayerA->apply();
				else
					PlayerB->apply();

			}
			else if(black)
				Black->apply();
			else
				White->apply();

			wall->draw(t); 

			glPopName();
			glPopName();

			glPopMatrix();
			glPopMatrix();

			// DrawPiece

			if(board[i*2][j*2] == 'A')
			{
				glPushMatrix();
				glTranslated(x, y, -0.15);
				PlayerA->apply();
				piece->draw(PlayerA->APPTexture);
				glPopMatrix();
			}
			else if(board[i*2][j*2] == 'B')
			{
				glPushMatrix();
				glTranslated(x, y, -0.15);
				PlayerB->apply();
				piece->draw(PlayerB->APPTexture);
				glPopMatrix();
			}

			if(j+1 < nSpaces){

				if(board[i*2][j*2+1] == '-' )
				{
					glPushMatrix();
					glTranslated(x, y+0.07, -0.1);
					glScaled(0.13,0.02,0.13);

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
					glTranslated(y, -x-0.07, -0.1);
					glScaled(0.13,0.02,0.13);

					wallApp->apply();
					wall->draw(t);

					glPopMatrix();
				}
			}
		} 
	}
	//drawPlay
	if(playerPlay.active && playerPlay.wall == 0)
	{
		glPushMatrix();
		glTranslated((float)playerPlay.col/nSpaces, (float)playerPlay.line/nSpaces, -0.15);
		playerPlay.animPiece->apply();
		playerPlay.Player->apply();
		piece->draw(playerPlay.Player->APPTexture);
		glPopMatrix();
	}
	else if(playerPlay.active) // move
	{
		glPushMatrix();
		glTranslated((float)playerPlay.col/nSpaces, (float)playerPlay.line/nSpaces, -0.15);
		playerPlay.animPiece->apply();
		playerPlay.Player->apply();
		piece->draw(playerPlay.Player->APPTexture);
		glPopMatrix();
	}


	if(playerPlay.wallFalling){
		vector<float> temp = playerPlay.animPiece->getFinalPos();
		float wallX = (playerPlay.col+temp[0]*7)/nSpaces, wallY= (playerPlay.line+temp[1]*7)/nSpaces;

		glPushMatrix();

		switch(playerPlay.wall){
		case 1:
			glTranslated(wallX, wallY-0.07, -0.1);
			break;
		case 2:
			glTranslated(wallX, wallY+0.07, -0.1);
			break;
		case 3:
			glRotated(90, 0, 0, 1);
			glTranslated(wallY, -wallX+0.07, -0.1);
			break;
		case 4:
			glRotated(90, 0, 0, 1);
			glTranslated(wallY, -wallX-0.07, -0.1);
			break;

		}
		glScaled(0.13,0.02,0.13);
		playerPlay.animWall->apply();
		wallApp->apply();
		wall->draw(t);
		glPopMatrix();

	}
	glPopMatrix();
}

void Board::update(unsigned long t){

	if(playerPlay.active)
		playerPlay.animPiece->update(t);

	if(playerPlay.wallFalling)
		playerPlay.animWall->update(t);

	if(playerPlay.animPiece->getStop() && playerPlay.active)
		startWall();

	if(playerPlay.animWall->getStop() && playerPlay.wallFalling)
		endPlay();
}

string Board::getBoardString() {

	stringstream boardString;
	boardString << "[";

	// Each Row
	for(unsigned int i = 0; i < board.size(); i++) {

		boardString << "[";

		// Each Point
		for(unsigned int j = 0; j < board[i].size(); j ++) {
			if(board[j][i] == '0')
				boardString << board[j][i];
			else
				boardString << "'" << board[j][i] << "'";

			if(j + 1 < board[i].size())
				boardString << ",";
		}

		boardString << "]";

		if(i + 1 < board.size())
			boardString << ",";

	}

	boardString << "]";

	return boardString.str();
}

Appearance* Board::getPalyerApp(unsigned int p){
	if(p == 1)
		return PlayerA;
	else
		return PlayerB;
}

void Board::startWall(){

	if(playerPlay.active && playerPlay.wall == 0)
	{
		if(playerPlay.Player->getAppId() == "PlayerA")
			board[2*playerPlay.col][2*playerPlay.line] = 'A';
		else if(playerPlay.Player->getAppId() == "PlayerB")
			board[2*playerPlay.col][2*playerPlay.line] = 'B';

		playerPlay.wallFalling = false;

	}
	else if(playerPlay.active)
	{
		vector<float> t = playerPlay.animPiece->getFinalPos();

		if(playerPlay.Player->getAppId() == "PlayerA")
			board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7)] = 'A';
		else if(playerPlay.Player->getAppId() == "PlayerB")
			board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7)] = 'B';

		playerPlay.wallFalling = true;
	}

	playerPlay.active = false;

}

void Board::endPlay(){
	playerPlay.wallFalling = false;
	vector<float> t = playerPlay.animPiece->getFinalPos();

	switch(playerPlay.wall){

	case 1:
		board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7) -1] = '-';
		break;
	case 2:
		board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7) +1] = '-';
		break;
	case 3:
		board[2*(playerPlay.col+t[0]*7)-1][2*(playerPlay.line+t[1]*7)] = '|';
		break;
	case 4:
		board[2*(playerPlay.col+t[0]*7)+1][2*(playerPlay.line+t[1]*7)] = '|';
		break;

	}

}

void Board::resetBoard(){
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
		item[12][6] = 'B';

		this->board = item;
}

bool Board::isPlaying(){
	return playerPlay.active || playerPlay.wallFalling;
}

void Board::undo(){

	if(playerPlay.wall == 0)
	{
		board[2*playerPlay.col][2*playerPlay.line] = '0';
	}
	else
	{
		vector<float> t = playerPlay.animPiece->getFinalPos();
		char oldchar = board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7)];
		board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7)] = '0';

		board[2*(playerPlay.col)][2*(playerPlay.line)] = oldchar;

		switch(playerPlay.wall){
		case 1:
			board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7) -1] = ' ';
			break;
		case 2:
			board[2*(playerPlay.col+t[0]*7)][2*(playerPlay.line+t[1]*7) +1] = ' ';
			break;
		case 3:
			board[2*(playerPlay.col+t[0]*7)-1][2*(playerPlay.line+t[1]*7)] = ' ';
			break;
		case 4:
			board[2*(playerPlay.col+t[0]*7)+1][2*(playerPlay.line+t[1]*7)] = ' ';
			break;
		}

	}
}

void Board::setBoard(string boardString){

	boardString.erase(remove(boardString.begin(), boardString.end(), '\r'), boardString.end());
	boardString.erase(remove(boardString.begin(), boardString.end(), '['), boardString.end());
	boardString.erase(remove(boardString.begin(), boardString.end(), ']'), boardString.end());
	boardString.erase(remove(boardString.begin(), boardString.end(), '.'), boardString.end());
	boardString.erase(remove(boardString.begin(), boardString.end(), '\''), boardString.end());
	boardString.erase(remove(boardString.begin(), boardString.end(), ','), boardString.end());

	unsigned int indice = 0;
	for(unsigned int i = 0; i < board.size(); i++)
		for(unsigned int j = 0; j < board[i].size(); j++)
			{
				if(boardString.at(indice) != 'A')
				board[j][i] = boardString.at(indice);
				indice++;
			}


}