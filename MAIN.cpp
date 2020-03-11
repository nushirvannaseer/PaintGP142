#include <Windows.h>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <vector> 
#include <iostream>
#include "Polygon.h"
#include "Shape.h"
#include "Circle.h"
#include "Triangle.h"
#include "nPolygon.h"
#include "Rect.h"
#include "OpenShape.h"
#include "Text.h"
#include "GP142.h"


//
//#define circlemac 0
//#define linemac 1
//#define trianglemac 2
//#define rectanglemac 3
//#define textmac 4
//#define npolygonmac 5
//#define curvemac 6
////#define circlemac 7
////#define circlemac 8
////#define circlemac 9



#define solidline 0
#define dottedline 1
#define solidcurve 2
#define dottedcurve 3
#define rectangle 4
#define triangle 5
#define npolygon 6
#define circle 7
#define textbox 8
#define eraser 9
#define floodfill 10
#define save 11
#define newcanvas 12
#define load 13


#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20

using namespace std;


//A) DRAWING FUNCTIONS
//the two drawing functions that you will use to make all shapes
void draw_line(int x1, int y1, int x2, int y2, int color = WHITE, int width = 1) 
{
	GP142_lineXY(color, x1, y1, x2, y2, width);
}

void draw_circle(int x, int y, int radius, int color = GREEN) 
{
	GP142_circleXY(color, x, y, radius);
}

//B) EVENT HANDLERS
//Mouse handler
void handle_mouse(int x, int y) 
{
	GP142_printfXY(YELLOW, 0, 0, 9, "Mouse at (%d,%d)", x, y);
}

//Keyboard handler
void handle_kbd(char c)
{
	//put the character anywhere you want to.
	//I'm putting it on the origin
	GP142_printfXY(WHITE, 0, 0, TEXT_SIZE, "%c", c);
}

//periodic handler you will not need to use because we're not doing animation
void demo_handle_periodic(void) {};


//for making a line manually
void manualLine(int mouse_x1, int mouse_y1, int mouse_x2, int mouse_y2, int color_to_set, int width)
{
	width--;
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
			if (double(i % 3) == 0 || double(-i % 3) == 0)
			{
				int j = 0;
				j = (gradient*i) + y_intercept;
				int h = i; int k = j;

				GP142_pixelXY(color_to_set, i, j);
				GP142_pixelXY(color_to_set, i, j+width);
				GP142_pixelXY(color_to_set, i, j-width);
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
			if (double(i % 5) != 0)
			{
				GP142_pixelXY(color_to_set, mouse_x1, i);
				GP142_pixelXY(color_to_set, mouse_x1+width, i);
				GP142_pixelXY(color_to_set, mouse_x1-width, i);
			}


		}
	}

}


int retColor(COLORREF color)
{
	int iRed = GetRValue(color);
	int iBlue = GetBValue(color);
	int iGreen = GetGValue(color);

	int colortoreturn = (iRed * 65536) + (iGreen * 256) + iBlue;

	switch (colortoreturn)
	{
	case 16777215://
		return WHITE;
		break;
	case 255://
		return BLUE;
		break;
	case 16711680://
		return RED;
		break;
	case 65280://
		return GREEN;
		break;
	case 8421504://
		return MED_GRAY;
		break;
	case 16776960://
		return YELLOW;
		break;
	case 65535://
		return CYAN;
		break;
	case 16711935://
		return MAGENTA;
		break;
	case 10027212:
		return 8;
	case 10053273:
		return 10;
		break;
		break;
	case 13209:
		return 9;
		break;
	case 10092492:
		return 12;
		break;
	case 10092543://was 11 before dunno y
		return 11;
		break;
	case 16737792:
		return 13;
		break;
	case 10053171:
		return 14;
		break;
	case 16751052:
		return 15;
		break;
	case 16777113:
		return 16;
		break;
	case 13408563:
		return 17;
		break;
	case 16750950:
		return 18;
		break;
	case 26163:
		return 19;
		break;
	case 3394713:
		return 20;
		break;
	case 10066227:
		return 21;
		break;
	case 0:
		return 0;
		break;
		break;
	case 13421772:
		return 23;
		break;

	}

}

