#pragma once
#include <vector>
#include "GameConstant.h"

using namespace std;

class Tile
{
public:
	int **grid; // change the blocks
	int direction;
	int color = Color::RED;
	
	void init();
	void rotateRight();	
	int getColorAt(int i, int j);
	virtual void addToGrid() = 0;
	
};
class Cube : public Tile
{
	void addToGrid()
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				grid[i][j] = color;
			}
		}
	}
};
class Triangle : public Tile
{
	void addToGrid()
	{
		grid[0][1] = color;
		for (int i = 0; i < 3; i++)
		{
			grid[1][i] = color; 
		}
	}
};
class Line : public Tile
{
	void addToGrid()
	{
		for (int i = 0; i < 4; i++)
			grid[i][0] = color;
	}
};
class ZetLeft : public Tile
{
	void addToGrid()
	{
		grid[0][1] = grid[0][2] = grid[1][0] = grid[1][1] = color;
	}
};
class ZetRight : public Tile
{
	void addToGrid()
	{
		grid[0][0] = grid[0][1] = grid[1][1] = grid[1][2] = color; 
	}
};
class LRight : public Tile
{
	void addToGrid()
	{
		grid[0][0] = grid[0][1] = grid[0][2] = grid[1][2]= color; 
	}
};
class LLeft : public Tile
{
	void addToGrid()
	{
		grid[0][0] = grid[0][1] = grid[0][2] = grid[1][0] = color;
	}
};
