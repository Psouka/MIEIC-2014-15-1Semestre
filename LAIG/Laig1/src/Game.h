#ifndef GAME_H
#define GAME_H

#include "Socket.h"
#include "Primitives.h"

using namespace std;

class Game
{
	Board GameBoard;
	int player;

public:
	Game();
	void nextPlayer();
	void previousPlayer();

};

#endif