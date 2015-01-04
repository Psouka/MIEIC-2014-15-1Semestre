#include "Game.h"

Game::Game(){
	GameBoard = new Board();
	socket = new Socket();
	player = 1;
	bot = 0;
	endGame = true;
	undoDone = true;
	timePlay = 10;
	currentTime = 0;
	bestOf = 0;
	pointsA = pointsB = 0;
}

void Game::nextPlayer() {
	this->player++;
	this->player %= 2;
}

void Game::previousPlayer() {
	this->player--;
	this->player %= 2;
}

void Game::newGame(){
	currentTime = 0;
	player = 1;
	undoDone = true;
	endGame = false;
	GameBoard->resetBoard();
	GameBoard->selectetPos.col = -1;
	GameBoard->selectetPos.line = -1;

	switch(bestOf){
		case 0:
			if(pointsA > 1 && pointsB == 0 || pointsB > 1 && pointsA == 0 || pointsA + pointsB == 3)
				pointsA = pointsB = 0;
			break;
		case 1:
			if(pointsA > 2 && pointsB == 0 || pointsB > 2 && pointsA == 0 || pointsA + pointsB == 5)
				pointsA = pointsB = 0;
			break;
		case 2:
			if(pointsA > 4 && pointsB == 0 || pointsB > 4 && pointsA == 0 || pointsA + pointsB == 9)
				pointsA = pointsB = 0;
			break;

		}
}

Board* Game::getBoard(){
	return GameBoard;
}

Socket* Game:: getSocket(){
	return socket;
}

Game :: ~Game(void){
	delete(GameBoard);
	delete(socket);
}

void Game::addPiece(unsigned int x,unsigned int y){
	currentTime = 0;
	GameBoard->playerPlay.active = true;
	GameBoard->playerPlay.wallFalling = false;
	GameBoard->playerPlay.wall = 0;

	delete(GameBoard->playerPlay.animPiece);

	vector<vector<float>> cPoint;
	vector<float> point(3);
	point[0] = 0;
	point[1] = 0;
	point[2] = -0.5;
	cPoint.push_back(point);
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;
	cPoint.push_back(point);

	GameBoard->playerPlay.animPiece = new LinearAnimation("Piece",0.7, cPoint);

	delete(GameBoard->playerPlay.animWall);
	GameBoard->playerPlay.animWall = new NoAnimation();

	GameBoard->playerPlay.Player = GameBoard->getPalyerApp(this->player%2);

	GameBoard->playerPlay.col = x;
	GameBoard->playerPlay.line = y;

	undoDone = false;
	nextPlayer();
}

void Game::movePiece(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall){
	currentTime = 0;
	GameBoard->playerPlay.active = true;
	GameBoard->playerPlay.wall = wall;

	delete(GameBoard->playerPlay.animPiece);

	vector<vector<float>> cPoint;
	int dx,dy;
	dx = (xf-xi);
	dy = (yf-yi);
	vector<float> point(3);
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;
	cPoint.push_back(point);
	point[0] = (float)dx/14;
	point[1] = (float)dy/14;
	point[2] = -0.3;
	cPoint.push_back(point);
	point[0] = (float)dx/7;
	point[1] = (float)dy/7;
	point[2] = 0; 
	cPoint.push_back(point);

	GameBoard->playerPlay.animPiece = new LinearAnimation("Piece",2, cPoint);

	delete(GameBoard->playerPlay.animWall);
	cPoint.clear();
	point[0] = 0;
	point[1] = 0;
	point[2] = -0.5;
	cPoint.push_back(point);
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;
	cPoint.push_back(point);

	GameBoard->playerPlay.animWall = new LinearAnimation("Wall",0.7, cPoint);

	GameBoard->playerPlay.Player = GameBoard->getPalyerApp(this->player%2);

	GameBoard->playerPlay.col = xi;
	GameBoard->playerPlay.line = yi;

	GameBoard->board[2*xi][2*yi] = '0';

	undoDone = false;
	nextPlayer();
}

void Game::playBot(){

	if(endGame)
		return;

	currentTime = 0;

	stringstream message;
	stringstream BotPoints;
	vector< vector<char> > board = getFutureBoard();

	message << "[playBot, ";

	message << getboardString(board);;

	unsigned int NrP_Bots = 0;

	BotPoints <<  "[";

	for(unsigned int i = 0; i < 7; i++)
		for(unsigned int j = 0; j < 7; j++)
			if(board[2*i][2*j] == 'B')
			{
				NrP_Bots++;
				if(BotPoints.str() == "[")
				{
					BotPoints <<  "[";
					BotPoints <<  i*2;
					BotPoints <<  ",";
					BotPoints <<  j*2;
					BotPoints <<  "]";
				}
				else
				{
					BotPoints << ",";
					BotPoints <<  "[";
					BotPoints <<  i*2;
					BotPoints <<  ",";
					BotPoints <<  j*2;
					BotPoints <<  "]";
				}
			}
			BotPoints <<  "]";
			message << ","<< BotPoints.str() << ","<< NrP_Bots << "]";

			string response = this->socket->sendMessage(message.str());

			GameBoard->setBoard(response);
			nextPlayer();
}

