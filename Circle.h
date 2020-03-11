#pragma once
#include "Shape.h"
#include "GP142.H"
#include "GP142LIB.H"
#include <cmath>

class Circle :public Shape
{
	int fill_color;
	double radius;
	
	void draw_circle(int x, int y, int radius, int color);
	
	
	void drawcircle(int centrex, int centrey, int radius, int boundary_color);

public:
	Circle();
	Circle(const Circle &obj);
	Circle(int boundaryc, int fillc=-1, double rad=1);
	bool contains(Point &p);
	int &getFill();
	void fillColor(int color);
	void serialize(string &fname);
	void deserialize(istream & in);
	void draw();
	~Circle();
};

