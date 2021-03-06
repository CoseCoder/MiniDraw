#include "Ellipse.h"

Ellipse::Ellipse(int start_point_x, int start_point_y, int end_point_x, int end_point_y, int width, QColor color)
{
	start_point_x_ = start_point_x;
	start_point_y_ = start_point_y;
	end_point_x_ = end_point_x;
	end_point_y_ = end_point_y;
	width_ = width;
	color_ = color;
}

Ellipse::~Ellipse()
{
}

void Ellipse::draw(QPainter &paint)
{
	paint.setPen(QPen(color_, width_));
	paint.drawEllipse(start_point_x_, start_point_y_, end_point_x_ - start_point_x_, end_point_y_ - start_point_y_);
}
