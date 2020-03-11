#pragma once
#include <vector>
#include "GP142.H"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Point
{
	double x, y;
};


struct colors
{
	int col;
	Point p;

	bool operator ==(const colors &obj)
	{
		if (col == obj.col && p.x == obj.p.x && p.y == obj.p.y)
		{
			return true;
		}

		else
		{
			return false;
		}
	}


};


class Shape
{
protected:

	vector <Point> points;
	int boundary_color;
	void highlightPixel(int mousex, int mousey, int color);
	bool clickInRange(int mouse_x, int mouse_y);
	void manualLine(int mouse_x1, int mouse_y1, int mouse_x2, int mouse_y2, int color_to_set, int width = 1);
	int retColor(COLORREF color);
	void fillColor1(int x, int y, int oldColor, int newcolor = 0);
	void fillColor2(int x, int y, int oldColor, int newcolor = 0);
	bool legalizeColor(int newColor, int fill_color);
	friend bool eraserTool(Point &p, vector<Shape*> &allShapes);

public:

	Shape();
	Shape(int ps, int bc=1);
	virtual void fillColor(int x, int y, int newColor);
	virtual void draw() = 0;
	virtual bool contains(Point &p) = 0;
	//void eraseShape(vector<Shape*>, int x, int y);
	//void eraser(vector<Point> points)
	virtual int& getFill() = 0;
	int& getBoundary();
	virtual void serialize(string &fname) = 0;
	virtual void deserialize(istream & in) = 0;
	

	virtual ~Shape();
};



//class Fill : public Shape
//{
//public:
//	Fill(int bc, int ps, int x, int y);
//
//	void fillColor(int x, int y, int newColor);
//	void fillColor1(int x, int y, int oldColor, int newcolor);
//	void fillColor2(int x, int y, int oldColor, int newcolor);
//	void draw();
//	bool contains(Point &p);
//	//void eraseShape(vector<Shape*>, int x, int y);
//	//void eraser(vector<Point> points)
//	int& getFill();
//	int& getBoundary();
//	void serialize(string &fname);
//	void deserialize(string &filename, istream & in);
//
//
//	~Fill();
//};
