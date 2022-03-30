/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Ali Zahid Raja
 */
/*
 * Board.cpp
 *
 *  Created on: May 2, 2014
 *      Author: Ali Zahid Raja
 */
#include <deque>
using namespace std;
#include "Board.h"
#include <cstdio>
const int Board::BOARD_X = 17;
const int Board::BOARD_Y = 14;
// here's Bomberman's crazy board

// Note that all these enum constants from NILL onwards
// have been given numbers in increasing order
// e.g. NILL=0, and so on
// and these numbers are represented in the board array...
enum BoardParts
{
	NILL = 0,
	S_BRICK = 1,
	G_BRICK = 2,
	R_BRICK = 3
};
// defining some utility functions...

static int board_array[Board::BOARD_Y][Board::BOARD_X] = {{0}};

#ifdef WITH_TEXTURES
const int nbricks = 3;

GLuint texture[nbricks];
GLuint tid[nbricks];
string tnames[] = {"solid.png", "brick.png", "brick-green.png"};
GLuint mtid[nbricks];
int cwidth = 60, cheight = 60; // 60x60 pixels bricks...

void RegisterTextures()
/*Function is used to load the textures from the
 * files and display*/
{
	// allocate a texture name
	glGenTextures(nbricks, tid);

	vector<unsigned char> data;
	// ofstream ofile("image-data.bin", ios::binary | ios::out);
	//  now load each bricks data...

	for (int i = 0; i < nbricks; ++i)
	{

		// Read current brick

		ReadImage(tnames[i], data);
		if (i == 0)
		{
			int length = data.size();
			// ofile.write((char*) &length, sizeof(int));
		}
		// ofile.write((char*) &data[0], sizeof(char) * data.size());

		cout << " Texture Id=" << tid[i] << endl;
		mtid[i] = tid[i];
		// select our current texture
		glBindTexture(GL_TEXTURE_2D, tid[i]);

		// select modulate to mix texture with color for shading
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
						GL_LINEAR_MIPMAP_NEAREST);
		// when texture area is large, bilinear filter the first MIP map
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		bool wrap = true;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
						wrap ? GL_REPEAT : GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
						wrap ? GL_REPEAT : GL_CLAMP);

		// build our texture MIP maps
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, cwidth, cheight, GL_RGB,
						  GL_UNSIGNED_BYTE, &data[0]);
	}
	// ofile.close();
}
void Drawbrick(const BoardParts &cname, float fx, float fy, float fwidth,
			   float fheight)
/*Draws a specfic brick at given position coordinate
 * sx = position of x-axis from left-bottom
 * sy = position of y-axis from left-bottom
 * cwidth= width of displayed brick in pixels
 * cheight= height of displayed bricki pixels.
 * */
{

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mtid[cname - 1]);
	//	glTranslatef(0, 0, 0);
	//	glRotatef(-M_PI / 2, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2d(fx, fy);
	glTexCoord2d(1.0, 0.0);
	glVertex2d(fx + fwidth, fy);
	glTexCoord2d(1.0, 1.0);
	glVertex2d(fx + fwidth, fy + fheight);
	glTexCoord2d(0.0, 1.0);
	glVertex2d(fx, fy + fheight);
	glEnd();

	glColor4f(1, 1, 1, 1);

	//	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// glutSwapBuffers();
}
#endif
// Destructor
Board::~Board(void)
{
}
void Board::InitalizeBoard(int w, int h)
{
	Score = 0;
	width = w;
	height = h;
	for (int i = 0; i < BOARD_Y - 1; ++i)
	{
		for (int j = 0; j < BOARD_X; ++j)
		{
			if (i == 0 || i == BOARD_Y - 2 || j == 0 || j == BOARD_X - 1)
				board_array[i][j] = S_BRICK;
			else if (i % 2 == 0 && j % 2 == 0)
				board_array[i][j] = S_BRICK;
			else
				board_array[i][j] =
					(GetRandInRange(0, 10)) < 8 ? NILL : (GetRandInRange(0, 10)) < 8 ? G_BRICK
																					 : R_BRICK;
		}
	}

	/*for (int i = 0; i < BOARD_Y - 1; ++i) {
		for (int j = 0; j < BOARD_X; ++j) {
			switch (board_array[i][j])
			{
			case NILL:
				game[i][j] = 0;
				break;
			case S_BRICK:
				game[i][j] = 1;
				break;
			case G_BRICK:
				game[i][j] = 2;
				break;
			case R_BRICK:
				game[i][j] = 3;
				break;
			}
		}

	}
	*/
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++)
			if (board_array[i][j] == R_BRICK || board_array[i][j] == G_BRICK)
			{
				Bricks::unb();
				Bricks::tot();
			}
	E[1].setP(780, 365);
	E[2].DIE();
	E[3].DIE();
	once = true;
	twice = true;
}
// Constructor
Board::Board(int xsize, int ysize)
{
	xcellsize = xsize;
	ycellsize = ysize;
	pcolor = CHOCOLATE;
	bcolor = ORANGE_RED;
	gcolor = PINK;

	// set up board
}

