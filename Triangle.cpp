#include "Triangle.h"



float Triangle::area(int x1, int y1, int x2, int y2, int x3, int y3)
{
	
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
	
}

Triangle::Triangle()
{
}

Triangle::Triangle(const Triangle & obj)
{
	points = obj.points;
	fill_color = boundary_color = BLACK;
}

Triangle::Triangle(int pointsize, int boundaryc, int fillc)
	:Polygon(3, boundaryc, fillc)
{
	points.resize(3);

	int mouse_x1, mouse_y1, num = 0;
	char key_pressed1;

	for (int i = 0; i < 3; i++)
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

void Triangle::draw()
{
	
	for (int i = 0; i < points.size() - 1; i++)
	{
		Polygon::draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, boundary_color);
	}

	Polygon::draw_line(points[0].x, points[0].y, points[2].x, points[2].y, boundary_color);

	
	
	
	/*if (fill_color == BLACK)
	{
		fillColor(fill_color);
	}*/
	
}



void Triangle::fillColor(int color)
{
	int x = (((points[0].x+points[1].x)/2)+points[2].x)/2;
	int y = (((points[0].y+points[1].y)/2)+points[2].y)/2;

	Shape::fillColor(x, y, color);
	fill_color = color;

}

bool Triangle::contains(Point & p)
{

	/* Calculate area of triangle ABC */
	float A = area(points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y);

	/* Calculate area of triangle PBC */
	float A1 = area(p.x, p.y, points[1].x, points[1].y, points[2].x, points[2].y);

	/* Calculate area of triangle PAC */
	float A2 = area(points[0].x, points[0].y, p.x, p.y, points[2].x, points[2].y);

	/* Calculate area of triangle PAB */
	float A3 = area(points[0].x, points[0].y, points[1].x, points[1].y, p.x, p.y);

	/* Check if sum of A1, A2 and A3 is same as A */
	if (A == A1 + A2 + A3)
	{
		return true;
	}

	return false;
}

void Triangle::serialize(string &fname)
{
	ofstream file(fname, ios::app);
	file << endl << "class Triangle" << endl;
	//file.write((char*)this, sizeof(*this));
	file.write((char*)&boundary_color, sizeof(boundary_color));
	file.write((char *)&fill_color, sizeof(fill_color));
	for (int i = 0; i < points.size(); i++)
	{
		file.write((char*)&points[i], sizeof(points[i]));
	}
	
}

void Triangle::deserialize(istream & in)
{
	in.read((char*)&boundary_color, sizeof(boundary_color));
	in.read((char *)&fill_color, sizeof(fill_color));
	points.resize(3);
	for (int i = 0; i < points.size(); i++)
	{
		in.read((char*)&points[i], sizeof(points[i]));
	}
	
}

int & Triangle::getFill()
{
	// TODO: insert return statement here
	return fill_color;
}

Triangle::~Triangle()
{
	cout << "H" << endl;
}
