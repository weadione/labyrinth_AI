#pragma once
#include "Player.h"
#include "Maze.h"
#include "Constants.h"

using namespace std;


class P2017112238 :public Player
{
	Point point; //�÷��̾� ��ġ
	int direction; //Ž���ҹ���(������ �ߴ����� �˰��� ���̿������ �� ���� ������� Ž���ϱ����� ���� ����)
	int **visit; //��ġ�� ���� �湮�ߴ� Ƚ���� �����ϱ����� 2���� �迭(�湮Ƚ���� �������� ã�Ƽ���)
	Cell **wall; //��ġ�� ���� ���� ������� �����ϱ����� 2���� �迭
	bool novisit;// ��湮�� visit�� +1�� �ǰ� �ϴ� ����

public:
	P2017112238();
	void gameStart(Point player, int height, int width);
	Action nextMove();
	void ableToMove(Point point, Point prevPoint);
	void notAbleToMove(Point point);
	~P2017112238();//�����Ҵ�޾Ҵ� �迭�� �޸� ����

};