#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QStatusBar>
#include <QLabel>
#include <QColorDialog>
#include "ui_ViewWidget.h"
#include "Figure.h"
#include "FigureType.h"
#include <vector>
using namespace std;


class ViewWidget : public QWidget
{
	Q_OBJECT

public:
	ViewWidget(QStatusBar *main_status, QWidget *parent = Q_NULLPTR);
	~ViewWidget();

	//��������Ӧ���������Ҽ���
	void mousePressEvent(QMouseEvent *event);

	//����ƶ���Ӧ����
	void mouseMoveEvent(QMouseEvent *event);

	//����ͷ���Ӧ����
	void mouseReleaseEvent(QMouseEvent *event);

	//������Ϣ��Ӧ����
	void paintEvent(QPaintEvent *);

	//��ɶ���εĻ��ƣ�ʹ����αպ�
	void endPolygonDrawing();

	//���õ�ǰ����ͼ������
	void setFigureTypeToLine();
	void setFigureTypeToEllipse();
	void setFigureTypeToRectangle();
	void setFigureTypeToPolygon();
	void setFigureTypeToFreehand();

	//������һ������
	void undoFigures();
	//�ָ���һ�������Ĳ���
	void doFigures();

	//��ջ���
	void clear();

	//����ʵ�߿��
	void set_Width(int w);
	//����ʵ����ɫ
	void changeColor();

private:
	Ui::ViewWidget ui;

	//����(�����߿�,��ɫ������)
	QPen *pen_;

	//λ��״̬���У���ʾ��ǰ���Ƶ�ͼ������
	QLabel *tip_;

	//��ǰ�Ļ滭״̬
	bool draw_status_;

	//ͼ�����
	QPoint start_point_;

	//ͼ�ε��յ�
	QPoint end_point_;

	//����εĸ���������������߾����ĵ�
	QVector<QPointF> points_;

	//�Ѿ����ƺõ�ͼ��
	vector<Figure*> figures_;

	//��������ͼ��
	vector<Figure*> undo_figures_;

	//��ǰ���Ƶ�ͼ������
	FigureType  figure_type_;

	//��ǰ���Ƶ�ͼ��
	Figure *current_figure_;

};
