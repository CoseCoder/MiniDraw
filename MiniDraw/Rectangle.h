#pragma once
#include "Figure.h"
class Rectangle :public Figure
{
public:
	Rectangle(int start_point_x, int start_point_y, int end_point_x, int end_point_y, int width, QColor color);

	~Rectangle();

	void draw(QPainter &paint);
};