#pragma once
#include "Point.h"
class Item
{
protected:
	Point pos;

public:
	Item();
	Item(Point);
	Item(int, int);
	Point getP();
	void setP(Point);
	void setP(int, int);

	~Item();
};
