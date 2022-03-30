#include "Bomberman.h"
#include "iostream"
using namespace std;

Bomberman::Bomberman()
{
	lives = 3;
	pos.setx(200);
	pos.sety(90);
	direction = 0;
	eat = false;
}
Bomberman::Bomberman(Point p)
{
	lives = 3;
	pos.setx(p.getx());
	pos.sety(p.gety());
	direction = 0;
	eat = false;
}

void Bomberman::moveright()
{
	if (canmove(pos.getx() + 60, pos.gety()))

		pos.setx(pos.getx() + 60);
	direction = 1;
}
void Bomberman::moveleft()
{
	if (canmove(pos.getx() - 60, pos.gety()))
		pos.setx(pos.getx() - 60);
	direction = 0;
}
void Bomberman::moveup()
{
	if (canmove(pos.getx(), pos.gety() + 60))
		pos.sety(pos.gety() + 60);
	direction = 2;
}
void Bomberman::movedown()
{
	if (canmove(pos.getx(), pos.gety() - 60))
		pos.sety(pos.gety() - 60);
	direction = 3;
}
bool Bomberman::canmove(int a, int b)
{
	if (a < 60 || a > 950 || b < 60 || b > 720)
		return false;
	return true;
}
void Bomberman::kill()
{
	lives = 0;
}
void Bomberman::resetlives()
{
	lives = 3;
}
void Bomberman::life_()
{
	lives--;
	pos.setx(200);
	pos.sety(90);
}
bool Bomberman::islive()
{
	if (lives > 0)
		return true;
	return false;
}

Bomberman::~Bomberman()
{
}
