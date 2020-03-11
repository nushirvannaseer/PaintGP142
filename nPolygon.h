#pragma once
#include "Polygon.h"

class nPolygon :public Polygon
{

	bool point_on_line(int x1, int y1, int x2, int y2, int x, int y);

public:
	nPolygon();
	nPolygon(int pointsize, int boundaryc, int fillc=-1);
	nPolygon(const nPolygon & obj);
	void draw();
	bool contains(Point &p);
	int orientation(int x1, int y1, int x, int y, int x2, int y2);
	bool intersects(int p1x, int p1y, int q1x, int q1y, int p2x, int p2y, int q2x, int q2y);
	void fillColor(int color);
	int &getFill();
	void serialize(string &fname);
	void deserialize(istream & in);
	~nPolygon();
};



