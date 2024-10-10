#include "Tile.h"
#include <iostream>

using namespace std;

void Tile::init()
{
	grid = new int* [TILE_ROW];
	for (int i = 0; i < TILE_ROW; ++i)
	{
		grid[i] = new int[TILE_COL];
	}

	for (int i = 0; i < TILE_ROW; ++i)
	{
		for (int j = 0; j < TILE_COL; ++j)
		{
			grid[i][j] = Color::EMPTY;
		}
	}
	 addToGrid();
	//grid[0][2] = grid[1][2] = grid[2][2] = grid[3][2] = color;
}

void Tile::rotateRight()
{
	int** store; 
	store = new int* [TILE_ROW];
	for (int i = 0; i < TILE_ROW; ++i)
	{
		store[i] = new int[TILE_COL];
	}
	for (int i = 0; i < TILE_ROW; i++)
	{
		for (int j = 0; j < TILE_COL; j++)
		{
			store[i][j] = grid[i][j];
		}
	}
	for (int i = 0; i < TILE_ROW; i++)
	{
		int k = TILE_ROW - 1;
		for (int j = 0; j < TILE_COL; j++)
		{
			grid[i][j] = store[k][i];
			k -= 1;
		}
	}

	/*
	TODO: Xoay grid sang phải
	*/
}

int Tile::getColorAt(int i, int j)
{
	if (i < 0 || j < 0 || i >= TILE_ROW || j >= TILE_COL)
	{
		return Color::EMPTY;
	}
	return grid[i][j];
	//return Color::EMPTY;
}
