#ifndef GAME_H
#define GAME_H

#include "Socket.h"
#include "Board.h"

using namespace std;

class Game
{
	Board* GameBoard;
	int player;

public:
	Game();
	~Game(void);
	void nextPlayer();
	void previousPlayer();
	Board* getBoard();

};

#endif