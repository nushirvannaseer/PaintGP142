#include "Polygon.h"
#include "GP142.H"



void Polygon::draw_line(int x1, int y1, int x2, int y2, int color, int width)
{	
		GP142_lineXY(color, x1, y1, x2, y2, width);
}

Polygon::Polygon()
{
}

Polygon::Polygon(int pointsize, int boundaryc, int fillc)
	:Shape(pointsize, boundaryc)
{
	fill_color = fillc;
}


//void Polygon::fillColor(int color)
//{
//}


int & Polygon::getFill()
{
	// TODO: insert return statement here
	return fill_color;
}

Polygon::~Polygon()
{
	cout << "O MY GAD" << endl;
}

