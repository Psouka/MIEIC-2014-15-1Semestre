#include "Game.h"

Game::Game(){
	GameBoard = new Board();
	socket = new Socket();
	player = 1;
}

void Game::nextPlayer() {
	this->player++;
	this->player %= 2;
}

void Game::previousPlayer() {
	this->player--;
	this->player %= 2;
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
	GameBoard->playerPlay.active = true;
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

	nextPlayer();
}


void Game::movePiece(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall){
	GameBoard->playerPlay.active = true;
	GameBoard->playerPlay.wall = wall;

	delete(GameBoard->playerPlay.animPiece);

	vector<vector<float>> cPoint;
	vector<float> point(3);
	point[0] = 0;
	point[1] = 0;
	point[2] = 0;
	cPoint.push_back(point);
	point[0] = 0;
	point[1] = 0;
	point[2] = -0.5;
	cPoint.push_back(point);
	point[0] = xf-xi;
	point[1] = yf-yi;
	point[2] = -0.5;
	cPoint.push_back(point);
	point[0] = xf-xi;
	point[1] = yf-yi;
	point[2] = 0;
	cPoint.push_back(point);

	GameBoard->playerPlay.animPiece = new LinearAnimation("Piece",1.5, cPoint);

	delete(GameBoard->playerPlay.animWall);
	GameBoard->playerPlay.animWall = new NoAnimation();

	GameBoard->playerPlay.Player = GameBoard->getPalyerApp(this->player%2);

	GameBoard->playerPlay.col = xi;
	GameBoard->playerPlay.line = yi;


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

	message << to_string(xi) << ",";

	message <<  to_string(yi) << ",";

	message <<  to_string(xf) << ",";

	message <<  to_string(yf) << ",";

	message << to_string(wall)  << "]";
	

	string response = this->socket->sendMessage(message.str());

	return response == "1.\r\n";
}