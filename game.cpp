#include "game.h"
#include <iostream>

using namespace std;


Game::Game(int minecount, int sizeX, int sizey) : board(Board(minecount, sizeX, sizey))
{
	board.print();
}

Game::~Game()
{
}

int Game::update(int x, int y)
{
	if(board.getData(x, y) == 'm')
	{
		return -1;
	} else if(board.getData(x, y) == '0')
	{
		board.checkEmptyField(x, y);
	} else if(board.getData(x, y) == 'o'){
		
	}
	else {
		board.moveToUIF(x, y);
	}
	if(board.getGameStatus() == 1) {
		board.print();
		return 1;
	}

	cout << endl;

	board.print();
	return 0;
}
