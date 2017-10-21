#pragma once
#include <QPainter>
#include <iostream>
using namespace std;
class Figure
{
public:
	Figure();

	virtual ~Figure();

	virtual void draw(QPainter &paint);

	//设置终点位置
	void setEnd(int end_point_x, int end_point_y);


protected:
	//起点和终点的x,y坐标
	int	start_point_x_, start_point_y_, end_point_x_, end_point_y_;

	//绘制图形的线的宽度
	int width_;

	//绘制图形的线的颜色
	QColor color_;
};