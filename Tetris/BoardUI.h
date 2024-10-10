#pragma once
#include "GameConstant.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

class Board;
class Tile;
struct Pos;

class BoardUI
{
public:
	BoardUI();
	void notifyLose();
	void drawBoard(int** grid, Tile* tile, Pos tilePos);
};