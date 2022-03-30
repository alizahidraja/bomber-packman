#include "Item.h"

Item::Item()
{
	pos.setx(0);
	pos.sety(0);
}
Item::Item(Point p)
{
	pos.setx(p.getx());
	pos.sety(p.gety());
}
Item::Item(int a, int b)
{
	pos.setx(a);
	pos.sety(b);
}
Point Item::getP()
{
	return pos;
}
void Item::setP(Point p)
{
	pos.setx(p.getx());
	pos.sety(p.gety());
}
void Item::setP(int a, int b)
{
	pos.setx(a);
	pos.sety(b);
}
Item::~Item()
{
}
