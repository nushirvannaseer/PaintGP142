#pragma once
#include "Shape.h"
#include "GP142.H"

class OpenShape :public Shape
{
protected:
	bool style;//whether line is solid or dotted
	
	void draw_line(int x1, int y1, int x2, int y2, int color=WHITE, int width=1);
public:
	OpenShape();
	OpenShape(int ps, int bc, bool s);
	virtual void draw() = 0;
	virtual void fillColor(int x, int y, int color) = 0;
	virtual bool contains(Point &p) = 0;
	virtual void serialize(string &fname) = 0;
	virtual void deserialize(istream & in) = 0;
	int & getFill();
	virtual ~OpenShape();
};

class line :public OpenShape
{
	int bg_color;
public:
	line();
	line(int ps, int bc, bool s, int bg=0);
	void draw();
	bool contains(Point &p);
	void fillColor(int x, int y,int color);
	void serialize(string &fname);
	int &getBoundary();
	void deserialize(istream & in);

	~line();
};

class curve :public OpenShape
{
	int bg_color;
public:
	curve();
	curve(int pc, int bc, bool s, int bg = 0);
	void draw();
	void serialize(string &fname);
	void deserialize(istream & in);
	bool contains(Point &p);
	int &getBoundary();
	void fillColor(int x, int y, int color);
	~curve();
};