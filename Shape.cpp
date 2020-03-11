#include "Shape.h"


void Shape::highlightPixel(int mousex, int mousey, int color=BLACK)
{
	GP142_pixelXY(color, mousex, mousey);
}

bool Shape::clickInRange(int mouse_x, int mouse_y)
{

	if (mouse_x >= -492 && mouse_x <= -400 && mouse_y <= 370 && mouse_y >= -370)
	{
		return false;
	}

	else if (mouse_x >= -492 && mouse_x <= 492 && mouse_y <= -200 && mouse_y >= -370)
	{
		return false;
	}

	return true;
}

void Shape::manualLine(int mouse_x1, int mouse_y1, int mouse_x2, int mouse_y2, int color_to_set, int width)
{
	if (double(mouse_x2) - double(mouse_x1) != 0)
	{
		double gradient = double(mouse_y2 - mouse_y1) / double(mouse_x2 - mouse_x1);
		double y_intercept = double(mouse_y1) - double((gradient*double(mouse_x1)));
		int length_of_line = sqrt(pow((mouse_x2 - mouse_x1), 2) + pow((mouse_y2 - mouse_y1), 2));

		int startx = mouse_x1, starty = mouse_y1, endx = mouse_x2, endy = mouse_y2;
		if (mouse_x1 > mouse_x2)
		{
			startx = mouse_x2;
			starty = mouse_y2;//decrease
			endx = mouse_x1;
			endy = mouse_y1;
		}


		for (int i = startx; i <= endx; i++)
		{
			if (double(i % 5) == 0 || double(-i%5)==0)
			{
				int j = 0;
				j = (gradient*i) + y_intercept;
				int h = i; int k = j;

				GP142_pixelXY(color_to_set, i, j);
			}		
			
		}


		//pixelArray[h + 492][k + 363] = color_to_set;
		//
	}

	else
	{
		int startx = mouse_x1, starty = mouse_y1, endx = mouse_x2, endy = mouse_y2;
		if (mouse_y1 > mouse_y2)
		{
			startx = mouse_x2;
			starty = mouse_y2;//decrease
			endx = mouse_x1;
			endy = mouse_y1;
		}


		for (int i = starty; i <= endy; i++)
		{
			if (i % 2== 0)
			{
				GP142_pixelXY(color_to_set, mouse_x1, i);
			}

						
		}
	}

}

int Shape::retColor(COLORREF color)
{
	{
		int iRed = GetRValue(color);
		int iBlue = GetBValue(color);
		int iGreen = GetGValue(color);

		int colortoreturn = (iRed * 65536) + (iGreen * 256) + iBlue;

		switch (colortoreturn)
		{
		case 16777215:
			return WHITE;
			break;
		case 255:
			return BLUE;
			break;
		case 16711680:
			return RED;
			break;
		case 65280:
			return GREEN;
			break;
		case 8421504:
			return MED_GRAY;
			break;
		case 16776960:
			return YELLOW;
			break;
		case 65535:
			return CYAN;
			break;
		case 16711935:
			return MAGENTA;
			break;
		case 39219:
			return 9;
			break;
		case 10066278:
			return 10;
			break;
		case 10092543:
			return 11;
			break;
		case 10079487:
			return 12;
			break;
		case 16711782:
			return 13;
			break;
		case 10040166:
			return 14;
			break;
		case 16764057:
			return 15;
			break;
		case 16751103:
			return 16;
			break;
		case 13382553:
			return 17;
			break;
		case 16737945:
			return 18;
			break;
		case 13158:
			return 19;
			break;
		case 3381708:
			return 20;
			break;
		case 10040217:
			return 21;
			break;
			break;
		case 13421772:
			return 23;
			break;

		}

	}
}

void Shape::fillColor1(int x, int y, int oldColor, int newcolor)
{
	// Base cases 

	if (retColor(GP142getPixel(x, y)) != oldColor)
	{
		return;
	}


	// Replace the color at (x, y) 
	GP142_pixelXY(newcolor, x, y);
	//screen[x][y] = newC;

	// Recur for north, east, south and west 
	fillColor1(x + 1, y, oldColor, newcolor);
	//fillColor(x - 1, y, oldColor, color);
	fillColor1(x, y + 1, oldColor, newcolor);
	//fillColor(x, y - 1, oldColor, color);
	fillColor1(x - 1, y, oldColor, newcolor);
	fillColor1(x, y - 1, oldColor, newcolor);
}

void Shape::fillColor2(int x, int y, int oldColor, int newcolor)
{
	// Base cases 

	if (retColor(GP142getPixel(x, y)) != oldColor)
	{
		return;
	}


	// Replace the color at (x, y) 
	GP142_pixelXY(newcolor, x, y);
	//screen[x][y] = newC;

	// Recur for north, east, south and west 
	fillColor2(x + 1, y, oldColor, newcolor);
	//fillColor(x - 1, y, oldColor, color);
	fillColor2(x, y - 1, oldColor, newcolor);
	//fillColor(x, y - 1, oldColor, color);
	fillColor2(x - 1, y, oldColor, newcolor);
}



//scane line filling method