void fillColor1(int x, int y, int oldColor, int newcolor)
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


	/*fillColor1(x+1, y - 1, oldColor, newcolor);
	fillColor1(x+1, y + 1, oldColor, newcolor);
	fillColor1(x-1, y - 1, oldColor, newcolor);
	fillColor1(x-1, y + 1, oldColor, newcolor);*/


}

void fillColorArr(int x, int y, int oldColor, int newcolor/*, vector<colors> &vec_col*/)
{
	// Base cases 

	if (retColor(GP142getPixel(x, y)) != oldColor)
	{
		return;
	}
	/*if (retColor(GP142getPixel(x-1, y-1)) != oldColor)
	{
		return;
	}
	if (retColor(GP142getPixel(x, y - 1)) != oldColor)
	{
		return;
	}
	if (retColor(GP142getPixel(x - 1, y)) != oldColor)
	{
		return;
	}*/

	if (x <= -400 || y < -200 || x>493 || y>363)
	{
		return;
	}
	GP142_pixelXY(newcolor, x, y);

	//// Replace the color at (x, y) 
	//GP142_pixelXY(newcolor, x, y);
	//Point * p = new Point{ double(x), double(y) };
	//colors * c = new colors;
	//c->col = newcolor;
	//c->p.x = x;
	//c->p.y = y;
	//vec_col.push_back(*c);

	//screen[x][y] = newC;

	// Recur for north, east, south and west 
	fillColorArr(x + 1, y, oldColor, newcolor);
	//fillColor(x - 1, y, oldColor, color);
	fillColorArr(x, y + 1, oldColor, newcolor);
	//fillColor(x, y - 1, oldColor, color);
	fillColorArr(x - 1, y, oldColor, newcolor);
	fillColorArr(x, y - 1, oldColor, newcolor);
}

void fillColorScan(int x, int y, int currentAppliedColor, int currentSeletedColor)
{
	int tempx = x, tempy = y, extremeLeftX = x, extremeRightX = x, midX = x;


	while (retColor(GP142getPixel(midX, tempy)) == currentAppliedColor)
	{
		extremeLeftX = midX;
		extremeRightX = midX;
		while (retColor(GP142getPixel(extremeLeftX, tempy)) == currentAppliedColor)
		{
			extremeLeftX--;
		}

		while (retColor(GP142getPixel(extremeRightX, tempy)) == currentAppliedColor)
		{
			extremeRightX++;
		}

		midX = (extremeRightX + extremeLeftX) / 2;
		for (int i = midX; i < extremeRightX; i++)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		for (int i = midX; i > extremeLeftX; i--)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		tempy++;
	}

	tempy = y - 1;
	midX = x;

	while (retColor(GP142getPixel(midX, tempy)) == currentAppliedColor)
	{
		extremeLeftX = midX;
		extremeRightX = midX;
		while (retColor(GP142getPixel(extremeLeftX, tempy)) == currentAppliedColor)
		{
			extremeLeftX--;
		}

		while (retColor(GP142getPixel(extremeRightX, tempy)) == currentAppliedColor)
		{
			extremeRightX++;
		}

		midX = (extremeRightX + extremeLeftX) / 2;
		for (int i = midX; i < extremeRightX; i++)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		for (int i = midX; i > extremeLeftX; i--)
		{
			GP142_pixelXY(currentSeletedColor, i, tempy);

		}
		//GP142_flush();

		tempy--;
	}

	//fillColor2(x - 1, y, currentAppliedColor, currentSeletedColor);
	//fillColor2(x + 1, y, currentAppliedColor, currentSeletedColor);
}

void draw_rectangle(int x1, int y1, int x2, int y2, int boundary_color)
{
	draw_line(x1, y1, x2, y1, boundary_color, 3);
	draw_line(x1, y1, x1, y2, boundary_color, 3);
	draw_line(x1, y2, x2, y2, boundary_color, 3);
	draw_line(x2, y2, x2, y1, boundary_color, 3);

	//fillColor1((x2 + x1) / 2, (y2 + y1) / 2, boundary_color, WHITE);
}