void Board::Draw()
{
	glColor3f(0, 0, 1);
	glPushMatrix();

	//	cout<<"F";
#ifdef WITH_TEXTURES

	for (int i = BOARD_Y - 2, y = 0; i >= 0; --i, y += xcellsize)
	{
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize))
		{
			// cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j])
			{
			case NILL:

				// Empty space
				break;
			case S_BRICK:
			case G_BRICK:
			case R_BRICK:
			defualt:
				s.go = false;
				float fwidth = (float)(xcellsize) / width * 2, fheight =
																   (float)ycellsize / height * 2;
				float fx = (float)(x - 10) / width * 2 - 1, fy = (float)y / height * 2 - 1;

				/*Drawbrick((BoardParts) board_array[i][j], fx, fy, fwidth,
				fheight);*/
				Drawbrick((BoardParts)board_array[i][j], (float)x / width - 1, (float)y / height - 1, fwidth,
						  fheight);
				break;
			}
		}
	}
#else
	//	cout << BOARD_Y << " " << BOARD_X;
	for (int i = 0, y = 0; i < BOARD_Y - 1; ++i, y += xcellsize)
	{
		for (int j = 0, x = 0; j < BOARD_X; j++, x += (ycellsize))
		{
			//			cout << " " << board_array[i][j] << " " << flush;
			switch (board_array[i][j])
			{
			case NILL:
				game[j][i] = 0;

				// B.getP().setgo(true);
				//  Empty space
				Brick[i + j].setbrick(0);
				break;
			case S_BRICK:
				game[j][i] = 1;
				Brick[i + j].setbrick(1);
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
							  colors[SLATE_GRAY]);
				DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[GRAY]);
				DrawLine(x + 50, y + 60, x - 10 + ycellsize, y, 4, colors[GRAY]);
				DrawLine(x + 50, y + 60, x - 10, y + 60, 4, colors[GRAY]);
				DrawLine(x - 10, y, x - 10, y + 60, 4, colors[GRAY]);
				// B.getP().setgo(false);

				break;
			case G_BRICK:
				game[j][i] = 2;
				Brick[i + j].setbrick(2);
				DrawRectangle(x - 10, y, ycellsize, xcellsize,
							  colors[LIGHT_GREEN]);
				DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[GREEN]);
				DrawLine(x + 50, y + 60, x - 10 + ycellsize, y, 4, colors[GREEN]);
				DrawLine(x + 50, y + 60, x - 10, y + 60, 4, colors[GREEN]);
				DrawLine(x - 10, y, x - 10, y + 60, 4, colors[GREEN]);
				// B.getP().setgo(false);
				break;
			case R_BRICK:
				game[j][i] = 3;
				Brick[i + j].setbrick(3);
				DrawRectangle(x - 10, y, ycellsize, xcellsize, colors[RED]);
				DrawLine(x - 10, y, x - 10 + ycellsize, y, 4, colors[RED]);
				DrawLine(x + 50, y + 60, x - 10 + ycellsize, y, 4, colors[RED]);
				DrawLine(x + 50, y + 60, x - 10, y + 60, 4, colors[RED]);
				DrawLine(x - 10, y, x - 10, y + 60, 4, colors[RED]);
				// B.getP().setgo(false);
				break;
				// default:
				// B.getP().setgo(false);
			}
		} // cout << endl;
	}

	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++)
			if (game[i][j] == 0)
				directions[i][j] = -2;
			else
				directions[i][j] = -3;
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 17; j++)
			switch (board_array[i][j])
			{
			case NILL:
				Brick[i + j].setbrick(0);
				break;
			case S_BRICK:
				Brick[i + j].setbrick(1);
				break;
			case G_BRICK:
				Brick[i + j].setbrick(2);

				break;
			case R_BRICK:
				Brick[i + j].setbrick(3);
			}

	if (Bricks::getunb() < Bricks::gettot() - Bricks::gettot() * 30 / 100.0 && once)
	{
		once = false;
		Point p(getbomberman().getP().getx(), getbomberman().getP().gety() + 95);
		while (p.gety() > 720)
		{
			p.sety(getbomberman().getP().gety() - 95);
			while (board_array[p.gety() / 60 + 1][p.getx() / 60] != NILL)
			{
				p.setx(p.getx() - 60);
				while (p.getx() < 60)
				{
					while (board_array[p.gety() / 60 + 1][p.getx() / 60] != NILL)
						p.setx(p.getx() + 60);
				}
			}
		}

		getinky().life(p);
	}

	if (Bricks::getunb() < Bricks::gettot() - Bricks::gettot() * 70 / 100.0 && twice)
	{
		twice = false;
		Point p(getbomberman().getP().getx(), getbomberman().getP().gety() + 95);
		while (p.gety() > 720)
		{
			p.sety(getbomberman().getP().gety() - 95);
			while (board_array[p.gety() / 60 + 1][p.getx() / 60] != NILL)
			{
				p.setx(p.getx() - 60);
				while (p.getx() < 60)
				{
					while (board_array[p.gety() / 60 + 1][p.getx() / 60] != NILL)
						p.setx(p.getx() + 60);
				}
			}
		}
		getclyde().life(p);
	}

