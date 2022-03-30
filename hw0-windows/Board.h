/*
 * Board.h
 *
 *  Created on: May 2, 2014
 *      Author: Ali Zahid Raja
 */
#ifndef _BOARD_H_
#define _BOARD_H_

//#include <GL/glut.h>
#include "Bomb.h"
#include "Bricks.h"
#include "Enemies.h"
#include <iostream>
#include "Bomberman.h"
#include "util.h"
#include "Energizer.h"
using namespace std;
class Board
{
private:
	int xcellsize, ycellsize;
	int width, height;
	ColorNames pcolor, bcolor, gcolor;
	int Score;
	Bomb bomb;
	Bomberman B;
	Enemies E[4];
	bool once, twice;
	bool pause;
	Energizer G[10];

public:
	bool checkbrick(Bricks[]);

	Bricks Brick[193];
	int game[17][13];
	Bomb &getbomb()
	{
		return bomb;
	}
	Bomberman &getbomberman()
	{
		return B;
	}
	Enemies &getblinky()
	{
		return E[0];
	}
	Enemies &getpinky()
	{
		return E[1];
	}
	Enemies &getinky()
	{
		return E[2];
	}
	Enemies &getclyde()
	{
		return E[3];
	}
	Energizer &getgift1()
	{
		if (G[0].isconsumed())
			G[0].setP(440, 450);
		return G[0];
	}
	Energizer &getgift2()
	{
		if (G[1].isconsumed())
			G[1].setP(440, 90);
		return G[1];
	}
	Energizer &getgift3()
	{
		if (G[2].isconsumed())
			G[2].setP(680, 270);
		return G[2];
	}
	Energizer &getgift4()
	{
		if (G[3].isconsumed())
			G[3].setP(860, 330);
		return G[3];
	}
	Energizer &getgift5()
	{
		if (G[4].isconsumed())
			G[4].setP(320, 330);
		return G[4];
	}
	Energizer &getgift6()
	{
		if (G[5].isconsumed())
			G[5].setP(320, 690);
		return G[5];
	}
	Energizer &getgift7()
	{
		if (G[6].isconsumed())
			G[6].setP(740, 690);
		return G[6];
	}
	Energizer &getgift8()
	{
		if (G[7].isconsumed())
			G[7].setP(920, 90);
		return G[7];
	}
	Energizer &getgift9()
	{
		if (G[8].isconsumed())
			G[8].setP(80, 270);
		return G[8];
	}
	Energizer &getgift0()
	{
		if (G[9].isconsumed())
			G[9].setP(200, 570);
		return G[9];
	}

	void BFS();
	void explodebricks(Point);
	void ENDGAME();
	void Scorer(int);
	int Scorer() { return Score; }
	int directions[13][17];
	bool getp() { return pause; }
	void setp(bool a) { pause = a; }

	static const int BOARD_X;
	static const int BOARD_Y;
	Board(int xsize = 8, int ysize = 8);

	~Board(void);
	void InitalizeBoard(int, int);
	// draw the board
	void Draw();

	static int GetBoardX()
	{
		return BOARD_X;
	}
	static int GetBoardY()
	{
		return BOARD_Y;
	}

	int GetMidX()
	{
		return BOARD_X * xcellsize / 2.0;
	}
	int GetMidY()
	{
		return BOARD_Y * ycellsize / 2.0;
	}
	int GetCellSize()
	{
		return xcellsize;
	}
	void GetInitBombermanPosition(int &x, int &y)
	{
		x = xcellsize + xcellsize / 2;
		y = ycellsize + ycellsize / 2;
	}

	void GetInitTextPosition(int &x, int &y);
	void GetInitPinkyPosition(int &x, int &y);
	//	int GetMidx
};

#ifdef WITH_TEXTURES
void RegisterTextures();
#endif

#endif