bool legalizeColor(int newColor, int fill_c)
{
	if (newColor == fill_c)
	{
		return false;
	}

	return true;

}

bool fill_Color_Tool(/*vector<vector<colors>> &vec_col,*/ int newColor, vector<Shape *> &allshapes)
{
	int x=0, y=0, oldColor=BLACK;
	char key;
	string str;
	char type[30];
	bool inShape = false;
	Point p;
	switch (GP142_await_event(&x, &y, &key))
	{
	case GP142_MOUSE:


		p = { double(x), double(y) };

		for (int i = allshapes.size()-1; i >=0 ; i--)
		{
			str = typeid(*(allshapes[i])).name();
			if ((str == "class line" || str == "class curve" || str=="class Text") && allshapes[i]->contains(p)==true)
			{
				allshapes[i]->getBoundary() = newColor;
				allshapes[i]->draw();
				return true;
			}

		}


		oldColor = retColor(GP142getPixel(x, y));
		if (legalizeColor(newColor, oldColor) == true)
		{

			fillColorArr(x, y, oldColor, newColor);			
			/*vec_col.resize(vec_col.size() + 1);*/
			
			return true;
		}	

		else {
			return false;
		}

		break;

	case GP142_KBD:

		return false;
		break;
	}

	
}

//bool eraserTool(vector<Shape*> &allshapes, vector<vector<colors>> &col_array)
//{
//	//int x = 0, y = 0, oldColor;
//	//char key; bool erased = false;
//	//vector<Shape *> black_shape;
//	//int to_draw_black = 0;
//	//	
//	//switch (GP142_await_event(&x, &y, &key))
//	//{
//	//case GP142_MOUSE:		
//
//	//	for (int i = allshapes.size() - 1, m=0; i >= 0; i--, m++)
//	//	{
//	//		Point p = { x, y };
//	//		black_shape.resize(m + 1);
//	//		black_shape[m] = allshapes[i];
//
//	//		int xmax, ymax, xmin, ymin;
//
//	//		if (allshapes[i]->contains(p) == true)
//	//		{
//	//			/*string str = typeid(*(allshapes[i])).name();
//	//			if (str == "class Circle")
//	//			{
//	//				xmax = allshapes[i]->points[0].x + radius;
//
//	//			}*/
//
//	//			//for(int i=0; i<allshapes[i])
//	//						   				 			  			  			 		   
//	//			to_draw_black = m;
//	//			erased = true;
//
//	//			for (int j = 0; j < col_array.size(); j++)
//	//			{
//	//				for (int k = 0; k < col_array[j].size(); k++)
//	//				{
//	//					Point b = { col_array[j][k].p.x, col_array[j][k].p.y };
//	//					if (allshapes[i]->contains(b) == true)
//	//					{
//	//						for (int n = i - 1; n >= 0; n--)
//	//						{
//
//	//							if (allshapes[n]->contains(b) != true || i == 0)
//	//							{
//	//								GP142_pixelXY(BLACK, b.x, b.y);
//	//								col_array[j][k].col = BLACK;
//	//							}
//
//	//						}
//
//	//						if (i == 0)
//	//						{
//	//							GP142_pixelXY(BLACK, b.x, b.y);
//	//							col_array[j][k].col = BLACK;
//	//						}
//
//	//					}
//	//				}
//	//			}
//
//	//			black_shape[m]->getFill() = BLACK;
//	//			black_shape[m]->getBoundary() = BLACK;
//
//	//			allshapes.erase(allshapes.begin()+i);
//	//			break;
//	//			
//
//	//		}	
//	//		
//	//		
//	//	}
//
//	//	if (erased != true)
//	//	{
//	//		return false;
//	//	}
//
//	//	black_shape[to_draw_black]->draw();
//
//	//	for (int i = 0; i < allshapes.size(); i++)
//	//	{
//	//		allshapes[i]->draw();
//	//	}
//
//
//
//
//	//	break;
//
//	//case GP142_KBD:
//	//	break;
//	//}
//
//
//	//
//	//return true;
//	//*/
//
//}


