#include "nPolygon.h"
#include "OpenShape.h"



bool nPolygon::point_on_line(int x1, int y1, int x, int y, int x2, int y2)
{

	if (x <= max(x1, x2) && x >= min(x1, x2) && y <= max(y1, y2) && y >= min(y1, y2))
	{
		return true;
	}

	return false;
}

int nPolygon::orientation(int x1, int y1, int x, int y, int x2, int y2)
{
	int ori = (y - y1)*(x2 - x) - (x - x1)*(y2 - y);
	
	if (ori == 0)
	{
		return 0;
	}

	else if (ori > 0)
	{
		return 1;
	}
		
	else
	{
		return 2;
	}
		

}

bool nPolygon:: intersects(int p1x, int p1y, int q1x, int q1y, int p2x, int p2y, int q2x, int q2y)
{
	int ori1, ori2, ori3, ori4;
	ori1 = nPolygon::orientation(p1x, p1y, q1x, q1y, p2x, p2y);
	ori2 = nPolygon::orientation(p1x, p1y, q1x, q1y, q2x, q2y);
	ori3 = nPolygon::orientation(p2x, p2y, q2x, q2y, p1x, p1y);
	ori4 = nPolygon::orientation(p2x, p2y, q2x, q2y, q1x, q1y);

	if (ori1 != ori2 && ori3 != ori4)
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p1x, p1y, p2x, p2y, q1x, p1y))
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p1x, p1y, q2x, q2y, q1x, q1y))
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p2x, p2y, p1x, p1y, q2x, p2y))
	{
		return true;
	}

	if (ori1 == 0 && point_on_line(p2x, p2y, q1x, q1y, q2x, q2y))
	{
		return true;
	}

	return false;

}

nPolygon::nPolygon()
{
}

nPolygon::nPolygon(int pointsize, int boundaryc, int fillc)
	:Polygon(3, boundaryc, fillc)
{
	points.resize(3);

	int mouse_x1, mouse_y1, num = 0;
	char key_pressed1;
	bool loop = true;
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

				highlightPixel(mouse_x1, mouse_y1, boundary_color);
			}
			break;

		case GP142_KBD:

			loop = false;
			break;

		}
	}

}

nPolygon::nPolygon(const nPolygon & obj)
{
	points = obj.points;
	boundary_color =fill_color= BLACK;

}

void nPolygon::draw()
{
	

	for (int i = 0; i < points.size() - 1; i++)
	{
		Polygon::draw_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, boundary_color);
	}

	Polygon::draw_line(points[0].x, points[0].y, points[points.size()-1].x, points[points.size()-1].y, boundary_color);

	
	//fillColor(fill_color);
}

//bool nPolygon::contains(Point & p)
//{
//	int hl = 0, hr = 0;
//
//	for (int i = 0; i < points.size() - 1; i++)
//	{
//		for (int j = 0; j <= 490; j++)
//		{
//			if (point_on_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, p.x+j, p.y) == true)
//			{
//				if (p.x + j == points[i].x || p.x + j == points[i + 1].x)
//				{
//					hr++;
//				}
//
//				hr++;
//			}
//
//			if (point_on_line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, p.x - j, p.y) == true)
//			{
//				if (p.x - j == points[i].x || p.x - j == points[i + 1].x)
//				{
//					hl++;
//				}
//
//				hl++;
//			}
//
//		}
//	}
//
//	for (int j = 0; j <= 490; j++)
//	{
//		if (point_on_line(points[0].x, points[0].y, points[points.size() - 1].x, points[points.size() - 1].y, p.x + j, p.y) == true)
//		{
//			if (p.x + j == points[0].x || p.x + j == points[points.size() - 1].x)
//			{
//				hr++;
//			}
//
//			hr++;
//		}
//
//		if (point_on_line(points[0].x, points[0].y, points[points.size() - 1].x, points[points.size() - 1].y, p.x - j, p.y) == true)
//		{
//			if (p.x - j == points[0].x || p.x - j == points[points.size() - 1].x)
//			{
//				hl++;
//			}
//
//			hl++;
//		}
//
//	}
//
//	if (hl % 2 != 0 || hr % 2 != 0)
//	{
//		return true;
//	}
//
//	return false;
//
//}


bool nPolygon::contains(Point &p)
{
	/*Point max = { 493, p.y };
	int count = 0, i = 0;

	do
	{
		int next_point = (i + 1) % points.size();
		if (intersects(points[i].x, points[i].y, points[next_point].x, points[next_point].y, p.x, p.y, max.x, max.y))
		{
			if (orientation(points[i].x, points[i].y, p.x, p.y, points[next_point].x, points[next_point].y) == 0)
			{
				return point_on_line(points[i].x, points[i].y, p.x, p.y, points[next_point].x, points[next_point].y);
			}
			count++;
		}
		i = next_point;
	}while (i != 0);

	return (count % 2 == 1);*/

	int i, j, nvert = points.size();
	bool c = false;

	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((points[i].y >= p.y) != (points[j].y >= p.y)) &&
			(p.x <= (points[j].x - points[i].x) * (p.y - points[i].y) / (points[j].y - points[i].y) + points[i].x)
			)
			c = !c;
	}
	return c;


}

void nPolygon::fillColor(int color)
{
}

int & nPolygon::getFill()
{
	// TODO: insert return statement here
	return fill_color;
}

void nPolygon::serialize(string & fname)
{
	ofstream file(fname, ios::app);
	file << endl << "class nPolygon" << endl;
	//file.write((char*)this, sizeof(*this));
	file.write((char*)&boundary_color, sizeof(boundary_color));
	file.write((char *)&fill_color, sizeof(fill_color));
	file << endl << points.size();
	for (int i = 0; i < points.size(); i++)
	{
		file.write((char*)&points[i], sizeof(points[i]));
	}

}

void nPolygon::deserialize(istream & in)
{
	in.read((char*)&boundary_color, sizeof(boundary_color));
	in.read((char *)&fill_color, sizeof(fill_color));
	int size;
	in >> size;
	points.resize(size);
	for (int i = 0; i < points.size(); i++)
	{
		in.read((char*)&points[i], sizeof(points[i]));
	}
}

//void nPolygon::fillColor(int color)
//{
//	int x, y;
//	x = (points[0].x + points[1].x) / 2;
//	y = (points[0].y + points[1].y) / 2;
//	for (int i = 2; i < points.size(); i++)
//	{
//		x = (x + points[i].x) / 2;
//		y = (y + points[i].x) / 2;
//	}
//
//	Shape::fillColor(x, y, color);
//	fill_color = color;
//}


nPolygon::~nPolygon()
{
	cout << "nPoly" << endl;
}