#endif
	glPopMatrix();
}

void Board::GetInitPinkyPosition(int &x, int &y)
{
	x = xcellsize * 3;
	y = (BOARD_Y - 3) * ycellsize;
}
void Board::GetInitTextPosition(int &x, int &y)
{
	x = xcellsize;
	y = (BOARD_Y - 1) * ycellsize + ycellsize / 2;
}
void Board::ENDGAME()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clean the screen and the depth buffer
	glLoadIdentity();
	glClearColor(0 /*Red Component*/, 0,						 // 148.0/255/*Green Component*/,
				 0.0 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);								 // Update the colors
	DrawString(400, 600, "THE END!", colors[5]);
	DrawString(400, 500, "Your Score is: " + Num2Str(Score), colors[5]);
	glutSwapBuffers();
}
void Board::Scorer(int a)
{
	Score += a;
}

void Board::explodebricks(Point p)
{
	if (p == B.getP())
		B.life_();
	if (p == E[0].getP())
	{
		E[0].DIE();
		Score += 200;
	}
	if (p == E[1].getP())
	{
		E[1].DIE();
		Score += 200;
	}
	if (p == E[2].getP())
	{
		E[2].DIE();
		Score += 200;
	}
	if (p == E[3].getP())
	{
		E[3].DIE();
		Score += 200;
	}
	if (board_array[p.gety() / 60 + 1][p.getx() / 60] != S_BRICK)
	{
		Point x(p.getx(), p.gety() + 60);
		if (x == B.getP())
			B.life_();
		if (x == E[0].getP())
		{
			E[0].DIE();
			Score += 200;
		}
		if (x == E[1].getP())
		{
			E[1].DIE();
			Score += 200;
		}
		if (x == E[2].getP())
		{
			E[2].DIE();
			Score += 200;
		}
		if (x == E[3].getP())
		{
			E[3].DIE();
			Score += 200;
		}
		if (board_array[p.gety() / 60 + 1][p.getx() / 60] == R_BRICK)
		{
			Bricks::unb_();
			Score += 100;
			explodebricks(x);
			DrawCircle(x.getx(), x.gety(), 70, colors[5]);
		}

		if (board_array[p.gety() / 60 + 1][p.getx() / 60] == G_BRICK)
		{
			Bricks::unb_();
			Score += 50;
		}
		board_array[p.gety() / 60 + 1][p.getx() / 60] = NILL;
	}

	if (board_array[p.gety() / 60 - 1][p.getx() / 60] != S_BRICK)
	{
		Point x(p.getx(), p.gety() - 60);
		if (x == B.getP())
			B.life_();
		if (x == E[0].getP())
		{
			E[0].DIE();
			Score += 200;
		}
		if (x == E[1].getP())
		{
			E[1].DIE();
			Score += 200;
		}
		if (x == E[2].getP())
		{
			E[2].DIE();
			Score += 200;
		}
		if (x == E[3].getP())
		{
			E[3].DIE();
			Score += 200;
		}
		if (board_array[p.gety() / 60 - 1][p.getx() / 60] == R_BRICK)
		{
			Bricks::unb_();
			Score += 100;
			explodebricks(x);
			DrawCircle(x.getx(), x.gety(), 70, colors[5]);
		}
		if (board_array[p.gety() / 60 - 1][p.getx() / 60] == G_BRICK)
		{
			Bricks::unb_();
			Score += 50;
		}
		board_array[p.gety() / 60 - 1][p.getx() / 60] = NILL;
	}

	if (board_array[p.gety() / 60][p.getx() / 60 + 1] != S_BRICK)
	{
		Point x(p.getx() + 60, p.gety());
		if (x == B.getP())
			B.life_();
		if (x == E[0].getP())
		{
			E[0].DIE();
			Score += 200;
		}
		if (x == E[1].getP())
		{
			E[1].DIE();
			Score += 200;
		}
		if (x == E[2].getP())
		{
			E[2].DIE();
			Score += 200;
		}
		if (x == E[3].getP())
		{
			E[3].DIE();
			Score += 200;
		}
		if (board_array[p.gety() / 60][p.getx() / 60 + 1] == R_BRICK)
		{
			Bricks::unb_();
			Score += 100;
			explodebricks(x);
			DrawCircle(x.getx(), x.gety(), 70, colors[5]);
		}
		if (board_array[p.gety() / 60][p.getx() / 60 + 1] == G_BRICK)
		{
			Bricks::unb_();
			Score += 50;
		}
		board_array[p.gety() / 60][p.getx() / 60 + 1] = NILL;
	}

	if (board_array[p.gety() / 60][p.getx() / 60 - 1] != S_BRICK)
	{
		Point x(p.getx() - 60, p.gety());
		if (x == B.getP())
			B.life_();
		if (x == E[0].getP())
		{
			E[0].DIE();
			Score += 200;
		}
		if (x == E[1].getP())
		{
			E[1].DIE();
			Score += 200;
		}
		if (x == E[2].getP())
		{
			E[2].DIE();
			Score += 200;
		}
		if (x == E[3].getP())
		{
			E[3].DIE();
			Score += 200;
		}
		if (board_array[p.gety() / 60][p.getx() / 60 - 1] == R_BRICK)
		{
			Bricks::unb_();
			Score += 100;
			explodebricks(x);
			DrawCircle(x.getx(), x.gety(), 70, colors[5]);
		}
		if (board_array[p.gety() / 60][p.getx() / 60 - 1] == G_BRICK)
		{
			Bricks::unb_();
			Score += 50;
		}
		board_array[p.gety() / 60][p.getx() / 60 - 1] = NILL;
	}
}

