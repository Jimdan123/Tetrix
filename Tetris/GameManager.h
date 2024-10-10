#pragma once
#include "Tile.h"
#include "Board.h"
#include "BoardUI.h"
#include "GameConstant.h"

class GameManager
{
public:
	Board* board; 
	Tile* currentTile;
	Pos currentTilePos;
	int nextPiece;
	int gameState;
	GameManager();
	void start();
	bool dropTile();
	bool rotateLeft();
	bool rotateRight();
	bool moveLeft();
	bool moveRight();
	void gameLoop();
	bool checkLoseCondition();
	void restart();
	bool checkValidMove();
	void generateNewTile();
	void lose();
	void setState(GameState state);
};