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
	bool endGame;
	bool undoDone;
	float currentTime;
public:
	int timePlay;
	int bot;
	Game();
	~Game(void);
	void nextPlayer();
	void previousPlayer();
	void newGame();
	void addPiece(unsigned int x,unsigned int y);
	void movePiece(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall);
	void playBot();
	bool checkPiece(unsigned int x,unsigned int y);
	bool checkMove(unsigned int xi,unsigned int yi,unsigned int xf,unsigned int yf,unsigned int wall);
	string checkGame();
	bool gameState();
	Board* getBoard();
	Socket* getSocket();
	bool isActive();
	void undo();
	int getPlayer();
	vector< vector<char> > getFutureBoard();
	string getboardString(vector< vector<char> > board);
	void update(unsigned long t);
	bool timePassed();

};

#endif