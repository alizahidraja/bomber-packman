#include "Enemies.h"

Enemies::Enemies()
{
	alive = true;
	pos.setx(363);
	pos.sety(185);
}
Enemies::Enemies(Point p)
{
	alive = true;
	pos.setx(p.getx());
	pos.sety(p.gety());
}
void Enemies::moveright()
{
	if (canmove(pos.getx() + 60, pos.gety()))

		pos.setx(pos.getx() + 60);
}
void Enemies::moveleft()
{
	if (canmove(pos.getx() - 60, pos.gety()))
		pos.setx(pos.getx() - 60);
}
void Enemies::moveup()
{
	if (canmove(pos.getx(), pos.gety() + 60))
		pos.sety(pos.gety() + 60);
}
void Enemies::movedown()
{
	if (canmove(pos.getx(), pos.gety() - 60))
		pos.sety(pos.gety() - 60);
}
bool Enemies::canmove(int a, int b)
{
	if (a < 60 || a > 950 || b < 60 || b > 720)
		return false;
	return true;
}

bool Enemies::isalive()
{
	return alive;
}
void Enemies::life(Point p)
{
	// Point x(p.getx()-20, p.gety()+95);

	setP(p);
	alive = true;
}

void Enemies::DIE()
{
	setP(0, 0);

	alive = false;
}

Enemies::~Enemies()
{
}
