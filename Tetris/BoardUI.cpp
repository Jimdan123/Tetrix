#include "BoardUI.h"
#include "Board.h"
#include "Tile.h"
#include "GameManager.h"

BoardUI::BoardUI()
{
}

void BoardUI::notifyLose()
{
	cout << "\n\nYOU LOSEEEEEEEEE :'>";
}

void drawColor(int color)
{
	if (color == Color::EMPTY)
	{
		cout << ' ';
	}
	else
	{
		if (color == BORDER)
			cout << char(color);
		else
			cout << color;
	}
}

void BoardUI::drawBoard(int** grid, Tile* tile, Pos tilePos)
{
	system("cls");
	for (int i = -1; i <= BOARD_ROW; ++i)
	{
		for (int j = -1; j <= BOARD_COL; ++j)
		{
			if (i == -1 || j == -1 || i == BOARD_ROW || j == BOARD_COL)
			{
				drawColor(BORDER);
				continue;
			}
			else
			{
				if (grid[i][j] != Color::EMPTY)
				{
					drawColor(grid[i][j]);
					continue;
				}
				else
				{
					if (tilePos.x <= i && i < tilePos.x + TILE_ROW && tilePos.y <= j && j < tilePos.y + TILE_COL)
					{
						if (tile->getColorAt(i - tilePos.x, j - tilePos.y) != Color::EMPTY)
						{
							drawColor(tile->getColorAt(i - tilePos.x, j - tilePos.y));
							continue;
						}
					}
					drawColor(Color::EMPTY);
				}
			}
		}
		
		if (i != BOARD_ROW)
		{
			cout << "\n";
		}
	}
}
