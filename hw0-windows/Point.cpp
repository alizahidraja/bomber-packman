#include "Point.h"
#include "iostream"
using namespace std;

Point::Point()
{
	x = 80;
	y = 80;
	go = NULL;
}
Point::Point(int a, int b)
{
	x = a;
	y = b;
}
bool Point::operator==(Point p)
{
	bool equalx = false;
	bool equaly = false;
	for (int i = x - 30; i < x + 30; i++)
	{

		if (i == p.getx())
			equalx = true;
	}
	for (int i = y - 30; i < y + 30; i++)
	{
		if (i == p.gety())
			equaly = true;
	}
	if (equalx && equaly)
		return true;
	return false;
}

bool Point::isgo()
{
	return go;
}
void Point::setgo(bool a)
{
	go = a;
}
int Point::getx()
{
	return x;
}
int Point::gety()
{
	return y;
}
void Point::setx(int a)
{
	x = a;
}
void Point::sety(int b)
{
	y = b;
}
Point::~Point()
{
}
