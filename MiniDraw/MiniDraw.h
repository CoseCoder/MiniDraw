#pragma once

#include <QtWidgets/QMainWindow>
#include <QDial>
#include <QEvent>
#include <QMenuBar>
#include <QToolBar>
#include "ui_MiniDraw.h"
#include "ViewWidget.h"

class MiniDraw : public QMainWindow
{
	Q_OBJECT

public:
	MiniDraw(QWidget *parent = Q_NULLPTR);

	//创建菜单栏及菜单
	void createQMenu();

	//创建工具栏及工具
	void createQToolBar();

	//创建状态栏
	void createQStatusBar();

	//创建各个QAction动作
	void createQActions();

	//设置QAction的触发条件及相应动作
	void connectQActions();

	//设置状态栏提示
	void setStatusTip();

	//设置显示实线宽度的标签的文本
	void changeWidthLabel(int);

private:
	Ui::MiniDrawClass ui;

	//画板
	ViewWidget *view_widget_;

	QMenu	   *main_menu_;
	QToolBar   *main_toolbar_;
	QStatusBar *main_status_;

	QAction	*p_line_action_;
	QAction	*p_ellipse_action_;
	QAction	*p_rectangle_action_;
	QAction	*p_polygon_action_;
	QAction	*p_freehand_action_;
	//撤销动作
	QAction	*p_undo_action_;
	//恢复撤销动作
	QAction	*p_do_action_;
	//清空动作
	QAction *p_clear_;
	//改变颜色动作
	QAction *p_change_color_;

	//显示当前线条宽度  
	QLabel *width_label_;
	//线条宽度标度盘
	QDial  *width_dial_;
};
