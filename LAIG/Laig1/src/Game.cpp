#include "Game.h"

Game::Game(){
	GameBoard = new Board();
	socket = new Socket();
	player = 1;
	endGame = false;
	undoDone = false;
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
	player = 1;
	GameBoard->resetBoard();
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

void Game::checkGame(){

	stringstream message;

	message << "[gameOver, ";
	message << GameBoard->getBoardString();
	message <<  "]";
	

	string response = this->socket->sendMessage(message.str());

 if(response.find("0") == string::npos)
 {
	 cout << "\nThe winner is the player " << response.at(1) << ".";
	 endGame = true;
 }
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
	}
}