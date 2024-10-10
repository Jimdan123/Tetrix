#include "GameManager.h"
#include <Windows.h>
#include <conio.h>

void GameManager::restart()
{
	board->reset();
}

bool GameManager::checkValidMove()
{
	for (int i = 0; i < TILE_ROW; i++)
	{
		for (int j = 0; j < TILE_COL; j++)
		{
			if (currentTile->getColorAt(i, j) != Color::EMPTY)
			{
				if (currentTilePos.y + j < 0 || currentTilePos.y + j >= BOARD_COL)
					return false;
			}
		}
	}
	return !board->checkCollision(currentTile, currentTilePos);
	/*
	TODO: Kiểm tra nước đi hiện tại có hợp lệ hay không?
	Hợp lệ nếu tile không vượt ra ngoài bàn chơi và không va chạm với tile khác.
	*/
	
	return true;
}

void GameManager::generateNewTile()
{ 
	srand(time(NULL));
	vector<Tile*> randomTile = { new Cube(), new Triangle(), new ZetLeft(), new ZetRight(), new LLeft(), new LRight(), new Line() };
	currentTile = randomTile[rand() % randomTile.size()];
	currentTile->init();
	currentTilePos.x = - TILE_ROW; 
	currentTilePos.y = BOARD_COL/ 2 - TILE_COL / 2;
	/*
	TODO: Tạo ra một tile mới, set vị trí bắt đầu cho tile
	*/
}

void GameManager::lose()
{
	setState(GameState::LOSE);
	board->notifyLose();
	char c = _getch();
	start();
}

void GameManager::setState(GameState state)
{
	this->gameState = state;
}

GameManager::GameManager()
{
	board = new Board();
}

void GameManager::start()
{
	restart();
	setState(GameState::PLAYING);
	generateNewTile();
	gameLoop();
}

bool GameManager::dropTile()
{
	/*
		Hàm cho currentTile rơi xuống
	*/
	Pos oldPos = currentTilePos; 
	currentTilePos = { currentTilePos.x + 1, currentTilePos.y};
	if (board->checkCollision(currentTile, currentTilePos)) // if collision
	{
		currentTilePos = oldPos;
		if (checkLoseCondition())
		{

			return false;
		}
		board->merge(currentTile, currentTilePos);
		generateNewTile();
	}
	return true;
}

bool GameManager::rotateLeft()
{
	for (int i = 0; i < 3; i++)
		currentTile->rotateRight(); 
		if (checkValidMove() == false)
		{
			for (int i = 0; i < 2; i++)
				currentTile->rotateRight();
			return false;
		}
	/*
	TODO: xoáy trái currentTile
	Cẩn thận trường hợp không thể xoay do:
		- Tile vượt ra khỏi bàn chơi.
		- Tile va chạm với tile khác.
	*/
	return true;
}

bool GameManager::rotateRight()
{
	currentTile->rotateRight(); 
	if (checkValidMove() == false)
	{
		for (int i = 0; i < 3; i++)
			currentTile->rotateRight();
		return false;
	}
	/*
	TODO: xoay phải currentTile
	*/
	return true;
}

bool GameManager::moveLeft()
{
	Pos oldPos = currentTilePos;
	currentTilePos = { currentTilePos.x , currentTilePos.y - 1 };
	if (checkValidMove() == false)
	{
		currentTilePos = oldPos;
		return false;
	}
	/*
	TODO: Di chuyển tile sang trái
	Cẩn thận trường hợp tương tự rotateLeft
	*/
	return true;
}

bool GameManager::moveRight()
{
	Pos oldPos = currentTilePos;
	currentTilePos = { currentTilePos.x , currentTilePos.y + 1 };
	if (checkValidMove() == false)
	{
		currentTilePos = oldPos;
		return false;
	}
	/*
	TODO: Di chuyển tile sang phải
	*/
	return true;
}

void GameManager::gameLoop()
{
	int time = 0;
	while (true)
	{
		if (gameState == GameState::PLAYING)
		{
			time += GAME_TICK;
			while (_kbhit())
			{
				char c = _getch();
				bool isValidAction = false;
				switch (c)
				{
				case 'a':
					isValidAction = moveLeft();
					break;
				case 'd':
					isValidAction = moveRight();
					break;
				case 'r':
					isValidAction = rotateRight();
					break;
				default:
					break;
				}
			}
			if (time >= TILE_DROP_TIME)
			{
				if (dropTile())
					board->updateGameScene(currentTile, currentTilePos);
				else
					lose();
				time -= TILE_DROP_TIME;
			}
			else
			{
				board->updateGameScene(currentTile, currentTilePos);
			}
			Sleep(GAME_TICK);
		}
		else if (gameState == GameState::LOSE)
		{
			break;
		}
		else if (gameState == GameState::PAUSE)
		{
			if (_kbhit())
			{
				_getch();
			}
		}
	}
}

bool GameManager::checkLoseCondition()
{
	for (int i = 0; i < TILE_ROW; i++)
	{
		for (int j = 0; j < TILE_COL; j++)
		{
			if (currentTile->getColorAt(i, j) != Color::EMPTY)
			{
				if (currentTilePos.x + i < 0 )
					return true;
			}
		}
	}
	/*
	TODO: Kiểm tra điều kiện thua
	Thua khi tile vượt quá chiều cao board
	*/
	return false;
}