#include "Polygon.h"

Polygon::Polygon(QVector<QPointF> points, int width, QColor color)
{
	points_ = QVector<QPointF>(points);
	width_ = width;
	color_ = color;
}

Polygon::~Polygon()
{
}

void Polygon::draw(QPainter &paint)
{
	paint.setPen(QPen(color_, width_));
	paint.drawPolygon(points_);
}
