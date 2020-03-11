#include "Text.h"

#include <iostream>
using namespace std;


void Text::handle_kbd(char c)
{
	//GP142_printfXY(WHITE, 0, 0, TEXT_SIZE, "%c", c);
	str.push_back(c);
}

int Text::check_length(string str)
{
	int count = 0;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] > 'A' - 1 && str[i] < 'Z' + 1)
		{
			count++;
		}
	}

	return (str.length() * 7 + count * 2);
}

bool Text::contains(Point & p)
{
	int limit = abs(points[0].x) + check_length(str);

	for (int i = points[0].x; abs(i) <= limit ; i++)
	{
		for (int j = points[0].y; j <= 15 + points[0].y; j++)
		{
			if (p.x == i && p.y == j)
			{
				return true;
			}
		}
	}
	return false;
}

Text::Text()
{
}

Text::Text(const Text & obj)
{
	points = obj.points;
	boundary_color = BLACK;
	str = obj.str;
}

Text::Text(int ps, int bc)
	:Shape(1, bc)
{
	int mouse_x1, mouse_y1, num = 0;
	char key_pressed1;
	bool loop = true;
	bool mouse_click = false, range = false;
	char result[500];

	while (range == false)
	{

		switch (GP142_await_event(&mouse_x1, &mouse_y1, &key_pressed1))
		{
		case GP142_MOUSE:
			if (clickInRange(mouse_x1, mouse_y1) == true)
			{

				range = true;
				points[0].x = mouse_x1;
				points[0].y = mouse_y1;

				GP142_gets("Enter Text Here:", result);

				str = result;

			}

			break;

		case GP142_KBD:
			range = false;
		}
	}
}

void Text::fillColor(int color)
{
		
}

void Text::draw()
{

	char * result = new char[str.length() + 1];
	for (int i = 0; i < str.length(); i++)
	{
		result[i] = str[i];
	}
	result[str.length()] = '\0';

	if (boundary_color == BLACK)
	{
		for (int i = 0; i < 20; i++)
		{
			GP142_printfXY(boundary_color, points[0].x, points[0].y, 15, result);
			GP142_printfXY(boundary_color, points[0].x + 1, points[0].y, 15, result);
		}
			
	}

	for(int i=0; i<10; i++)
	GP142_printfXY(boundary_color, points[0].x, points[0].y, 15, result);

	delete [] result;
	
}

void Text::changeColor(int color)
{
}


void Text::serialize(string & fname)
{
	ofstream file(fname, ios::app);
	file << endl << "class Text" << endl;

	file.write((char*)&boundary_color, sizeof(boundary_color));

	file << str << endl;
	file.write((char*)&points[0], sizeof(points[0]));
	

}

void Text::deserialize(istream & in)
{
	char arr[500];
	in.read((char*)&boundary_color, sizeof(boundary_color));	
	in.getline(arr, 500);
	str = arr;
	points.resize(1);

	in.read((char*)&points[0], sizeof(points[0]));

}

int & Text::getBoundary()
{

	return boundary_color;
}

int & Text::getFill()
{
	int a = -1;
	// TODO: insert return statement here
	return a;
}

Text::~Text()
{
}