bool eraserTool(Point &p, vector<Shape*> &allShapes)
{
	bool shape_contains_this_point = false;

	Shape *shapeToBeDeleted = nullptr;
	int indexOfShapeToBeDeleted;
	for (int i = allShapes.size() - 1; i >= 0; i--)
	{
		if (allShapes[i]->contains(p) == true)
		{
			shape_contains_this_point = true;
			shapeToBeDeleted = allShapes[i];
			indexOfShapeToBeDeleted = i;
			break;
		}
	}


	if (shape_contains_this_point == false)
	{
		fillColor1(p.x, p.y, retColor(GP142getPixel(p.x, p.y)), BLACK);
	}

	if (shapeToBeDeleted == nullptr)
		return false;

	string shapeName = typeid(*(shapeToBeDeleted)).name();
	int minX = shapeToBeDeleted->points[0].x;
	int maxX = shapeToBeDeleted->points[0].x;
	int minY = shapeToBeDeleted->points[0].y;
	int maxY = shapeToBeDeleted->points[0].y;

	if (shapeName == "class line" || shapeName == "class curve")
	{
		shapeToBeDeleted->boundary_color = BLACK;
		shapeToBeDeleted->draw();

		allShapes.erase(allShapes.begin() + indexOfShapeToBeDeleted);
		for (int i = 0; i < allShapes.size(); i++)
			allShapes[i]->draw();

		return true;
	}
	else if (shapeName == "class Circle")
	{
		int radius = sqrt(pow(shapeToBeDeleted->points[1].x - shapeToBeDeleted->points[0].x, 2) + pow(shapeToBeDeleted->points[1].y - shapeToBeDeleted->points[0].y, 2));
		maxX = shapeToBeDeleted->points[0].x + radius;
		minX = shapeToBeDeleted->points[0].x - radius;

		maxY = shapeToBeDeleted->points[0].y + radius;
		minY = shapeToBeDeleted->points[0].y - radius;


	}
	else if (shapeName == "class Text")
	{
		shapeToBeDeleted->boundary_color = BLACK;
		for (int i = 0; i < 10; i++)
			shapeToBeDeleted->draw();

		allShapes.erase(allShapes.begin() + indexOfShapeToBeDeleted);
		for (int i = 0; i < allShapes.size(); i++)
			allShapes[i]->draw();

		return true;
	}
	else
	{


		for (int i = 0; i < shapeToBeDeleted->points.size(); i++)
		{
			if (shapeToBeDeleted->points[i].x > maxX)
				maxX = shapeToBeDeleted->points[i].x;

			if (shapeToBeDeleted->points[i].x < minX)
				minX = shapeToBeDeleted->points[i].x;

			if (shapeToBeDeleted->points[i].y > maxY)
				maxY = shapeToBeDeleted->points[i].y;

			if (shapeToBeDeleted->points[i].y < minY)
				minY = shapeToBeDeleted->points[i].y;
		}
	}
	//GP142_rectangleXY(BLACK, minX, minY, maxX, maxY, 2);
	//GP142_flush();
	shapeToBeDeleted->boundary_color = BLACK;
	shapeToBeDeleted->draw();


	Point tempPoint;
	//bool pointFoundInAnotherShape = false;
	for (int x = minX; x <= maxX; x++)
	{
		for (int y = minY; y <= maxY; y++)
		{
			//pointFoundInAnotherShape = false;
			tempPoint = { double(x),double(y) };

			if (shapeToBeDeleted->contains(tempPoint) == true && x > -700 && y > -295)
			{
				if (indexOfShapeToBeDeleted == 0)
				{
					GP142_pixelXY(BLACK, x, y);
				}

				for (int i = indexOfShapeToBeDeleted - 1; i >= 0; i--)
				{

					if (allShapes[i]->contains(tempPoint) == false)
					{
						GP142_pixelXY(BLACK, x, y);

						break;
					}

				}
			}
			//GP142_pixelXY(WHITE, x, y);
		/*{
			for (int i = 0; i < allShapes.size(); i++)
			{
				if (i == indexOfShapeToBeDeleted)
					continue;

				if (allShapes[i]->contains(tempPoint) == true)
				{
					pointFoundInAnotherShape = true;
					break;
				}
			}
		}*/

		//if (pointFoundInAnotherShape == true)
		//	continue;
		//else
		//{
			//GP142_pixelXY(WHITE, x, y);
		//}
		}
	}
	allShapes.erase(allShapes.begin() + indexOfShapeToBeDeleted);
	for (int i = 0; i < allShapes.size(); i++)
		allShapes[i]->draw();



	return shape_contains_this_point;


}

