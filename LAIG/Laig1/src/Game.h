#ifndef GAME_H
#define GAME_H

#include "Socket.h"
#include "Board.h"

using namespace std;

class Game
{
	Board* GameBoard;
	Socket* socket;
	int player;

public:
	Game();
	~Game(void);
	void nextPlayer();
	void previousPlayer();
	void addPiece(unsigned int x,unsigned int y);
	void movePiece(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall);
	bool checkPiece(unsigned int x,unsigned int y);
	bool checkMove(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall);
	Board* getBoard();
	Socket* getSocket();

};

#endif