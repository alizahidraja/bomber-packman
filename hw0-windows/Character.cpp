#include "Character.h"

Character::Character()
{
	pos.setx(0);
	pos.sety(0);
}
Character::Character(Point p)
{
	pos.setx(p.getx());
	pos.sety(p.gety());
}
Character::Character(int a, int b)
{
	pos.setx(a);
	pos.sety(b);
}
Point Character::getP()
{
	return pos;
}
void Character::setP(Point p)
{
	pos.setx(p.getx());
	pos.sety(p.gety());
}
void Character::setP(int a, int b)
{
	pos.setx(a);
	pos.sety(b);
}
Character::~Character()
{
}
