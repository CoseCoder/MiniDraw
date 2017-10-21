#pragma once
#include "Figure.h"
class Polygon :public Figure
{
public:
	Polygon(QVector<QPointF> points, int width, QColor color);

	~Polygon();

	void draw(QPainter &paint);

private:
	QVector<QPointF> points_;
};