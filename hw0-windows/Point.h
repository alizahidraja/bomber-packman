#pragma once
class Point
{
	int x;
	int y;
	bool go;

public:
	bool operator==(Point);
	Point();
	Point(int a, int b);
	bool isgo();
	void setgo(bool a);
	int getx();
	int gety();
	void setx(int a);
	void sety(int);
	~Point();
};
