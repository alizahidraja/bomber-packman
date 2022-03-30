#include "Energizer.h"

Energizer::Energizer()
{

	present = true;
}

Energizer::Energizer(Point p)
{
	pos.setx(p.getx());
	pos.sety(p.gety());
	present = true;
}
void Energizer::consumed()
{
	present = false;
}
bool Energizer::isconsumed()
{
	pos.setx(0);
	pos.sety(0);
	return present;
}
Energizer::~Energizer()
{
}
