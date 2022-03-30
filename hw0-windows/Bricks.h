#pragma once
#include "Item.h"
class Bricks : public Item
{
	enum colors
	{
		NILL = 0,
		SILVER = 1,
		GREEN = 2,
		RED = 3
	};
	int brick;

public:
	static int unbreakable;
	static int total;
	Bricks();
	static void unb() { unbreakable++; }
	static void tot() { total++; }
	static int getunb() { return unbreakable; }
	static int gettot() { return total; }
	static void unb_() { unbreakable--; }
	int getbrick();

	void setbrick(int);

	~Bricks();
};
