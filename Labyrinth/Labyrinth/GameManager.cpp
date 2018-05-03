#include "GameManager.h"

void GameManager::init()
{
	maze.generateMaze();
	// �̷θ� ȭ�鿡 ���
	maze.printMaze(maze.getStartPoint());
}

// player: ������ �÷��̾�
void GameManager::run(Player* player)
{
	// ���� �÷��̾��� ��ǥ�� �̷��� ����������
	Point playerPoint = maze.getStartPoint();

	// ���� ��ŸƮ
	player->gameStart(playerPoint, Maze::HEIGHT, Maze::WIDTH);

	// 10000�� ���� �ش�.
	// 10000�� ���� �̷θ� ������ ���ϸ� ���� ����.
	int limitTurn = MAX_TURN;
	while (limitTurn--)
	{
		// �̷θ� ȭ�鿡 ���
		//maze.printMaze(playerPoint);


		// ������ �̵��� ��ǥ
		Point nextPoint;
		switch (player->nextMove())
		{
		case MOVE_LEFT:
			nextPoint = Point(playerPoint.getX(), playerPoint.getY() - 1);
			break;
		case MOVE_RIGHT:
			nextPoint = Point(playerPoint.getX(), playerPoint.getY() + 1);
			break;
		case MOVE_UP:
			nextPoint = Point(playerPoint.getX() - 1, playerPoint.getY());
			break;
		case MOVE_DOWN:
			nextPoint = Point(playerPoint.getX() + 1, playerPoint.getY());
			break;
		}

		// Ŭ����
		if (maze.isGoal(nextPoint))
		{
			break;
		}

		// �̵� �����ϸ�
		if (maze.ableToMove(nextPoint))
		{
			player->ableToMove(nextPoint, playerPoint);

			playerPoint = nextPoint;
		}
		// �̵��� �Ұ����ϸ� 
		else
		{
			player->notAbleToMove(playerPoint);
		}
	}


	// �̷θ� ȭ�鿡 ���
	//maze.printMaze(playerPoint);

	// ������ �� ������ ������ ���� Ŭ���� �� �ҿ�� �� ���
	if (limitTurn >= 0)
	{
		std::cout << MAX_TURN - limitTurn << "ȸ ���� �̷θ� Ŭ���� �ϼ̽��ϴ�! >,<" << std::endl;
	}
	// ���� ����
	else
	{
		std::cout << MAX_TURN << "ȸ �ȿ� �̷θ� Ŭ���� ���� ���ϼ̽��ϴ�! T^T" << std::endl;
	}


	delete player;
}
