#include "P2013111995.h"

P2013111995::P2013111995()
{
}

void P2013111995::gameStart(Point player, int height, int width)
{
	//std::cout << "���� ��ġ" << player << ' ' << height << ' ' << width << std::endl;
}

Action P2013111995::nextMove()
{
	// �����ϰ� �̵�
	switch (rand()%4)
	{
	case 0:
		return Action::MOVE_DOWN;
	case 1:
		return Action::MOVE_UP;
	case 2:
		return Action::MOVE_LEFT;
	case 3:
		return Action::MOVE_RIGHT;
	}
}

void P2013111995::ableToMove(Point point, Point prevPoint)
{
	//std::cout << point << "����" << prevPoint <<std::endl;
}

void P2013111995::notAbleToMove(Point point)
{
	//std::cout << point << "�Ұ�" << std::endl;
}
