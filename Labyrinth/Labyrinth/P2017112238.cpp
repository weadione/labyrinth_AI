#include "P2017112238.h"
using namespace std;

P2017112238::P2017112238()
{
}

//�迭 �����Ҵ�� �������� �����ʱ�ȭ
void P2017112238::gameStart(Point player, int height, int width)
{
	//visit, wall �迭 �����Ҵ� �� �ʱ�ȭ
	visit = new int*[height];
	wall = new Cell*[height];
	for (int i = 0; i < height; i++) {
		visit[i] = new int[width];
		wall[i] = new Cell[width];
		for (int j = 0; j < width; j++) {
			visit[i][j] = 0;
			wall[i][j] = SPACE;
		}
	}
	//������ġ�� �湮Ƚ���� 1�� �����Ŵ
	visit[player.getX()][player.getY()] = 1;
	//������ġ�� �ٽ� �����ʰ� ������ ���
	wall[player.getX()][player.getY()] = WALL;
	//�̷�Ž���� ���� Ž���� ������ �ʱ�ȭ(0:��, 1:��, 2:��, 3:�� (�ð����))
	direction = 0;
	//point�� x,y���� ������ġ�� �ʱ�ȭ
	point = player;
	//�湮 ���¸� ���� �湮���� �ʱ�ȭ(true:���ʹ湮, false:��湮)
	novisit = true;
}

/*�÷��̾� �̵��Լ�
  ó������ �־��� ������ �����Ƿ� ������ �̵��õ��ؼ� ���� �� ������ ����
1.�÷��̾ �ܰ����� �پ������� �پ��ִ� ���� �ܰ����� �̵��õ��ؼ� GOAL�� �ֳ� Ž��.
2.�������� �ð�������� ������ ������ �÷��̾� �̵��õ� (����: �̵��Ϸ��� ���� �� ���� �ƴϰ� ���ʹ湮�̰� ���� �ƴҰ�)
3.2�� �ܰ迡�� �̵��õ��� ���ߴٸ� ������ġ���� �����¿찡 ��� ��or�̹� �湮�ߴ� ���̹Ƿ� ������ġ�� �湮Ƚ���� 1���ϰ�
  �湮���¸� ��湮���� �ٲ۴��� �ٽ� �������� �ð�������� ������ ������ �÷��̾� �̵��õ� (����: �̵��Ϸ��� ���� �� ���� �ƴϰ� ������ġ�� �湮 Ƚ������ �̵��Ϸ��°��� �湮Ƚ���� �۰� ���� �ƴҰ�) */
Action P2017112238::nextMove()
{
	//1.goal�� �ֳ� �켱Ž��(���� �پ������� �̵��õ��ؼ� goal�� �ֳ� ���� Ž��)
	//  2�� �������� Ž�� ������ ������ �������� �����̹Ƿ� ���� 1�ܰ迡�� ������ Ž�������� ����(�ߺ�����)
	if (point.getX() == 1 && wall[point.getX() - 1][point.getY()] != WALL) {
		direction = 1;
		return Action::MOVE_UP;
	}
	else if (point.getY() == 49 && wall[point.getX()][point.getY() + 1] != WALL) {
		direction = 2;
		return Action::MOVE_RIGHT;
	}
	else if (point.getX() == 19  && wall[point.getX()+1][point.getY()] != WALL) {
		direction = 3;
		return Action::MOVE_DOWN;
	}

	//2.visit�� 0�϶� �̵��õ�(�̵���������: �̵��Ϸ��� ���� �� ���� �ƴ�, ���ʹ湮�ϰ�, ���� �ƴҰ�)
	direction = 0;
	for(int i=direction;i<4;i++)//���� �̵��Ϸ��� ���� ���̿��ٸ� ���� Ž��������� ����
		switch (i)
		{
		case 0://��
			if (point.getY() == 0 || visit[point.getX()][point.getY() - 1] != 0 || wall[point.getX()][point.getY() - 1] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_LEFT;
			}
		case 1://��
			if (point.getX() == 0 || visit[point.getX() - 1][point.getY()] != 0 || wall[point.getX() - 1][point.getY()] == WALL)
				break;
			else {
				direction = 1;
				return Action::MOVE_UP;
			}
		case 2://��
			if (point.getY() == 50 || visit[point.getX()][point.getY() + 1] != 0 || wall[point.getX()][point.getY() + 1] == WALL)
				break;
			else {
				direction = 2;
				return Action::MOVE_RIGHT;
			}
		case 3://��
			if (point.getX() == 20 || visit[point.getX() + 1][point.getY()] != 0 || wall[point.getX() + 1][point.getY()] == WALL)
				break;
			else {
				direction = 3;
				return Action::MOVE_DOWN;
			}
		}

	//3.visit�� 1�̻��϶� �̵��õ�(�̵���������: �̵��Ϸ��� ���� �� ���� �ƴ�, ���� ��ǥ�� �湮������ �̵��Ϸ��� ���� �湮���� ������, ���� �ƴҰ�)
	visit[point.getX()][point.getY()]++;//������ġ �湮Ƚ�� +1
	novisit=false;//�湮���¸� ��湮���� ����

	for (int i = 0; i < 4; i++)
		switch (i)
		{
		case 0://��
			if (point.getY() == 0 || visit[point.getX()][point.getY() - 1] >= visit[point.getX()][point.getY()] || wall[point.getX()][point.getY() - 1] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_LEFT;
			}
		case 1://��
			if (point.getX() == 0 || visit[point.getX() - 1][point.getY()] >= visit[point.getX()][point.getY()] || wall[point.getX() - 1][point.getY()] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_UP;
			}
		case 2://��
			if (point.getY() == 50 || visit[point.getX()][point.getY() + 1] >= visit[point.getX()][point.getY()] || wall[point.getX()][point.getY() + 1] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_RIGHT;
			}
		case 3://��
			if (point.getX() == 20 || visit[point.getX() + 1][point.getY()] >= visit[point.getX()][point.getY()] || wall[point.getX() + 1][point.getY()] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_DOWN;
			}
		}
}

//�̵����ɽ� Ž������ �ʱ�ȭ(����), �湮���¿� ���� visit����, �÷��̾� ��ǥ�̵�
void P2017112238::ableToMove(Point point, Point prevPoint)
{
	direction = 0;
	//���ʹ湮�ϰ�� �̵��� ��ġ�� visit +1
	if (novisit)
		visit[point.getX()][point.getY()]++;
	//��湮�ϰ�� �湮���¸� �ٽ� ���ʹ湮���� ����
	else
		novisit = true;
	this->point = point;
}

//�̵��Ұ��� �������ߴ� ��ǥ�� ������ ����
void P2017112238::notAbleToMove(Point point)
{
	switch (direction)
	{
	case 0:
		wall[point.getX()][point.getY() - 1] = WALL;
		break;
	case 1:
		wall[point.getX() - 1][point.getY()] = WALL;
		break;
	case 2:
		wall[point.getX()][point.getY() + 1] = WALL;
		break;
	case 3:
		wall[point.getX() + 1][point.getY()] = WALL;
		break;
	}
}

//�����Ҵ�޾Ҵ� �迭�� �޸� ����
P2017112238::~P2017112238()
{
	for(int i=0;i<MAZE_HEIGHT;i++){
		delete[] visit[i];
		delete[] wall[i];
	}
	delete[] visit;
	delete[] wall;
}