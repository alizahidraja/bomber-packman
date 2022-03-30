#pragma once
#include "Character.h"
class Bomberman : public Character
{
	int lives;

	bool eat;

public:
	int direction;
	void seteat(bool a) { eat = a; }
	bool geteat() { return eat; }
	Bomberman();
	Bomberman(Point);
	void moveright();
	void moveleft();
	void moveup();
	void movedown();
	bool canmove(int, int);
	void resetlives();
	void life_();
	bool islive();
	void kill();

	~Bomberman();
};
