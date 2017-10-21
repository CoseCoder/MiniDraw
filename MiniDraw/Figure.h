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

	//�����յ�λ��
	void setEnd(int end_point_x, int end_point_y);


protected:
	//�����յ��x,y����
	int	start_point_x_, start_point_y_, end_point_x_, end_point_y_;

	//����ͼ�ε��ߵĿ��
	int width_;

	//����ͼ�ε��ߵ���ɫ
	QColor color_;
};