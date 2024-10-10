#pragma once

const int BOARD_ROW = 8;
const int BOARD_COL = 8;
const int TILE_ROW = 4;
const int TILE_COL = 4;
const int RANDOMBLOCK = 0;

enum GameState
{
	PLAYING,
	PAUSE,
	LOSE
};

enum Color
{
	EMPTY = 0,
	RED = 1,
	GREEN = 2,
	BLUE = 3
};

struct Pos
{
	int x, y;
};

const char BORDER = '*';
const int FPS = 60;
const int GAME_TICK = 1000 / FPS;
const int TILE_DROP_TIME = 150;