//void Shape::fillColor1(int x, int y, int newColor, int oldColor)
//{
//	int tempx = x, tempy = y, left_x = x, right_x = x, mid_x;
//
//
//	while (retColor(GP142getPixel(tempx, tempy)) == newColor)
//	{
//		left_x = x;
//		right_x = x;
//
//		while (retColor(GP142getPixel(left_x, tempy)) == newColor)
//		{
//			left_x--;
//		}
//
//		while (retColor(GP142getPixel(right_x, tempy)) == newColor)
//		{
//			right_x++;
//		}
//
//		mid_x = (right_x + left_x) / 2;
//		for (int i = mid_x; i < right_x; i++)
//		{
//			GP142_pixelXY(oldColor, i, tempy);
//		}
//
//		for (int i = mid_x; i > left_x; i--)
//		{
//			GP142_pixelXY(oldColor, i, tempy);
//		}
//
//		tempy++;
//	}
//
//	tempy = y - 1;
//
//
//	while (retColor(GP142getPixel(tempx, tempy)) == newColor)
//	{
//		left_x = x;
//		right_x = x;
//		while (retColor(GP142getPixel(left_x, tempy)) == newColor)
//		{
//			left_x--;
//		}
//
//		while (retColor(GP142getPixel(right_x, tempy)) == newColor)
//		{
//			right_x++;
//		}
//
//		mid_x = (right_x + left_x) / 2;
//		for (int i = mid_x; i < right_x; i++)
//		{
//			GP142_pixelXY(oldColor, i, tempy);
//		}
//
//
//		for (int i = mid_x; i > left_x; i--)
//		{
//			GP142_pixelXY(oldColor, i, tempy);
//		}
//
//		tempy--;
//	}
//
//
//}

bool Shape::legalizeColor(int newColor, int fill_c)
{
	if (newColor == fill_c)
	{
		return false;
	}

	return true;
	
}



Shape::Shape()
{
}

Shape::Shape(int ps, int bc)
	:boundary_color(bc)
{
	points.resize(ps);	
}

void Shape::fillColor(int x, int y, int newColor)
{
	int oldColor = retColor(GP142getPixel(x, y));
	if (legalizeColor(newColor, oldColor) == true)
	{
		fillColor1(x, y, oldColor, newColor);
		//fillColor2(x, y - 1, oldColor, newColor);
	}
	
}

//void Shape::eraseShape(vector<Shape*> allShapes, int x, int y)
//{
//	Point p = { x, y };
//	for (int i = allShapes.size()-1; i >=0; i--)
//	{
//		if (allShapes[i]->contains(p) == true)
//		{
//			allShapes[i]->draw();
//			allShapes.erase(allShapes.begin() - i);
//			break;
//		}
//	}
//}

int& Shape::getBoundary()
{
	return boundary_color;
}

Shape::~Shape()
{
	cout << "NO" << endl;
}
//
//Fill::Fill(int bc, int ps, int x, int y)
//	:Shape(1, ps)
//{
//	points[0].x = x;
//	points[0].y = y;
//}
//
//
//void Fill::fillColor1(int x, int y, int oldColor, int newcolor)
//{
//	// Base cases 
//	Point p = { x, y };
//
//	if (retColor(GP142getPixel(x, y)) != oldColor )
//	{
//
//		for (int i = 1; i < points.size(); i++)
//		{
//			if (points[i].x == x || points[i].y == y)
//			{
//				points.push_back(p);
//			}
//		}	
//
//		return;
//	}
//
//
//	// Replace the color at (x, y) 
//	GP142_pixelXY(newcolor, x, y);
//	//screen[x][y] = newC;
//
//	// Recur for north, east, south and west 
//	Fill::fillColor1(x + 1, y, oldColor, newcolor);
//	//fillColor(x - 1, y, oldColor, color);
//	Fill::fillColor1(x, y + 1, oldColor, newcolor);
//	//fillColor(x, y - 1, oldColor, color);
//	Fill::fillColor1(x - 1, y, oldColor, newcolor);
//	Fill::fillColor1(x, y - 1, oldColor, newcolor);
//}
//
//void Fill::fillColor2(int x, int y, int oldColor, int newcolor)
//{
//	// Base cases 
//
//	if (retColor(GP142getPixel(x, y)) != oldColor)
//	{
//		return;
//	}
//
//
//	// Replace the color at (x, y) 
//	GP142_pixelXY(newcolor, x, y);
//	//screen[x][y] = newC;
//
//	// Recur for north, east, south and west 
//	Fill::fillColor2(x + 1, y, oldColor, newcolor);
//	//fillColor(x - 1, y, oldColor, color);
//	Fill::fillColor2(x, y - 1, oldColor, newcolor);
//	//fillColor(x, y - 1, oldColor, color);
//	Fill::fillColor2(x - 1, y, oldColor, newcolor);
//}
//
//void Fill::fillColor(int x, int y, int newColor)
//{
//	int oldColor = retColor(GP142getPixel(x, y));
//	if (legalizeColor(newColor, oldColor) == true)
//	{
//		Fill::fillColor1(x, y, oldColor, newColor);
//		//Shape::fillColor2(x, y - 1, oldColor, newColor);
//	}
//
//	boundary_color = newColor;
//
//}
//
//
//void Fill::draw()
//{
//	Fill::fillColor(points[0].x, points[0].y, boundary_color);
//}
//
//bool Fill::contains(Point & p)
//{
//	if (retColor(GP142getPixel(p.x, p.y)) == boundary_color)
//	{
//		return true;
//	}
//
//	return false;
//}
//
//int & Fill::getFill()
//{
//	return boundary_color;
//}
//
//int & Fill::getBoundary()
//{
//	return boundary_color;
//}
//
//
//
//void Fill::serialize(string & fname)
//{
//	ofstream file(fname, ios::app);
//	/*file.open(fname);
//	if (!file.fail())
//	{*/
//	file << endl << "class Fill" << endl;
//	file.write((char*)this, sizeof(*this));
//	//}
//}
//
//void Fill::deserialize(string & filename, istream & in)
//{
//	in.read((char*)this, sizeof(*this));
//}
//
//
//
//
//
//Fill::~Fill()
//{
//}
