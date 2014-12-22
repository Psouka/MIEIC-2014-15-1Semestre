#include "Game.h"

Game::Game(){
}

void Game::nextPlayer() {
	this->player++;
	this->player %= 2;
}

void Game::previousPlayer() {
	this->player--;
	this->player %= 2;
}