#include "OpenShape.h"


void OpenShape::draw_line(int x1, int y1, int x2, int y2, int color, int width)
{	
		GP142_lineXY(color, x1, y1, x2, y2, width);
}

OpenShape::OpenShape()
{
}

OpenShape::OpenShape(int ps, int bc, bool s)
	:Shape(ps, bc),style(s)
{
}

OpenShape::~OpenShape()
{
	cout << "OPENSHAPE VIRTUAL" << endl;
}



int & OpenShape::getFill()
{
	int a = -1;
	// TODO: insert return statement here
	return a;

}

line::line()
{
}

line::line(int ps, int bc, bool s, int bg)
	:OpenShape(ps, bc, s), bg_color(bg)
{
	int mouse_x1, mouse_y1;
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

				//highlightPixel(mouse_x1, mouse_y1, boundary_color);
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

void line::draw()
{
	

	if (style == true)
	{
		OpenShape::draw_line(points[0].x, points[0].y, points[1].x, points[1].y, boundary_color);
	}

	else
	{
		//OpenShape::draw_line(points[0].x, points[0].y, points[1].x, points[1].y, boundary_color);
		Shape::manualLine(points[0].x, points[0].y, points[1].x, points[1].y, boundary_color);
	}
	

}

bool line::contains(Point & p)
{
	double gradient = (points[1].y - points[0].y) / (points[1].x-points[0].x);
	double c = points[1].y - (gradient*points[1].x);

	double tempy = double(gradient) * p.x + double(c);
	double tempx = double(p.y - c) / double(gradient);

	int x2 = points[1].x, y2 = points[1].y, x1 = points[0].x, y1 = points[0].y;

	if (x1 > x2)
	{
		swap(x1, x2);
	}

	if (y1 > y2)
	{
		swap(y1, y2);
	}

	if (p.x > x2 || p.x<x1 || p.y>y2 || p.y < y1)
	{
		return false;
	}

	if ((int(tempy) <= int(p.y+2) && int(tempy)>=int(p.y-2)) && (int(tempx) <= int(p.x+2) && int(tempx)>=int(p.x-2)))
	{
		return true;
	}
	

	return false;

}

void line::fillColor(int x, int y, int color)
{

	if (style == true)
	{
		OpenShape::draw_line(points[0].x, points[0].y, points[1].x, points[1].y, color);
		boundary_color = color;
	}

	else
	{
		//OpenShape::draw_line(points[0].x, points[0].y, points[1].x, points[1].y, color);
		Shape::manualLine(points[0].x, points[0].y, points[1].x, points[1].y, color);
		boundary_color = color;
	}

}

void line::serialize(string & fname)
{
	ofstream file(fname, ios::app);
	file << endl << "class line" << endl;
	//file.write((char*)this, sizeof(*this));
	file.write((char*)&boundary_color, sizeof(boundary_color));
	file.write((char *)&bg_color, sizeof(bg_color));
	file.write((char *)&style, sizeof(style));
	for (int i = 0; i < points.size(); i++)
	{
		file.write((char*)&points[i], sizeof(points[i]));
	}

}

int & line::getBoundary()
{
	// TODO: insert return statement here
	return boundary_color;
}

void line::deserialize(istream & in)
{
	in.read((char*)&boundary_color, sizeof(boundary_color));
	in.read((char *)&bg_color, sizeof(bg_color));
	in.read((char *)&style, sizeof(style));
	points.resize(2);
	for (int i = 0; i < points.size(); i++)
	{
		in.read((char*)&points[i], sizeof(points[i]));
	}
}

line::~line()
{
}

curve::curve()
{
}

curve::curve(int ps, int bc, bool s, int bg)
	:OpenShape(ps, bc, s), bg_color(bg)
{
	int mouse_x1, mouse_y1, num = 0;
	char key_pressed1;
	bool loop = true;

	bool click1 = false, click2 = false;

	while (loop == true)
	{

		switch (GP142_await_event(&mouse_x1, &mouse_y1, &key_pressed1))
		{
		case GP142_MOUSE:

			if (clickInRange(mouse_x1, mouse_y1) == true)
			{
				num++;
				points.resize(num);

				points[num - 1].x = mouse_x1;
				points[num - 1].y = mouse_y1;

				//highlightPixel(mouse_x1, mouse_y1, boundary_color);

			}
			break;

		case GP142_KBD:

			loop = false;
			break;

		}

	}
}

void curve::draw()
{
	

	if (style == true)
	{
		for (int i = 0; i < points.size()-1; i++)
		{
			OpenShape::draw_line(points[i].x, points[i].y, points[i+1].x, points[i+1].y, boundary_color);
		}
	}


	else
	{
		
			for (int i = 0; i < points.size() - 1; i++)
			{
				Shape::manualLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, boundary_color);
			}
		
	}
}

void curve::serialize(string & fname)
{
	ofstream file(fname, ios::app);
	file << endl << "class curve" << endl;
	//file.write((char*)this, sizeof(*this));
	file.write((char*)&boundary_color, sizeof(boundary_color));
	file.write((char *)&bg_color, sizeof(bg_color));
	file.write((char *)&style, sizeof(style));	
	file << endl << points.size();
	for (int i = 0; i < points.size(); i++)
	{
		file.write((char*)&points[i], sizeof(points[i]));
	}
}

void curve::deserialize(istream & in)
{
	in.read((char*)&boundary_color, sizeof(boundary_color));
	in.read((char *)&bg_color, sizeof(bg_color));
	in.read((char *)&style, sizeof(style));
	int size;
	in >> size;
	points.resize(size);
	for (int i = 0; i < points.size(); i++)
	{
		in.read((char*)&points[i], sizeof(points[i]));

	}
}


bool curve::contains(Point & p)
{

	for (int i = 0; i < points.size() - 1; i++)
	{
		double gradient = (points[i+1].y - points[i].y) / (points[i+1].x - points[i].x);
		double c = points[i].y - (gradient*points[i].x);

		double tempy = double(gradient) * p.x + double(c);
		double tempx = double(p.y - c) / double(gradient);

		if ((int(tempy) <= int(p.y + 2) && int(tempy) >= int(p.y - 2)) && (int(tempx) <= int(p.x + 2) && int(tempx) >= int(p.x - 2)))
		{
			return true;
		}
	}	

	return false;
}

int & curve::getBoundary()
{
	// TODO: insert return statement here
	return boundary_color;
}

void curve::fillColor(int xx, int y, int color)
{
	if (style == true)
	{
		for (int i = 0; i < points.size() - 1; i++)
		{
			OpenShape::draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);
		}
		boundary_color = color;
	}


	else
	{

		for (int i = 0; i < points.size() - 1; i++)
		{
			Shape::manualLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);
			
		}
		boundary_color = color;
	}

}

curve::~curve()
{
}