void drawcircle(int centrex, int centrey, int radius, int boundaryColor)
{
	int ycoord1 = 0, ycoord2 = 0;
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
		ycoord2 = (-1 * sqrt(pow(radius, 2) - pow(centrex - i, 2))) + centrey;
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
}

void setTool(int tool, int &box_selected)
{
	box_selected = tool;

	if (tool < 10)
	{
		for (int i = 363, j = 0; i >= -200 + 56; i -= 56, j++)
		{
			if (j == box_selected)
			{
				draw_rectangle(-492, i, -400, i - 56, YELLOW);
				break;
			}
			else
			{
				draw_rectangle(-492, i, -400, i - 56, WHITE);
			}

		}
	}


	else if (tool == 10)
	{
		draw_rectangle(103, -200, 103 + 130, -300, YELLOW);
	}

	else if (tool == 11)
	{
		draw_rectangle(103+130, -200, 103 + 130+130, -300, YELLOW);
	}

	else if (tool == 12)
	{
		draw_rectangle(103+130+130, -200, 103 + 130+130+130+130, -300, YELLOW);
	}

}

void loadFromFile(vector<Shape*> &AllShapes, string &file, vector<vector<int>> &color_array)
{	

	AllShapes.clear();

	char typ[25];
	ifstream fin(file);

	if (fin.peek() == std::ifstream::traits_type::eof() == true)
	{
		return;
	}

	if (fin.fail())
	{
		return;
	}



	int size;
	char get;
	fin >> size;
	AllShapes.resize(size);
	fin.ignore(1);
	string type;


	for (int i = 0; i < 2*AllShapes.size(); i++)
	{
		fin.getline(typ, 25);
		type = typ;
		if (type == "class Circle")
		{
			Circle * temp = new Circle;
			temp->deserialize(fin);
			AllShapes[i/2] = temp;
		}

		else if (type == "class Triangle")
		{
			Triangle * temp = new Triangle;
			temp->deserialize(fin);
			AllShapes[i/2] = temp;
		}

		else if (type == "class Rectangle")
		{
			Rect * temp = new Rect;
			temp->deserialize(fin);
			AllShapes[i/2] = temp;
		}

		else if (type == "class line")
		{
			line * temp = new line;
			temp->deserialize(fin);
			AllShapes[i/2] = temp;
		}

		else if (type == "class curve")
		{
			curve * temp = new curve;
			temp->deserialize( fin);
			AllShapes[i/2] = temp;
		}

		else if (type == "class Text")
		{
			Text * temp = new Text;
			temp->deserialize(fin);
			AllShapes[i/2] = temp;
		}

		else if (type == "class nPolygon")
		{
			nPolygon * temp = new nPolygon;
			temp->deserialize(fin);
			AllShapes[i/2] = temp;
		}

		
	}

	GP142_clear();
	
	//int size1, size2;
	//fin >> size1;
	//color_array.resize(size1);
	//for (int i = 0; i < size1; i++)
	//{
	//	fin >> size2;
	//	color_array[i].resize(size2);
	//}
	//
	//int x, y, col;
	int num; //char g;
	//fin >> g;

	for (int i = 0; i < 894; i++)
	{
		for (int j = 0; j < 564; j++)
		{
			fin >> num;
			color_array[i][j] = num;
			GP142_pixelXY(color_array[i][j], i-399, 363-j);
		}
		//in >> endl;
	}


	//for (int i = 0; i < color_array.size(); i++)
	//{
	//	for (int j = 0; j < color_array[i].size(); j++)
	//	{
	//		
	//		//GP142_pixelXY(color_array[i][j],j - 399, 363 - i);
	//		fin >> x;
	//		color_array[i][j].p.x = x;
	//		fin >> y;
	//		color_array[i][j].p.y = y;
	//		fin >> col;
	//		color_array[i][j].col = col;
	//		GP142_pixelXY(color_array[i][j].col, color_array[i][j].p.x, color_array[i][j].p.y);
	//	}
	//}

	for (int i = 0; i < AllShapes.size(); i++)
	{
		AllShapes[i]->draw();
	}

}

