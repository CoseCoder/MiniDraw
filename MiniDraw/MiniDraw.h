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

	//�����˵������˵�
	void createQMenu();

	//����������������
	void createQToolBar();

	//����״̬��
	void createQStatusBar();

	//��������QAction����
	void createQActions();

	//����QAction�Ĵ�����������Ӧ����
	void connectQActions();

	//����״̬����ʾ
	void setStatusTip();

	//������ʾʵ�߿�ȵı�ǩ���ı�
	void changeWidthLabel(int);

private:
	Ui::MiniDrawClass ui;

	//����
	ViewWidget *view_widget_;

	QMenu	   *main_menu_;
	QToolBar   *main_toolbar_;
	QStatusBar *main_status_;

	QAction	*p_line_action_;
	QAction	*p_ellipse_action_;
	QAction	*p_rectangle_action_;
	QAction	*p_polygon_action_;
	QAction	*p_freehand_action_;
	//��������
	QAction	*p_undo_action_;
	//�ָ���������
	QAction	*p_do_action_;
	//��ն���
	QAction *p_clear_;
	//�ı���ɫ����
	QAction *p_change_color_;

	//��ʾ��ǰ�������  
	QLabel *width_label_;
	//������ȱ����
	QDial  *width_dial_;
};
