#include "Bomb.h"
#include "util.h"
#include <iostream>
using namespace std;

Bomb::Bomb()
{
	pos.setx(0);
	pos.sety(0);
	active = NULL;
	exploded = NULL;
}
Bomb::Bomb(Point p)
{
	pos.setx(p.getx());
	pos.sety(p.gety());
	active = NULL;
	exploded = NULL;
}

void Bomb::activate()
{
	active = true;
	tick = 2;
}
void Bomb::ticker()
{
	tick--;
	if (tick == 0)
	{
		exploded = true;
		active = false;
	}
}
bool Bomb::isactive()
{
	return active;
}
bool Bomb::isexploded()
{
	return exploded;
}

void Bomb::explode()
{
	DrawCircle(pos.getx(), pos.gety(), 70, colors[23]);

	exploded = false;
}

Bomb::~Bomb()
{
}
