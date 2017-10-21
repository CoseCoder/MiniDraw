#pragma once
#include "Figure.h"
class Ellipse :public Figure
{
public:
	Ellipse(int start_point_x, int start_point_y, int end_point_x, int end_point_y, int width, QColor color);

	~Ellipse();

	void draw(QPainter &paint);
};