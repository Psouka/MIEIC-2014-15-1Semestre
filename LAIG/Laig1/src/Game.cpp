#include "Game.h"

Game::Game(){
	GameBoard = new Board();
	socket = new Socket();
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

	nextPlayer();
}


void Game::movePiece(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall){


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

	message << yi << ",";

	message << xf << ",";

	message << yf << ",";

	message << wall << "]";
	

	string response = this->socket->sendMessage(message.str());

	return response == "1.\r\n";
}