#include "P2017112238.h"
using namespace std;

P2017112238::P2017112238()
{
}

//배열 동적할당및 여러가지 변수초기화
void P2017112238::gameStart(Point player, int height, int width)
{
	//visit, wall 배열 동적할당 및 초기화
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
	//시작위치의 방문횟수를 1로 변경시킴
	visit[player.getX()][player.getY()] = 1;
	//시작위치에 다시 들어가지않게 벽으로 취급
	wall[player.getX()][player.getY()] = WALL;
	//미로탐색을 위해 탐색할 방향을 초기화(0:좌, 1:상, 2:우, 3:하 (시계방향))
	direction = 0;
	//point의 x,y값을 시작위치로 초기화
	point = player;
	//방문 상태를 최초 방문으로 초기화(true:최초방문, false:재방문)
	novisit = true;
}

/*플레이어 이동함수
  처음에는 주어진 정보가 없으므로 일일이 이동시도해서 벽과 길 데이터 갱신
1.플레이어가 외곽벽에 붙어있을시 붙어있는 쪽의 외곽벽에 이동시도해서 GOAL이 있나 탐색.
2.좌측부터 시계방향으로 조건이 맞으면 플레이어 이동시도 (조건: 이동하려는 곳이 맵 밖이 아니고 최초방문이고 벽이 아닐것)
3.2번 단계에서 이동시도를 못했다면 현재위치에서 상하좌우가 모두 벽or이미 방문했던 곳이므로 현재위치의 방문횟수를 1더하고
  방문상태를 재방문으로 바꾼다음 다시 좌측부터 시계방향으로 조건이 맞으면 플레이어 이동시도 (조건: 이동하려는 곳이 맵 밖이 아니고 현재위치의 방문 횟수보다 이동하려는곳의 방문횟수가 작고 벽이 아닐것) */
Action P2017112238::nextMove()
{
	//1.goal이 있나 우선탐색(벽에 붙어있을시 이동시도해서 goal이 있나 먼저 탐색)
	//  2번 과정에서 탐색 방향이 무조건 좌측부터 시작이므로 굳이 1단계에서 좌측을 탐색할이유 없음(중복방지)
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

	//2.visit가 0일때 이동시도(이동가능조건: 이동하려는 곳이 맵 밖이 아님, 최초방문일것, 벽이 아닐것)
	direction = 0;
	for(int i=direction;i<4;i++)//만약 이동하려던 곳이 벽이였다면 다음 탐색방향부터 시작
		switch (i)
		{
		case 0://좌
			if (point.getY() == 0 || visit[point.getX()][point.getY() - 1] != 0 || wall[point.getX()][point.getY() - 1] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_LEFT;
			}
		case 1://상
			if (point.getX() == 0 || visit[point.getX() - 1][point.getY()] != 0 || wall[point.getX() - 1][point.getY()] == WALL)
				break;
			else {
				direction = 1;
				return Action::MOVE_UP;
			}
		case 2://우
			if (point.getY() == 50 || visit[point.getX()][point.getY() + 1] != 0 || wall[point.getX()][point.getY() + 1] == WALL)
				break;
			else {
				direction = 2;
				return Action::MOVE_RIGHT;
			}
		case 3://하
			if (point.getX() == 20 || visit[point.getX() + 1][point.getY()] != 0 || wall[point.getX() + 1][point.getY()] == WALL)
				break;
			else {
				direction = 3;
				return Action::MOVE_DOWN;
			}
		}

	//3.visit가 1이상일때 이동시도(이동가능조건: 이동하려는 곳이 맵 밖이 아님, 현재 좌표의 방문수보다 이동하려는 곳의 방문수가 적을것, 벽이 아닐것)
	visit[point.getX()][point.getY()]++;//현재위치 방문횟수 +1
	novisit=false;//방문상태를 재방문으로 변경

	for (int i = 0; i < 4; i++)
		switch (i)
		{
		case 0://좌
			if (point.getY() == 0 || visit[point.getX()][point.getY() - 1] >= visit[point.getX()][point.getY()] || wall[point.getX()][point.getY() - 1] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_LEFT;
			}
		case 1://상
			if (point.getX() == 0 || visit[point.getX() - 1][point.getY()] >= visit[point.getX()][point.getY()] || wall[point.getX() - 1][point.getY()] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_UP;
			}
		case 2://우
			if (point.getY() == 50 || visit[point.getX()][point.getY() + 1] >= visit[point.getX()][point.getY()] || wall[point.getX()][point.getY() + 1] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_RIGHT;
			}
		case 3://하
			if (point.getX() == 20 || visit[point.getX() + 1][point.getY()] >= visit[point.getX()][point.getY()] || wall[point.getX() + 1][point.getY()] == WALL)
				break;
			else {
				direction = 0;
				return Action::MOVE_DOWN;
			}
		}
}

//이동가능시 탐색방향 초기화(좌측), 방문상태에 따라 visit변경, 플레이어 좌표이동
void P2017112238::ableToMove(Point point, Point prevPoint)
{
	direction = 0;
	//최초방문일경우 이동한 위치의 visit +1
	if (novisit)
		visit[point.getX()][point.getY()]++;
	//재방문일경우 방문상태를 다시 최초방문으로 변경
	else
		novisit = true;
	this->point = point;
}

//이동불가시 가려고했던 좌표를 벽으로 변경
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

//동적할당받았던 배열들 메모리 해제
P2017112238::~P2017112238()
{
	for(int i=0;i<MAZE_HEIGHT;i++){
		delete[] visit[i];
		delete[] wall[i];
	}
	delete[] visit;
	delete[] wall;
}