void Board::BFS()
{

	bool a = true;
	if (E[1].isalive())
		while (a)
		{
			int random = rand() % 4;
			switch (random)
			{
			case 0:
				if (game[(E[1].getP().getx() / 60)][(E[1].getP().gety() / 60) + 1] == 0)
				{
					E[1].moveup();
					a = false;
					break;
				}
				break;
			case 1:
				if (game[(E[1].getP().getx() / 60)][(E[1].getP().gety() / 60) - 1] == 0)
				{
					E[1].movedown();
					a = false;
					break;
				}
				break;
			case 2:
				if (game[(E[1].getP().getx() / 60) + 1][(E[1].getP().gety() / 60)] == 0)
				{
					E[1].moveright();
					a = false;
					break;
				}
				break;
			case 3:
				if (game[(E[1].getP().getx() / 60) - 1][(E[1].getP().gety() / 60)] == 0)
				{
					E[1].moveleft();
					a = false;
					break;
				}
			}
		}
	a = true;
	if (E[0].isalive())
		while (a)
		{
			int random = rand() % 4;
			switch (random)
			{
			case 0:
				if (game[(E[0].getP().getx() / 60)][(E[0].getP().gety() / 60) + 1] == 0)
				{
					E[0].moveup();
					a = false;
					break;
				}
				break;
			case 1:
				if (game[(E[0].getP().getx() / 60)][(E[0].getP().gety() / 60) - 1] == 0)
				{
					E[0].movedown();
					a = false;
					break;
				}
				break;
			case 2:
				if (game[(E[0].getP().getx() / 60) + 1][(E[0].getP().gety() / 60)] == 0)
				{
					E[0].moveright();
					a = false;
					break;
				}
				break;
			case 3:
				if (game[(E[0].getP().getx() / 60) - 1][(E[0].getP().gety() / 60)] == 0)
				{
					E[0].moveleft();
					a = false;
					break;
				}
			}
		}
	a = true;
	if (E[2].isalive())
		while (a)
		{
			int random = rand() % 4;
			switch (random)
			{
			case 0:
				if (game[(E[2].getP().getx() / 60)][(E[2].getP().gety() / 60) + 1] == 0)
				{
					E[2].moveup();
					a = false;
					break;
				}
				break;
			case 1:
				if (game[(E[2].getP().getx() / 60)][(E[2].getP().gety() / 60) - 1] == 0)
				{
					E[2].movedown();
					a = false;
					break;
				}
				break;
			case 2:
				if (game[(E[2].getP().getx() / 60) + 1][(E[2].getP().gety() / 60)] == 0)
				{
					E[2].moveright();
					a = false;
					break;
				}
				break;
			case 3:
				if (game[(E[2].getP().getx() / 60) - 1][(E[2].getP().gety() / 60)] == 0)
				{
					E[2].moveleft();
					a = false;
					break;
				}
			}
		}
	a = true;
	if (E[3].isalive())
		while (a)
		{
			int random = rand() % 4;
			switch (random)
			{
			case 0:
				if (game[(E[3].getP().getx() / 60)][(E[3].getP().gety() / 60) + 1] == 0)
				{
					E[3].moveup();
					a = false;
					break;
				}
				break;
			case 1:
				if (game[(E[3].getP().getx() / 60)][(E[3].getP().gety() / 60) - 1] == 0)
				{
					E[3].movedown();
					a = false;
					break;
				}
				break;
			case 2:
				if (game[(E[3].getP().getx() / 60) + 1][(E[3].getP().gety() / 60)] == 0)
				{
					E[3].moveright();
					a = false;
					break;
				}
				break;
			case 3:
				if (game[(E[3].getP().getx() / 60) - 1][(E[3].getP().gety() / 60)] == 0)
				{
					E[3].moveleft();
					a = false;
					break;
				}
			}
		}

	enum directions
	{
		FORBIDDEN = -3,
		ALLOWED = -2,
		VISITED = -1,
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};
	deque<deque<int>> board;
	// deque<deque<int>>::iterator row=board.begin();
	// deque<int>::iterator col = row->begin();
	int x, y;
	for (int i = 0; i < 13; i++)
	{

		for (int j = 0; j < 17; j++)
		{
			//		x = E.getP().getx() / 60; y = E.getP().gety() / 60;
		}
	}

	/*
	Make�a�2D�array�(i.e.make�copy�of�board�array)of�directions.
	for�each�of�the�ghost�s�valid�neighboring�squares:
		add�the�square�s�location�(the�square�s�position�in�the�2D array)
		to�the�queue�and�storethe�square�s�direction�in�the�2D array,
		indexed�by�its�location�
	while�the�queue�isn't�empty:
	� dequeue�the�next�square�location�
	  update�the�shortest�distance�and�board�coordinate�
	  for�each�valid�neighbor�of�the�current�square
	  � if�the�neighbor�has�not�been�visited,
		�add�its�location�to�the queue�and�store�the
		 �current� square�s�direction�in�the�2D array�at�the�neighbor�s�x�y�coordinates.
		return�the�direction�of�the�closest�square.
	*/
}
