//============================================================================
// Name        : bubble-shooter.cpp
// Author      : Ali Zahid Raja
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Bubble Shooting...
//============================================================================
#ifndef BOMBER_PACMAN_CPP
#define BOMBER_PACMAN_CPP

//#include <GL/gl.h>
//#include <GL/glut.h>

#include "Board.h"
#include "util.h"
#include <iostream>
#include <string>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
bool bombStatus = false;
Board *b;
int Bricks::unbreakable = 0;
int Bricks::total = 0;
// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void DrawEnemy(int x /*starting x*/, int y /*starting y*/,
			   ColorNames color /*color*/, float gw = 6 /*Enemy Width in Units*/,
			   float gh = 7 /*Enemy Height in Units*/)
{
	int ogw = 6, ogh = 7;

	glPushMatrix();
	float sx = (float)gw / ogw, sy = (float)gh / ogh;
	glTranslatef(x, y, 1);
	glScalef(sx, sy, 1);

	// Draw Enemy
	DrawRoundRect(0, 1, 6, 3, colors[color]);
	DrawCircle(3, 4, 3.01, colors[color]);
	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	//  legs
	DrawCircle(0.75, 1, 0.75, colors[color]);
	DrawCircle(3.25, 1, 0.75, colors[color]);
	DrawCircle(5.85, 1, 0.75, colors[color]);

	glPopMatrix();
	//	glPopMatrix();

	// eyes

	glPushMatrix();
	glScalef(0.9, 1.1, 1);
	DrawCircle(1.85, 3.95, 0.75, colors[WHITE]);
	DrawCircle(4.95, 3.95, 0.75, colors[WHITE]);
	glPopMatrix();

	// eyes
	DrawCircle(1.65, 4.25, 0.45, colors[BLUE]);
	DrawCircle(4.45, 4.25, 0.45, colors[BLUE]);
	glPopMatrix();
}

// Number of Vertices used to draw Bomberman Circle...
//  x= r cos (theta), y= r sin(theta)
const int npmvertices = 1220;
GLfloat pmvertices[npmvertices][2];
void InitPMVertices(float radius)
{

	float hdegree = (M_PI - M_PI / 2.0) / 360.0;
	float angle = M_PI + M_PI / 6.0;
	for (int i = 0; i < npmvertices; ++i)
	{
		pmvertices[i][0] = radius * cos(angle);
		pmvertices[i][1] = radius * sin(angle);
		angle += hdegree;
	}
}

void DrawBombermanL(float sx /*center x*/, float sy /*center y*/,
					float radius /*Radius*/,
					const ColorNames &colorname /*Bomberman Colour*/)
{

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	if (!b->getbomberman().geteat())
		glVertex4f(sx, sy, 0, 1);
	else
		b->getbomberman().seteat(false);

	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][0], sy + pmvertices[i][1], 0, 1);

	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			   radius / 10, colors[BLACK]);
}
void DrawBombermanR(float sx /*center x*/, float sy /*center y*/,
					float radius /*Radius*/,
					const ColorNames &colorname /*Bomberman Colour*/)
{

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);

	if (!b->getbomberman().geteat())

		glVertex4f(sx, sy, 0, 1);
	else
		b->getbomberman().seteat(false);

	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx - pmvertices[i][0], sy - pmvertices[i][1], 0, 1);
	glEnd();
	DrawCircle(sx + radius - radius / 2, sy + (radius - radius / 2),
			   radius / 10, colors[BLACK]);
}
void DrawBombermanU(float sx /*center x*/, float sy /*center y*/,
					float radius /*Radius*/,
					const ColorNames &colorname /*Bomberman Colour*/)
{

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	if (!b->getbomberman().geteat())

		glVertex4f(sx, sy, 0, 1);
	else
		b->getbomberman().seteat(false);

	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx - pmvertices[i][1], sy - pmvertices[i][0], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy + (radius - radius / 2),
			   radius / 10, colors[BLACK]);
}
void DrawBombermanD(float sx /*center x*/, float sy /*center y*/,
					float radius /*Radius*/,
					const ColorNames &colorname /*Bomberman Colour*/)
{

	glColor3fv(colors[colorname]); // set the circle color
	InitPMVertices(radius);
	glBegin(GL_TRIANGLE_FAN);
	if (!b->getbomberman().geteat())

		glVertex4f(sx, sy, 0, 1);
	else
		b->getbomberman().seteat(false);
	for (int i = 0; i < npmvertices; ++i)
		glVertex4f(sx + pmvertices[i][1], sy + pmvertices[i][0], 0, 1);
	glEnd();
	DrawCircle(sx - radius + radius / 2, sy - (radius - radius / 2),
			   radius / 10, colors[BLACK]);
}
/*
 * Main Canvas drawing function.
 * */
void Timer(int);

