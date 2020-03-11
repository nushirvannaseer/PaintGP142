#pragma once
#include "Shape.h"
#include "GP142.H"


class Polygon : public Shape
{
protected:
	int fill_color;
	void draw_line(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1);

public:
	Polygon();
	Polygon(int pointsize, int boundaryc, int fillc);
	virtual void draw() = 0;
	virtual void fillColor(int color) = 0;
	virtual bool contains(Point &p) = 0;
	virtual void serialize(string &fname) = 0;
	virtual void deserialize(istream & in) = 0;
	int& getFill();
	~Polygon();
};

