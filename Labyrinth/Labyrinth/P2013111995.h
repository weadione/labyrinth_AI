#pragma once
#include "Player.h"

class P2013111995 : public Player
{
public:
	P2013111995();
	void gameStart(Point player, int height, int width);
	Action nextMove();
	void ableToMove(Point point, Point prevPoint);
	void notAbleToMove(Point point);

private:
	Point point;
};