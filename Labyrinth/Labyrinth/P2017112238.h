#pragma once
#include "Player.h"
#include "Maze.h"
#include "Constants.h"

using namespace std;


class P2017112238 :public Player
{
	Point point; //플레이어 위치
	int direction; //탐색할방향(가려고 했던곳이 알고보니 벽이였을경우 그 다음 방향부터 탐색하기위해 넣은 변수)
	int **visit; //위치에 따른 방문했던 횟수을 저장하기위한 2차원 배열(방문횟수가 적은곳을 찾아서감)
	Cell **wall; //위치에 따라 벽과 빈공간을 저장하기위한 2차원 배열
	bool novisit;// 재방문시 visit가 +1만 되게 하는 변수

public:
	P2017112238();
	void gameStart(Point player, int height, int width);
	Action nextMove();
	void ableToMove(Point point, Point prevPoint);
	void notAbleToMove(Point point);
	~P2017112238();//동적할당받았던 배열들 메모리 해제

};