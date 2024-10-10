#include "Board.h"

Board::Board()
{
	boardUI = new BoardUI();
	grid = new int* [BOARD_ROW];
	for (int i = 0; i < BOARD_ROW; ++i)
	{
		grid[i] = new int[BOARD_COL];
	}
	reset();
}

void Board::reset()
{
	for (int i = 0; i < BOARD_ROW; ++i)
		for (int j = 0; j < BOARD_COL; ++j)
			grid[i][j] = Color::EMPTY;
}

bool Board::checkCollision(Tile* tile, Pos tilePos)
{
	/*
		TODO: Kiểm tra tile ở vị trí tilePos có va chạm với board không
		Nếu có return true, ngược lại return false
	*/
	for (int i = 0; i < TILE_ROW; i++)
	{
		for (int j = 0; j < TILE_COL; j++)
		{
			if (tile->getColorAt(i, j) != Color::EMPTY)
			{
				if (tilePos.x + i >= BOARD_ROW)
					return true;
			}
		}
	}
	for (int i = 0; i < TILE_ROW; i++)
	{
		for (int j = 0; j < TILE_COL; j++)
		{
			if (tile->getColorAt(i, j) != Color::EMPTY)
			{
				if (tilePos.x + i >= 0 && tilePos.x + i < BOARD_ROW  && tilePos.y + j >= 0 && tilePos.y + j < BOARD_COL)
				if (grid[tilePos.x + i][tilePos.y + j] != Color::EMPTY)
					return true;
			}
		}
	}
	return false;
}

void Board::merge(Tile* tile, Pos tilePos)
{
	for (int i = 0; i < TILE_ROW; i++)
	{
		for (int j = 0; j < TILE_COL; j++)
		{
			if (tile->getColorAt(i, j) != Color::EMPTY)
			{
				grid[tilePos.x + i][tilePos.y + j] = tile->getColorAt(i, j);
			}
		}
	}
	for (int i = BOARD_ROW - 1; i >= 0; i--)
	{
		bool fullRow = true;
		for (int j = BOARD_COL - 1; j >= 0; j--)
		{
			if (grid[i][j] == Color::EMPTY)
			{
				fullRow = false;
				break;
			}
		}
		if (fullRow == true)
			clearRow(i);
	}
	int bottomBoard = BOARD_ROW - 1;
	for (int i = BOARD_ROW - 1; i >= 0; i--)
	{
		// grid[bottomBoard] là một hàng rỗng thấp nhất (index lớn nhất)
		for (int j = 0; j < BOARD_COL; j++)
		{
			if (bottomBoard >= 0)
				grid[bottomBoard][j] = grid[i][j]; // quăng xuống
			if (bottomBoard != i)
				grid[i][j] = Color::EMPTY; // clear hàng i 
		}
		for (int j = 0; j < BOARD_COL; j++)
		{
			if (grid[bottomBoard][j] != Color::EMPTY)
			{
				bottomBoard -= 1;
				break;
			}
		}

	}

	/*
	TODO: Thêm tile vào board và remove những dòng full
	*/
}

void Board::clearRow(int indexRow)
{
	for (int i = 0; i < BOARD_COL; i++)
	{
		grid[indexRow][i] = Color::EMPTY;
	}
}

void Board::updateGameScene(Tile* tile, Pos tilePos)
{
	boardUI->drawBoard(grid, tile, tilePos);
}

void Board::notifyLose()
{
	boardUI->notifyLose();
}