bool Game::checkPiece(unsigned int x,unsigned int y){
	stringstream message;
	message << "[addPiece, ";

	message << GameBoard->getBoardString();

	if(player % 2)
		message << ",'A',";
	else
		message << ",'B',";

	message << x << ",";

	message << y << "]";


	string response = this->socket->sendMessage(message.str());


	return response == "1.\r\n";
}

bool Game::checkMove(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall){
	stringstream message;

	message << "[movePiece, ";

	message << GameBoard->getBoardString();

	if(player % 2)
		message << ",'A',";
	else
		message << ",'B',";

	message << xi << ",";

	message <<  yi << ",";

	message <<  xf << ",";

	message <<  yf << ",";

	message << wall  << "]";


	string response = this->socket->sendMessage(message.str());

	return response == "1.\r\n";
}

string Game::checkGame(){
	vector< vector<char> > board = getFutureBoard();
	stringstream message;
	message << "[gameOver, ";
	message << getboardString(board);
	message <<  "]";


	string response = this->socket->sendMessage(message.str());
	string retorno = "";
	if(response.find("0") == string::npos)
	{
		retorno += "\nPlayer ";
		retorno +=response.at(1);
		retorno +=" Won";
		endGame = true;

		if(response.at(1) == 'A')
			pointsA++;
		else
			pointsB++;
	}

	return retorno;
}

bool Game::gameState(){
	return endGame;
}

bool Game::isActive(){
	return GameBoard->isPlaying();
}

void Game::undo(){
	if(!undoDone)
	{
		GameBoard->undo();
		nextPlayer();
		undoDone = true;
		currentTime = 0;
		isSelected(-1,-1);
	}
}

int Game::getPlayer(){
	return player;
}

vector< vector<char> > Game::getFutureBoard(){

	vector< vector<char> > board = GameBoard->board;

	if(GameBoard->playerPlay.active && GameBoard->playerPlay.wall == 0)
	{
		if(GameBoard->playerPlay.Player->getAppId() == "PlayerA")
			board[2*GameBoard->playerPlay.col][2*GameBoard->playerPlay.line] = 'A';
		else if(GameBoard->playerPlay.Player->getAppId() == "PlayerB")
			board[2*GameBoard->playerPlay.col][2*GameBoard->playerPlay.line] = 'B';

	}
	else if(GameBoard->playerPlay.active)
	{
		vector<float> t = GameBoard->playerPlay.animPiece->getFinalPos();

		if(GameBoard->playerPlay.Player->getAppId() == "PlayerA")
			board[2*(GameBoard->playerPlay.col+t[0]*7)][2*(GameBoard->playerPlay.line+t[1]*7)] = 'A';
		else if(GameBoard->playerPlay.Player->getAppId() == "PlayerB")
			board[2*(GameBoard->playerPlay.col+t[0]*7)][2*(GameBoard->playerPlay.line+t[1]*7)] = 'B';

		switch(GameBoard->playerPlay.wall){

		case 1:
			board[2*(GameBoard->playerPlay.col+t[0]*7)][2*(GameBoard->playerPlay.line+t[1]*7) -1] = '-';
			break;
		case 2:
			board[2*(GameBoard->playerPlay.col+t[0]*7)][2*(GameBoard->playerPlay.line+t[1]*7) +1] = '-';
			break;
		case 3:
			board[2*(GameBoard->playerPlay.col+t[0]*7)-1][2*(GameBoard->playerPlay.line+t[1]*7)] = '|';
			break;
		case 4:
			board[2*(GameBoard->playerPlay.col+t[0]*7)+1][2*(GameBoard->playerPlay.line+t[1]*7)] = '|';
			break;

		}
	}
	return board;
}

string Game::getboardString(vector< vector<char> > board){

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

void Game::update(unsigned long t){
	if(currentTime < timePlay && !endGame)
		currentTime += 0.06;
}

bool Game::timePassed(){
	if(currentTime >= timePlay)
		endGame = true;

	return endGame;
}

void Game::isSelected(unsigned int col, unsigned int line){
	GameBoard->selectetPos.col = col;
	GameBoard->selectetPos.line = line;
	GameBoard->selectetPos.Player = player;
}

void Game::draw(){

	// drawTimer
	char array[10];
	glDisable(GL_LIGHTING);


	glPushMatrix();
	glTranslatef(2,2,1);
	glScalef(0.05, 0.05, 0.05);
	glColor3f(1.0,1.0,0.0);	

	sprintf_s(array, "%d", pointsA);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, array[0]);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, '-');
	sprintf_s(array, "%d", pointsB);
	glutStrokeCharacter(GLUT_STROKE_ROMAN, array[0]);
	glPopMatrix();


	glPushMatrix();		
	glScaled(2.5,1,2.5);
	glTranslated(3, 4.25, 3);
	glRotated(90, 1, 0, 0);

	if(player == 1){
		glColor3f(0.0,0.0,1.0);
		glRasterPos3f(-0.3,0,-0.1);
	}else{
		glColor3f(1.0,0.0,0.0);
		glRasterPos3f(1.1,0.8,-0.1);
	}

	sprintf_s(array, "%f", timePlay -currentTime);


	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'i');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'm');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'e');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'r');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ':');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ' ');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, array[0]);
	if(timePlay -currentTime >= 10)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, array[1]);

	glPopMatrix();

	glEnable(GL_LIGHTING);

	Texture * temp = new Texture("NULL");
	GameBoard->draw(temp);
	delete(temp);
}