void GameDisplay() /**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0 /*Red Component*/, 0,						 // 148.0/255/*Green Component*/,
				 0.0 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);								 // Update the colors

	//
	if (!b->getbomberman().islive())
	{
		b->ENDGAME();
	}
	b->Draw();
	int x, y;
	// b->GetInitPinkyPosition(x, y);
	// cout << x << "  y= " << y << endl << flush;
	if (b->getblinky().isalive())
		DrawEnemy(b->getblinky().getP().getx() - 4, b->getblinky().getP().gety(), PINK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	if (b->getpinky().isalive())
		DrawEnemy(b->getpinky().getP().getx() - 4, b->getpinky().getP().gety(), RED, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	if (b->getinky().isalive())
		DrawEnemy(b->getinky().getP().getx() - 25, b->getinky().getP().gety(), BLACK, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	if (b->getclyde().isalive())
		DrawEnemy(b->getclyde().getP().getx() - 25, b->getclyde().getP().gety(), BLUE, 0.8 * b->GetCellSize(), 0.8 * b->GetCellSize());
	// b->GetInitBombermanPosition(x, y);

	switch (b->getbomberman().direction)
	{
	case 0:
		DrawBombermanL(b->getbomberman().getP().getx(), b->getbomberman().getP().gety(), b->GetCellSize() / 2 - 2, YELLOW);
		break;
	case 1:
		DrawBombermanR(b->getbomberman().getP().getx(), b->getbomberman().getP().gety(), b->GetCellSize() / 2 - 2, YELLOW);
		break;
	case 2:
		DrawBombermanU(b->getbomberman().getP().getx(), b->getbomberman().getP().gety(), b->GetCellSize() / 2 - 2, YELLOW);
		break;
	case 3:
		DrawBombermanD(b->getbomberman().getP().getx(), b->getbomberman().getP().gety(), b->GetCellSize() / 2 - 2, YELLOW);
		break;
	}

	b->GetInitTextPosition(x, y);
	// cout << endl << "Text Position = " << x << "  y= " << y << endl << flush;

	//	glPopMatrix();
	if (b->getbomb().isactive())
	{

		DrawCircle(b->getbomb().getP().getx(), b->getbomb().getP().gety(), b->GetCellSize() / 2 - 15, colors[RED]); // To Draw a bomb. You will provide your own x and y relative to Bombermans position

		//		bombStatus = false;
	}
	if (b->getbomb().isexploded() == true)
	{
		b->getbomb().explode();
		b->explodebricks(b->getbomb().getP());
	}

	/*
	for (int i = 0; i <13; i++)
	{
	for (int j = 0; j <17; j++)
	{
	cout << b->game[i][j]<<" "<<b->directions[i][j]<<" ";
	}
	cout << endl;
	}
	*/

	bool empty = true;

	for (int i = 0; i < 221; i++)
	{
		if (b->Brick[i].getbrick() == 2 || b->Brick[i].getbrick() == 3)
			empty = false;
	}

	if (empty && !b->getclyde().isalive() && !b->getblinky().isalive() && !b->getpinky().isalive() && !b->getinky().isalive())
	{
		b->getbomberman().kill();
	}

	if (b->getbomberman().getP() == b->getblinky().getP() || b->getbomberman().getP() == b->getpinky().getP() || b->getbomberman().getP() == b->getclyde().getP() || b->getbomberman().getP() == b->getinky().getP())
		b->getbomberman().life_();

	if (b->getgift1().isconsumed())
		DrawCircle(b->getgift1().getP().getx(), b->getgift1().getP().gety(), 10, colors[80]);
	if (b->getgift2().isconsumed())
		DrawCircle(b->getgift2().getP().getx(), b->getgift2().getP().gety(), 10, colors[80]);
	if (b->getgift3().isconsumed())
		DrawCircle(b->getgift3().getP().getx(), b->getgift3().getP().gety(), 10, colors[80]);
	if (b->getgift4().isconsumed())
		DrawCircle(b->getgift4().getP().getx(), b->getgift4().getP().gety(), 10, colors[80]);
	if (b->getgift5().isconsumed())
		DrawCircle(b->getgift5().getP().getx(), b->getgift5().getP().gety(), 10, colors[80]);
	if (b->getgift6().isconsumed())
		DrawCircle(b->getgift6().getP().getx(), b->getgift6().getP().gety(), 10, colors[80]);
	if (b->getgift7().isconsumed())
		DrawCircle(b->getgift7().getP().getx(), b->getgift7().getP().gety(), 10, colors[80]);
	if (b->getgift8().isconsumed())
		DrawCircle(b->getgift8().getP().getx(), b->getgift8().getP().gety(), 10, colors[80]);
	if (b->getgift9().isconsumed())
		DrawCircle(b->getgift9().getP().getx(), b->getgift9().getP().gety(), 10, colors[80]);
	if (b->getgift0().isconsumed())
		DrawCircle(b->getgift0().getP().getx(), b->getgift0().getP().gety(), 10, colors[80]);
	if (b->getbomberman().getP() == b->getgift1().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift1().consumed();
	}
	if (b->getbomberman().getP() == b->getgift2().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift2().consumed();
	}
	if (b->getbomberman().getP() == b->getgift3().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift3().consumed();
	}
	if (b->getbomberman().getP() == b->getgift4().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift4().consumed();
	}
	if (b->getbomberman().getP() == b->getgift5().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift5().consumed();
	}
	if (b->getbomberman().getP() == b->getgift6().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift6().consumed();
	}
	if (b->getbomberman().getP() == b->getgift7().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift7().consumed();
	}
	if (b->getbomberman().getP() == b->getgift8().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift8().consumed();
	}
	if (b->getbomberman().getP() == b->getgift9().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift9().consumed();
	}
	if (b->getbomberman().getP() == b->getgift0().getP())
	{
		b->getbomberman().seteat(true);
		b->Scorer(100);
		b->getgift0().consumed();
	}
	DrawString(x, y, "Score = " + Num2Str(b->Scorer()), colors[5]);
	if (!b->getp())
		DrawString(700, 800, "PAUSED", colors[5]);
	glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{

	if (b->getp())
	{
		if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
		{
			// what to do when left key is pressed...

			if (b->game[(b->getbomberman().getP().getx() / 60) - 1][(b->getbomberman().getP().gety() / 60)] == 0)
				b->getbomberman().moveleft();
			if (b->getbomberman().getP() == b->getblinky().getP() || b->getbomberman().getP() == b->getpinky().getP() || b->getbomberman().getP() == b->getclyde().getP() || b->getbomberman().getP() == b->getinky().getP())
				b->getbomberman().life_();

			if (!b->getbomberman().islive())
				b->ENDGAME();
			else
				glutPostRedisplay();
		}
		else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
		{

			if (b->game[(b->getbomberman().getP().getx() / 60) + 1][(b->getbomberman().getP().gety() / 60)] == 0)
				b->getbomberman().moveright();
			if (b->getbomberman().getP() == b->getblinky().getP() || b->getbomberman().getP() == b->getpinky().getP() || b->getbomberman().getP() == b->getclyde().getP() || b->getbomberman().getP() == b->getinky().getP())
				b->getbomberman().life_();
			if (!b->getbomberman().islive())
				b->ENDGAME();
			else
				glutPostRedisplay();
		}
		else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
		{

			if (b->game[(b->getbomberman().getP().getx() / 60)][(b->getbomberman().getP().gety() / 60) + 1] == 0)
				b->getbomberman().moveup();

			if (b->getbomberman().getP() == b->getblinky().getP() || b->getbomberman().getP() == b->getpinky().getP() || b->getbomberman().getP() == b->getclyde().getP() || b->getbomberman().getP() == b->getinky().getP())
				b->getbomberman().life_();
			if (!b->getbomberman().islive())
				b->ENDGAME();
			else
				glutPostRedisplay();
		}

		else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
		{

			if (b->game[(b->getbomberman().getP().getx() / 60)][(b->getbomberman().getP().gety() / 60) - 1] == 0)
				b->getbomberman().movedown();

			if (b->getbomberman().getP() == b->getblinky().getP() || b->getbomberman().getP() == b->getpinky().getP() || b->getbomberman().getP() == b->getclyde().getP() || b->getbomberman().getP() == b->getinky().getP())
				b->getbomberman().life_();
			if (!b->getbomberman().islive())
				b->ENDGAME();
			else
				glutPostRedisplay();
		}
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	/*
	glutPostRedisplay();
	*/
}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27 /* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'p' || key == 'P')
	{
		if (!b->getp())
			b->setp(true);
		else
			b->setp(false);
		glutPostRedisplay();
	}

	if (key == 'b' || key == 'B') // Key for placing the bomb
	{
		if (b->getp())
		{
			b->getbomb().activate();
			b->getbomb().setP(b->getbomberman().getP());

			if (!b->getbomberman().islive())
				b->ENDGAME();
			else

				glutPostRedisplay();
		}
	}
}

/*
* This function is called after every 1000.0/FPS milliseconds

* (FPS is defined on in the beginning).
* You can use this function to animate objects and control the
* speed of different moving objects by varying the constant FPS.
*
* */
void Timer(int m)
{

	// implement your functionality here
	// glutPostRedisplay();
	if (b->getp())
	{

		if (b->getbomb().isactive())
			b->getbomb().ticker();
		if (!b->getbomberman().islive())
			b->ENDGAME();
		else
		{
			b->BFS();
			glutPostRedisplay();
		}
	}
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{

	b = new Board(60, 60);			// create a new board object to use in the Display Function ...
	int width = 1020, height = 840; // i have set my window size to be 800 x 600
	b->InitalizeBoard(width, height);
	InitRandomizer();							  // seed the random number generator...
	glutInit(&argc, argv);						  // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50);				  // set the initial position of our window
	glutInitWindowSize(width, height);			  // set the size of our window
	glutCreateWindow("AZR's Bomberman");		  // set the title of our game window
	SetCanvasSize(width, height);				  // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	// glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
#ifdef WITH_TEXTURES
	RegisterTextures();
#endif
	glutDisplayFunc(GameDisplay);	   // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys);   // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Bomberman_CPP_ */
