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

	//鼠标击发响应函数（左右键）
	void mousePressEvent(QMouseEvent *event);

	//鼠标移动响应函数
	void mouseMoveEvent(QMouseEvent *event);

	//鼠标释放响应函数
	void mouseReleaseEvent(QMouseEvent *event);

	//绘制消息响应函数
	void paintEvent(QPaintEvent *);

	//完成多边形的绘制，使多边形闭合
	void endPolygonDrawing();

	//设置当前绘制图形类型
	void setFigureTypeToLine();
	void setFigureTypeToEllipse();
	void setFigureTypeToRectangle();
	void setFigureTypeToPolygon();
	void setFigureTypeToFreehand();

	//撤销上一步操作
	void undoFigures();
	//恢复上一步撤销的操作
	void doFigures();

	//清空画布
	void clear();

	//设置实线宽度
	void set_Width(int w);
	//设置实线颜色
	void changeColor();

private:
	Ui::ViewWidget ui;

	//画笔(包括线宽,颜色等属性)
	QPen *pen_;

	//位于状态栏中，显示当前绘制的图形类型
	QLabel *tip_;

	//当前的绘画状态
	bool draw_status_;

	//图形起点
	QPoint start_point_;

	//图形的终点
	QPoint end_point_;

	//多边形的各个顶点或自由曲线经过的点
	QVector<QPointF> points_;

	//已经绘制好的图形
	vector<Figure*> figures_;

	//被撤销的图形
	vector<Figure*> undo_figures_;

	//当前绘制的图形类型
	FigureType  figure_type_;

	//当前绘制的图形
	Figure *current_figure_;

};
