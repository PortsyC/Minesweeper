#include "board.h"
#include <iostream>
#include <time.h>
#include <cstdlib>


using namespace std;


Board::Board(int mines, int sizex, int sizey) : sizeX(sizex), sizeY(sizey)
{
	srand(time(NULL));
	
	uif = new char* [sizeX];
	data = new char* [sizeX];
	for(int i = 0; i < sizeX; i++){
		uif[i] = new char[sizeY];
		data[i] = new char[sizeY];
	}

	for(int y = 0; y < sizeY; y++)
	{
		for(int x = 0; x < sizeX; x++)
		{
			uif[x][y] =  '.';
			data[x][y] = '.';
		}
	}

	for(int i = 0; i < mines; i++)
	{
		int x, y;
		while(true)
		{
			x = rand() % sizeX;
			y = rand() % sizeY;
			if(data[x][y] != 'm')
			{
				data[x][y] = 'm';
				break;
			}
		}
	}

	for(int y = 0; y < sizeY; y++)
	{
		for(int x = 0; x < sizeX; x++)
		{
			if(data[x][y] != 'm')
			{
				int minecount = 0;
				addToMinecount(x - 1, y - 1, minecount);
				addToMinecount(x, y - 1, minecount);
				addToMinecount(x + 1, y - 1, minecount);
				addToMinecount(x - 1, y, minecount);
				addToMinecount(x + 1, y, minecount);
				addToMinecount(x - 1, y + 1, minecount);
				addToMinecount(x, y + 1, minecount);
				addToMinecount(x + 1, y + 1, minecount);
				char c = (char)(((int)'0')+minecount);
				data[x][y] = c;
			}
		}
	}
}

Board::~Board()
{
	for(int i = 0; i < sizeY; i++)
	{
		delete[] data[i];
		delete[] uif[i];
	}
	delete[] data;
	delete[] uif;
}


void Board::print()
{
	cout << endl << "   ";

	for(int i = 0; i < sizeX; i++)
	{
		cout << (char) (97 + i);
	}
	cout << endl << endl;

	for(int y = 0; y < sizeY; y++)
	{
		cout << (char) (97 + y) << "  ";
		for(int x = 0; x < sizeX; x++)
		{
			cout << uif[x][y];
		}
		cout << endl;
	}
	cout << endl;
}

char Board::getData(int x, int y)
{
	if(x < sizeX && y < sizeY && x >= 0 && y >= 0)
	{
		return data[x][y];
	}

	return 'o';

}

void Board::moveToUIF(int x, int y)
{
	uif[x][y] = data[x][y];
}


void Board::checkEmptyField(int x, int y)
{
	if(x >= 0 && y >= 0 && x < sizeX && y < sizeY)
	{
		if(data[x][y] == '0' && uif[x][y] == '.'){
			uif[x][y] = '0';
			checkEmptyField(x - 1, y - 1);
			checkEmptyField(x, y - 1);
			checkEmptyField(x + 1, y - 1);
			checkEmptyField(x - 1, y);
			checkEmptyField(x + 1, y);
			checkEmptyField(x -1, y + 1);
			checkEmptyField(x, y + 1);
			checkEmptyField(x + 1, y + 1);
		} else {
			moveToUIF(x, y);
		}
	}
}

int Board::addToMinecount(int x, int y, int& minecount){
	if(x >= 0 && x < sizeX && y >= 0 && y < sizeY)
	{
		if(data[x][y] == 'm') minecount++;
	}
	return 0;
}


int Board::getGameStatus()
{
	for(int y = 0; y < sizeY; y++)
	{
		for(int x = 0; x < sizeX; x++)
		{

			if(uif[x][y] == '.') {
				if(data[x][y] != 'm')
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
