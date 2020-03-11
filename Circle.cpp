#include "Circle.h"
#include <cmath>
#include "GP142.h"
//#include <graphics.h>


void Circle::draw_circle(int x, int y, int radius, int color = WHITE)
{
	GP142_circleXY(color, x, y, radius);
}

void Circle::drawcircle(int centrex, int centrey, int radius, int boundaryColor)
{
	int ycoord1=0, ycoord2=0;
	for (int i = centrex; i <= centrex + radius; i++)
	{
		ycoord1 = sqrt(pow(radius, 2) - pow(centrex - i, 2)) + centrey;
		ycoord2 = (-1 * sqrt(pow(radius, 2) - pow(centrex - i, 2))) + centrey;
		
		GP142_pixelXY(boundaryColor, i, ycoord1);
		
		GP142_pixelXY(boundaryColor, i, ycoord2);

	}

	for (int i = centrex; i >= centrex - radius; i--)
	{
		ycoord1 = sqrt(pow(radius, 2) - pow(centrex - i, 2)) + centrey;
		ycoord2 = (-1*sqrt(pow(radius, 2) - pow(centrex - i, 2))) + centrey;
		GP142_pixelXY(boundaryColor, i, ycoord1);
		GP142_pixelXY(boundaryColor, i, ycoord2);

	}

	for (int i = centrey; i <= centrey + radius; i++)
	{
		ycoord1 = sqrt(pow(radius, 2) - pow(centrey - i, 2)) + centrex;
		ycoord2 = (-1 * sqrt(pow(radius, 2) - pow(centrey - i, 2))) + centrex;
		GP142_pixelXY(boundaryColor, ycoord1, i);
		GP142_pixelXY(boundaryColor, ycoord2, i);

	}

	for (int i = centrey; i >= centrey - radius; i--)
	{
		ycoord1 = sqrt(pow(radius, 2) - pow(centrey - i, 2)) + centrex;
		ycoord2 = (-1 * sqrt(pow(radius, 2) - pow(centrey - i, 2))) + centrex;
		GP142_pixelXY(boundaryColor, ycoord1, i);
		GP142_pixelXY(boundaryColor, ycoord2, i);

	}
	//highlightPixel(centrex, centrey, );

	if(fill_color!=-1)
	{
		fillColor(fill_color);
	}

	if (fill_color == BLACK)
	{
		fill_color = -1;
	}

	/*fillColor3(centrex -5, centrey + 5, BLACK, fill_color);
	fillColor4(centrex +5, centrey - 5, BLACK, fill_color);*/
	
}

Circle::Circle()
	:Shape(1, 1)
{

}

Circle::Circle(const Circle & obj)
{
	points = obj.points;
	fill_color = boundary_color = BLACK;
	radius = obj.radius;
}

Circle::Circle(int bc, int fc, double rad)
	:Shape(1, bc), radius(rad), fill_color(fc)
{
	int mouse_x1, mouse_y1;
	char key_pressed1;
	bool clickinrange1 = false, clickinrange2 = false;
	while (clickinrange1 == false)
	{

		switch (GP142_await_event(&mouse_x1, &mouse_y1, &key_pressed1))
		{


		case GP142_MOUSE:

			if (clickInRange(mouse_x1, mouse_y1) == true)
			{

				clickinrange1 = true;
			}
			int mouse_x2, mouse_y2;
			char key_pressed2;
			//highlightPixel(mouse_x1, mouse_y1, boundary_color);

			while (clickinrange2 == false && clickinrange1 == true)
			{

				if (GP142_await_event(&mouse_x2, &mouse_y2, &key_pressed2) == GP142_MOUSE)
				{

					if (clickInRange(mouse_x2, mouse_y2) == true)
					{
						clickinrange2 = true;
						double rad;
						rad = pow((mouse_x2 - mouse_x1), 2) + pow((mouse_y2 - mouse_y1), 2);
						rad = sqrt(rad);

						points[0].x = mouse_x1;
						points[0].y = mouse_y1;
						radius = rad;

						Point p = { double(mouse_x2), double(mouse_y2) };
						points.push_back(p);

						//draw_circle(mouse_x1, mouse_y1, rad, boundary_color);
						//draw_circle(mouse_x1, mouse_y1, rad - 1, fill_color);
						//highlightPixel(mouse_x1, mouse_y1, fill_color);
						
					}
				}
			}

			break;

		}
	}
}

bool Circle::contains(Point & p)
{
	double distance = sqrt(pow(p.x - points[0].x, 2) + pow(p.y - points[0].y, 2));

	if (distance <= radius)
	{
		return true;
	}

	return false;

}

int & Circle::getFill()
{

	return fill_color;
	// TODO: insert return statement here
}

void Circle::fillColor(int color)
{
	Shape::fillColor(points[0].x, points[0].y, color);
	fill_color = color;
}

void Circle::serialize(string & fname)
{
	ofstream file(fname, ios::app);
		file << endl << "class Circle" << endl;
		//file.write((char*)this, sizeof(*this));
		file.write((char*)&boundary_color, sizeof(boundary_color));
		file.write((char *)&fill_color, sizeof(fill_color));
		file.write((char*)&radius, sizeof(radius));
		file.write((char*)&points[0], sizeof(points[0]));
		file.write((char *)&points[1], sizeof(points[1]));
}

void Circle::deserialize(istream & in)
{
	//in.read((char*)this, sizeof(*this));
	in.read((char*)&boundary_color, sizeof(boundary_color));
	in.read((char *)&fill_color, sizeof(fill_color));
	in.read((char*)&radius, sizeof(radius));
	points.resize(2);
	in.read((char*)&points[0], sizeof(points[0]));
	in.read((char*)&points[1], sizeof(points[1]));
}

void Circle::draw()
{
	
	drawcircle(points[0].x, points[0].y, radius, boundary_color);

	/*if (fill_color == BLACK)
	{
		fillColor(BLACK);
		draw_circle(points[0].x, points[0].y, BLACK);
	}*/
}

Circle::~Circle()
{
	cout << "YES" << endl;
}
