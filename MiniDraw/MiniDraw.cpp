#include "MiniDraw.h"

MiniDraw::MiniDraw(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	width_dial_ = new QDial(this);//��ʼ�������
	width_dial_->setRange(1, 20);//����������ȷ�Χ
	width_dial_->setNotchesVisible(true);//���ñ���̶̿ȿɼ�
	width_label_ = new QLabel("Size: 1", this);//������ʾ������ȵ�QLabel���ı�

	createQStatusBar();//����״̬��

	//���û���
	view_widget_ = new ViewWidget(main_status_);
	setCentralWidget(view_widget_);

	createQActions();//����QAction����
	createQMenu();//�����˵������˵�
	createQToolBar();//����������������	

	setStatusTip();//����״̬����ʾ
	connectQActions();//���ø��������Ĵ����źź���Ӧ����
}

void MiniDraw::createQMenu()
{
	main_menu_ = menuBar()->addMenu(tr("&Main"));
	main_menu_->addAction(p_line_action_);
	main_menu_->addAction(p_ellipse_action_);
	main_menu_->addAction(p_rectangle_action_);
	main_menu_->addAction(p_polygon_action_);
	main_menu_->addAction(p_freehand_action_);
	main_menu_->addAction(p_undo_action_);
	main_menu_->addAction(p_do_action_);
	main_menu_->addAction(p_change_color_);
	main_menu_->addAction(p_clear_);
}

void MiniDraw::createQToolBar()
{
	main_toolbar_ = addToolBar(tr("&Main"));
	main_toolbar_->addAction(p_line_action_);
	main_toolbar_->addAction(p_ellipse_action_);
	main_toolbar_->addAction(p_rectangle_action_);
	main_toolbar_->addAction(p_polygon_action_);
	main_toolbar_->addAction(p_freehand_action_);
	main_toolbar_->addAction(p_undo_action_);
	main_toolbar_->addAction(p_do_action_);
	main_toolbar_->addAction(p_change_color_);
	main_toolbar_->addAction(p_clear_);

	main_toolbar_->addWidget(width_dial_);
	main_toolbar_->addWidget(width_label_);
}

void MiniDraw::createQStatusBar()
{
	main_status_ = statusBar();
}

void MiniDraw::createQActions()
{
	p_line_action_ = new QAction(tr("&Line"), this);
	p_ellipse_action_ = new QAction(tr("&Ellipse"), this);
	p_rectangle_action_ = new QAction(tr("&Rectangle"), this);
	p_polygon_action_ = new QAction(tr("&Polygon"), this);
	p_freehand_action_ = new QAction(tr("&Freehand"), this);
	p_undo_action_ = new QAction(tr("&Undo"), this);
	p_undo_action_->setShortcut(tr("ctrl+Z"));
	p_do_action_ = new QAction(tr("&Do"), this);
	p_clear_ = new QAction(tr("&Clear"), this);
	p_change_color_ = new QAction(tr("&Color"), this);
}

void MiniDraw::connectQActions()
{
	connect(p_line_action_, &QAction::triggered, view_widget_, &ViewWidget::setFigureTypeToLine);
	connect(p_ellipse_action_, &QAction::triggered, view_widget_, &ViewWidget::setFigureTypeToEllipse);
	connect(p_rectangle_action_, &QAction::triggered, view_widget_, &ViewWidget::setFigureTypeToRectangle);
	connect(p_polygon_action_, &QAction::triggered, view_widget_, &ViewWidget::setFigureTypeToPolygon);
	connect(p_freehand_action_, &QAction::triggered, view_widget_, &ViewWidget::setFigureTypeToFreehand);
	connect(p_undo_action_, &QAction::triggered, view_widget_, &ViewWidget::undoFigures);
	connect(p_do_action_, &QAction::triggered, view_widget_, &ViewWidget::doFigures);
	connect(p_change_color_, &QAction::triggered, view_widget_, &ViewWidget::changeColor);
	connect(p_clear_, &QAction::triggered, view_widget_, &ViewWidget::clear);

	connect(width_dial_, &QDial::valueChanged, this, &MiniDraw::changeWidthLabel);
	connect(width_dial_, &QDial::valueChanged, view_widget_, &ViewWidget::set_Width);

}

void MiniDraw::setStatusTip()
{
	p_line_action_->setStatusTip(tr("Line"));
	p_ellipse_action_->setStatusTip(tr("Ellipse"));
	p_rectangle_action_->setStatusTip(tr("Rectangle"));
	p_polygon_action_->setStatusTip(tr("Polygon"));
	p_freehand_action_->setStatusTip(tr("Freehand"));
	p_undo_action_->setStatusTip(tr("Undo Ctrl+Z"));
	p_do_action_->setStatusTip(tr("Do"));
	p_change_color_->setStatusTip(tr("Change Color"));
	p_clear_->setStatusTip(tr("Clear"));

	width_label_->setStatusTip(tr("Line Width"));
	width_dial_->setStatusTip(tr("Change Line Width"));
}

//��ʾ��ǰ�����������
void MiniDraw::changeWidthLabel(int w)
{
	width_label_->setText("Size: " + QString::number(width_dial_->value()));
}

