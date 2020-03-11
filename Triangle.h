#pragma once
#include "Polygon.h"
#include "OpenShape.h"


class Triangle :public Polygon
{
	float area(int x1, int y1, int x2, int y2, int x3, int y3);
	

public:

	Triangle();
	Triangle(const Triangle &obj);
	Triangle(int pointsize, int boundaryc, int fillc=-1);
	void draw();
	void fillColor(int color);
	bool contains(Point &p);
	void serialize(string &fname);
	void deserialize(istream & in);
	//void eraser(vector<Point> points, int boundary_color, int fill_color=BLACK);
	int &getFill();
	~Triangle();
};

