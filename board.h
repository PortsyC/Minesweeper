#ifndef BOARD_H
#define BOARD_H

class Board
{
public:
	Board(int mines, int sizex, int sizey);
	~Board();
	void print();
	char getData(int x, int y);
	void moveToUIF(int x, int y);
	void checkEmptyField(int x, int y);
	int addToMinecount(int x, int y, int& minecount);
	int getGameStatus();
private:
	char** uif;
	char** data;
	const int sizeX;
	const int sizeY;
};

#endif
