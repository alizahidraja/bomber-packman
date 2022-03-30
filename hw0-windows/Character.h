#pragma once
#include "Point.h"
class Character
{
protected:
	Point pos;

public:
	Character();
	Character(Point);
	Character(int, int);
	Point getP();
	void setP(Point);
	void setP(int, int);

	~Character();
};
