#pragma once
#include "Character.h"
class Enemies : public Character
{

	bool alive;

public:
	Enemies();
	Enemies(Point);
	void moveright();
	void moveleft();
	void moveup();
	void movedown();
	bool canmove(int, int);
	bool isalive();
	void life(Point);
	void DIE();
	~Enemies();
};
