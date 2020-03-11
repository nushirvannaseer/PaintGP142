#include "Rect.h"
#include "Polygon.h"

using namespace std;

Rect::Rect()
{
}

Rect::Rect(const Rect & obj)
{
	points = obj.points;
	fill_color = boundary_color = BLACK;
}

Rect::Rect(int pointsize, int boundaryc, int fillc)
	:Polygon(2, boundaryc, fillc)
{
	points.resize(2);

	int mouse_x1, mouse_y1, num = 0;
	char key_pressed1;


	for (int i = 0; i < 2; i++)
	{
		switch (GP142_await_event(&mouse_x1, &mouse_y1, &key_pressed1))
		{
		case GP142_MOUSE:

			if (clickInRange(mouse_x1, mouse_y1) == true)
			{

				points[i].x = mouse_x1;
				points[i].y = mouse_y1;

				highlightPixel(mouse_x1, mouse_y1, boundary_color);
			}

			else
			{
				i--;
			}

			break;

		case GP142_KBD:
			i--;
		}
	}
}

void Rect::draw()
{
	

	Polygon::draw_line(points[0].x, points[0].y, points[1].x, points[0].y, boundary_color);
	Polygon::draw_line(points[0].x, points[0].y, points[0].x, points[1].y, boundary_color);
	Polygon::draw_line(points[0].x, points[1].y, points[1].x, points[1].y, boundary_color);
	Polygon::draw_line(points[1].x, points[1].y, points[1].x, points[0].y, boundary_color);


	
		

	/*if (fill_color == BLACK)
	{
		fillColor(fill_color);
	}*/
	


}

bool Rect::contains(Point & p)
{
	int x1 = points[0].x, x2 = points[1].x, y1 = points[0].y, y2 = points[1].y;
	if (points[0].x > points[1].x)
	{
		x2 = points[0].x;
		x1 = points[1].x;
	}

	if (points[0].y > points[1].y)
	{
		y2 = points[0].y;
		y1 = points[1].y;
	}

	if (p.x >= x1 && p.x <= x2 && p.y >= y1 && p.y <= y2)
	{
		return true;
	}

	return false;
	
}



int & Rect::getFill()
{
	// TODO: insert return statement here
	return fill_color;
}

void Rect::serialize(string & fname)
{
	ofstream file(fname, ios::app);
	file << endl << "class Rectangle" << endl;
	//file.write((char*)this, sizeof(*this));
	file.write((char*)&boundary_color, sizeof(boundary_color));
	file.write((char *)&fill_color, sizeof(fill_color));
	for (int i = 0; i < points.size(); i++)
	{
		file.write((char*)&points[i], sizeof(points[i]));
	}
}

void Rect::deserialize(istream & in)
{
	in.read((char*)&boundary_color, sizeof(boundary_color));
	in.read((char *)&fill_color, sizeof(fill_color));
	points.resize(2);
	for (int i = 0; i < points.size(); i++)
	{
		in.read((char*)&points[i], sizeof(points[i]));
	}
}

void Rect::fillColor(int color)
{
	int x = (points[0].x + points[1].x) / 2;
	int y = (points[0].y + points[1].y) / 2;

	Shape::fillColor(x, y, color);
	fill_color = color;
}


Rect::~Rect()
{
	cout << "E" << endl;
}