void saveToFile(vector<Shape*> &AllShapes, string &file, vector<vector<int>> & color_array)
{

	std::ofstream ofs;
	ofs.open(file, std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	ofstream fout(file, ios::app);
	fout.flush();
	fout << AllShapes.size() << endl;

	for (int i = 0; i < AllShapes.size(); i++)
	{
		AllShapes[i]->serialize(file);
	}


	for (int i = -399; i <= 493; i++)
	{
		for (int j = 363; j >= -200; j--)
		{
			color_array[i+399][363-j] = retColor(GP142getPixel(i, j));
		}
	}


	fout << endl;
	for (int i = 0; i <894 ; i++)
	{
		for (int j = 0; j < 564; j++)
		{			
			fout << color_array[i][j] << " ";
		}
		//fout << endl;
	}


}


int main()
{
	int quit = 0;           /* has user signaled quit yet?                      */
	int mouse_x, mouse_y;
	char key_pressed;
	int boundary_color = WHITE, fill_color = BLACK;
	vector <Shape*> AllShapes;
	int AllShapeSize = 0;
	int current_tool;
	bool color_type = true;//true for boundary, false for fill
	int box_selected = 100;
	bool clear = false;
	int circle_made = 0, first_run = 0;
	string file("C:\\Users\\Acer\\Desktop\\all.txt");

	//vector<vector<colors>> filled(1);
	vector<vector<int>> filled(894);
	for (int i = 0; i < 894; i++)
	{
		filled[i].resize(564);
	}
	
	GP142_open();
	   	 	

	while (quit == 0)
	{

		if (clear == true)
		{
			for (int i = 0; i < AllShapes.size() && AllShapes[i]!=nullptr; i++)
			{
				AllShapes[i]->draw();
			}
		}

		clear = false;
		

		if (quit == 0)
		{

			if (circle_made == 1 ||first_run==0)
			{

				for (int i = -492; i <= -400; i++)
				{
					for (int j = 365; j >= -365; j--)
					{
						GP142_pixelXY(BLACK, i, j);
					}
				}

				for (int i = -401; i <= 492; i++)
				{
					for (int j = -200; j >= -340; j--)
					{
						GP142_pixelXY(BLACK, i, j);
					}
				}


				draw_line(-492, -200, 492, -200, WHITE, 3);

				draw_line(-492, -300, 492, -300, WHITE, 3);
				draw_line(-492, -200, -492, -300, WHITE, 5);
				draw_line(103, -200, 103, -300, WHITE, 3);


				for (int i = -492; i <= 103; i += 46)
				{
					draw_line(i, -200, i, -300, WHITE, 2);
				}
				draw_line(-492, -250, 103, -250, WHITE, 2);



				int color = 0;

				for (int i = -443; i <= 103; i++)
				{
					if (i == -354 || i == -308 || i == -262 || i == -216 || i == -170 || i == -124 || i == -78 || i == -32 || i == 14 || i == 60)
					{
						i += 3;
						color++;
					}

					if (i == -401)
					{
						i += 4;
						color++;

					}

					for (int j = -203; j > -248; j--)
					{
						GP142_pixelXY(color, i - 1, j);

					}



				}

				color++;

				for (int i = -443; i <= 103; i++)
				{
					if (i == -354 || i == -308 || i == -262 || i == -216 || i == -170 || i == -124 || i == -78 || i == -32 || i == 14 || i == 60)
					{
						i += 3;
						color++;
					}

					if (i == -400)
					{
						i += 3;
						color++;
					}

					for (int j = -252; j > -298; j--)
					{
						GP142_pixelXY(color, i - 1, j);
					}

				}


				{
					draw_line(-470, 320, -430, 350, WHITE, 2);//line

					manualLine(-470, 264, -430, 294, WHITE, 2);//dotted line

					draw_line(-480, 208, -460, 238, WHITE, 2);// curve using line
					draw_line(-460, 238, -440, 208, WHITE, 2);//curve using line
					draw_line(-440, 208, -420, 238, WHITE, 2);//curve using line

					manualLine(-480, 152, -460, 182, WHITE, 2);// curve using line
					manualLine(-460, 182, -440, 152, WHITE, 2);//curve using line
					manualLine(-440, 152, -420, 182, WHITE, 2);//curve using line

					draw_rectangle(-470, 127, -430, 97, WHITE);//drawing rectangle

					//drawing a triangle
					draw_line(-475, 35, -422, 35, WHITE, 2);
					draw_line(-475, 35, -448, 75, WHITE, 2);
					draw_line(-448, 75, -422, 35, WHITE, 2);

					//drawing an n-sided polygon
					draw_line(-475, -20, -422, -20, WHITE, 2);
					draw_line(-475, -20, -475, -5, WHITE, 2);
					draw_line(-422, -20, -422, -5, WHITE, 2);
					draw_line(-475, -5, -448, 10, WHITE, 2);
					draw_line(-422, -5, -448, 10, WHITE, 2);


					//drawing a circle
					drawcircle(-448, -56, 20, WHITE);

					//text
					GP142_printfXY(WHITE, -460, -138, 40, "T");

					//eraser

					draw_rectangle(-457, -160, -435, -180, WHITE);
					draw_rectangle(-453, -160, -438, -155, WHITE);

				}
			}

			circle_made = 0;			
			first_run = 1;


			draw_line(-492, -300, 492, -300, WHITE, 3);
			draw_line(492, -200, 492, -300, WHITE, 3);

			if (color_type == false)
			{
				GP142_printfXY(WHITE, -492, -215, 9, " Boundary \n    Color");
				GP142_printfXY(ORANGE, -492, -265, 9, "      Fill \n    Color");
			}
			else
			{
				GP142_printfXY(ORANGE, -492, -215, 9, " Boundary \n    Color");
				GP142_printfXY(WHITE, -492, -265, 9, "      Fill \n    Color");
			}

			draw_line(-492, -227, -446, -227, WHITE, 2);
			draw_line(-492, -279, -446, -279, WHITE, 2);

			for (int i = -489; i < -447; i++)
			{
				for (int j = -229; j >= -248; j--)
				{
					GP142_pixelXY(boundary_color, i, j);
				}

				for (int j = -281; j > -299; j--)
				{
					GP142_pixelXY(fill_color, i, j);
				}

			}

			for (int i = 363; i >= -200 + 56; i -= 56)
			{
				draw_rectangle(-492, i, -400, i - 56, WHITE);				
			}
			
			


			for (int i = 103; i <= 492; i+=130)
			{
				draw_rectangle(i, -200, i+130, -300, WHITE);
			}


			

			draw_line(130, -260, 155, -230, WHITE, 3);
			draw_line(165, -275, 190, -245, WHITE, 3);
			draw_line(155, -230, 190, -245, WHITE, 3);
			draw_line(130, -260, 165, -275, WHITE, 3);
			draw_line(190, -245, 195, -250, WHITE, 2);
			draw_line(195, -250, 183, -255, WHITE, 2);
			draw_circle(200, -260, 5, fill_color);
			drawcircle(200, -260, 6, WHITE);
			//fillColorScan(160, -240, BLACK, WHITE);
			fillColorScan(160, -240, BLACK, LT_GRAY);

			GP142_printfXY(GREEN, 250, -240, 20, "    SAVE");
			draw_line(233, -250, 363, -250, WHITE, 2);
			GP142_printfXY(GREEN, 250, -290, 20, "    LOAD");
			GP142_printfXY(GREEN, 250+130, -270, 30, " NEW");


		}


		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed))
		{
		case GP142_MOUSE:			

			if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 363 && mouse_y >= 307)//solid line
			{
				current_tool = solidline;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new line(2, boundary_color, true, fill_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;


			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 306 && mouse_y >= 251)//dotted line
			{
				current_tool = dottedline;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new line(2, boundary_color, false, fill_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;

			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 250 && mouse_y >= 195)//solid curve
			{
				current_tool = solidcurve;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new curve(1, boundary_color, true, fill_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 194 && mouse_y >= 139)//dotted curve
			{
				current_tool = dottedcurve;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new curve(1, boundary_color, false, fill_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 138 && mouse_y >= 83)//rectangel
			{
				current_tool = rectangle;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new Rect(2, boundary_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 82 && mouse_y >= 27)//Triangle
			{
				current_tool = triangle;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new Triangle(3, boundary_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 26 && mouse_y >= -29)//nPolygon
			{
				current_tool = npolygon;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new nPolygon(3, boundary_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= -30 && mouse_y >= -85)//Circle
			{
				current_tool = circle; circle_made = 1;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new Circle(boundary_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= -86 && mouse_y >= -141)//Text
			{
				current_tool = textbox;
				setTool(current_tool, box_selected);
				AllShapes.resize(AllShapeSize + 1);
				AllShapes[AllShapeSize] = new Text(1, boundary_color);
				AllShapes[AllShapeSize]->draw();

				AllShapeSize++;
			}

			else if (mouse_x >= -490 && mouse_x <= -400 && mouse_y <= 18 && mouse_y >= -197)//Eraser
			{
				current_tool = eraser;
				setTool(current_tool, box_selected);

				int x = 0, y = 0, oldColor;			
				char key;

				switch (GP142_await_event(&x, &y, &key))
				{
				case GP142_MOUSE:

					Point p = { double(x), double(y) };
					if (eraserTool(p, AllShapes) == true)
					{
						AllShapeSize--;
						circle_made = 1;
					}

				}
				
			}

			else if (mouse_x >= -490 && mouse_x <= -444 && mouse_y >= -249 && mouse_y <= -200)
			{
				color_type = true;//boundary color
				GP142_printfXY(YELLOW, -492, -215, 9, " Boundary \n    Color");
				GP142_printfXY(WHITE, -492, -265, 9, "      Fill \n    Color");


			}

			else if (mouse_x >= -490 && mouse_x <= -444 && mouse_y >= -300 && mouse_y <= -250)
			{
				color_type = false;//fill color
				GP142_printfXY(WHITE, -492, -215, 9, " Boundary \n    Color");
				GP142_printfXY(YELLOW, -492, -265, 9, "      Fill \n    Color");


			}

			else if (mouse_x >= -443 && mouse_x < 103 && mouse_y >= -300 && mouse_y <= -200)
			{
				int color_selected = retColor(GP142getPixel(mouse_x, mouse_y));
				
				if (color_type == true)
				{
					boundary_color = color_selected;
				}

				else
				{
					fill_color = color_selected;
				}


			}

			else if (mouse_x >= 103 && mouse_x <= 232 && mouse_y >= -360 && mouse_y <= -200)//flood fill
			{

				current_tool = floodfill;
				setTool(current_tool, box_selected);
				
				if (fill_Color_Tool(fill_color, AllShapes) == true)
				{
					//AllShapeSize++;
				}
			}

			else if (mouse_x>=233 && mouse_x <= 363 && mouse_y>=-250 && mouse_y <= -200)//save
			{
				current_tool = save;
				setTool(current_tool, box_selected);
				saveToFile(AllShapes, file, filled);


			}

			else if (mouse_x >= 233 && mouse_x <= 363 && mouse_y >= -360 && mouse_y <= -250)//load
			{
				current_tool = load;
				setTool(current_tool, box_selected);
				loadFromFile(AllShapes, file, filled);
				AllShapeSize = AllShapes.size();
				
				first_run = 0;


			}

			else if (mouse_x >= 364 && mouse_x <= 493 && mouse_y >= -360 && mouse_y <= -200)//new canvas
			{
				current_tool = newcanvas;
				setTool(current_tool, box_selected);
				AllShapes.clear();
				AllShapeSize = 0;
				GP142_clear();
				first_run = 0;

			}


			else
			{

				quit = 0;

			}


			break;

		case GP142_QUIT:
			quit = 1;
			break;
		}
	
	}	
}