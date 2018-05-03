#include "Maze.h"
#include "MazeGenerator.h"

void Maze::printMaze(const Point & player) const
{
	//system("cls");
	for (int x = 0; x < HEIGHT; x++)
	{
		for (int y = 0; y < WIDTH; y++)
		{
			// ���̸� ���� �簢�� ���
			if (map[x][y] == WALL)
			{
				std::cout << "��";
			}
			//  �̷� �ⱸ�̸� ��Ʈ ���
			else if (map[x][y] == GOAL)
			{
				std::cout << "��";
			}
			// �÷��̾� ��ġ�� �� ���
			else if (player.getX() == x && player.getY() == y)
			{
				std::cout << "��";
			}
			// �� �����̸� �׳� ���� ���
			else
			{
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}

void Maze::generateMaze()
{
	// �̷� �������� ����
	MazeGenerator mazeGenerator;
	mazeGenerator.generate(map[0], WIDTH, HEIGHT);

	// �������� ������ ����
	int isStart = rand() % 2;
	for (int x = 0; x < HEIGHT; x++)
	{
		for (int y = 0; y < WIDTH; y++)
		{
			// �ܰ��� ������ �� ������ ����
			if ((x == 0 || x == HEIGHT - 1 || y == 0 || y == WIDTH - 1) && map[x][y] == Cell::SPACE)
			{
				if (isStart == 0)
				{
					map[x][y] = Cell::GOAL;
					isStart = 1 - isStart;
				}
				else
				{
					startPoint = Point(x, y);
					isStart = 1 - isStart;
				}
			}
		}
	}
}

Point Maze::getStartPoint() const
{
	return startPoint;
}

bool Maze::ableToMove(const Point & point) const
{
	// ���� üũ
	if (point.getX() < 0 || point.getX() >= HEIGHT || point.getY() < 0 || point.getY() >= WIDTH)
	{
		return false;
	}
	return map[point.getX()][point.getY()] == Cell::SPACE;
}

bool Maze::isGoal(const Point & point) const
{
	// ���� üũ
	if (point.getX() < 0 || point.getX() >= HEIGHT || point.getY() < 0 || point.getY() >= WIDTH)
	{
		return false;
	}
	return map[point.getX()][point.getY()] == Cell::GOAL;
}
