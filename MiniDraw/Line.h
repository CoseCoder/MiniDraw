#pragma once
#include "Figure.h"
class Line :public Figure
{
public:
	Line(int start_point_x, int start_point_y, int end_point_x, int end_point_y, int width, QColor color);

	~Line();

	void draw(QPainter &paint);
};