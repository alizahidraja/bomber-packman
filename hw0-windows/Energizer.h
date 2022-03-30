#pragma once
#include "Item.h"
class Energizer : public Item
{
	bool present;

public:
	Energizer();
	Energizer(Point);
	void consumed();
	bool isconsumed();
	~Energizer();
};
