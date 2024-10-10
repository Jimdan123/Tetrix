#pragma once
#include "BoardUI.h"
#include "GameConstant.h"
#include "Tile.h"

class Board
{
public:
	int **grid;
	BoardUI* boardUI;

	Board();
	void reset();
	bool checkCollision(Tile* tile, Pos tilePos);
	void merge(Tile* tile, Pos tilePos);
	void clearRow(int indexRow);
	void updateGameScene(Tile* tile, Pos tilePos);
	void notifyLose();
};