#pragma once
#include "Figure.h"
class Freehand :public Figure
{
public:
	Freehand(QVector<QPointF> points, int width, QColor color);

	~Freehand();

	void draw(QPainter &paint);

private:
	QVector<QPointF> points_;
};