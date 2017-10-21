#include "Freehand.h"

Freehand::Freehand(QVector<QPointF> points, int width, QColor color)
{
	points_ = QVector<QPointF>(points);
	width_ = width;
	color_ = color;
}

Freehand::~Freehand()
{
}

void Freehand::draw(QPainter &paint)
{
	paint.setPen(QPen(color_, width_));
	paint.drawPolyline(points_);
}
