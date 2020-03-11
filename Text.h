#pragma once
#include "Shape.h"
#include "GP142.H"
#include <string>
#include "Circle.h"

class Text :public Shape
{
	string str;
	void handle_kbd(char c);
	int check_length(string str);
	//void resizeString(char * &str);
	

public:

	Text();
	Text(const Text &obj);
	Text(int ps, int bc);
	void fillColor(int color);
	void draw();
	void changeColor(int color);
	void serialize(string &fname);
	bool contains(Point &p);
	void deserialize(istream & in);
	int &getBoundary();
	int& getFill();
	~Text();
};

