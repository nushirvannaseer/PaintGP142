#pragma once
#include "Polygon.h"


class Rect :public Polygon
{

public:

	Rect();
	Rect(const Rect & obj);
	Rect(int pointsize, int boundaryc, int fillc=-1);
	void draw();
	bool contains(Point &p);
	void fillColor(int color);
	int &getFill();
	void serialize(string &fname);
	
	void deserialize(istream &in);
	~Rect();
};
