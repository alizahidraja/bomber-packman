#pragma once
#include "Item.h"
class Bomb : public Item
{
	bool active;
	bool exploded;
	int tick;

public:
	Bomb();
	Bomb(Point);
	void activate();
	void ticker();
	bool isactive();
	void explode();
	bool isexploded();

	~Bomb();
};
