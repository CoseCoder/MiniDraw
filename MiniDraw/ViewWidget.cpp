#include "ViewWidget.h"
#include "Line.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Freehand.h"

//��ʼ��
ViewWidget::ViewWidget(QStatusBar *main_status, QWidget *parent)
	: QWidget(parent)
{
	draw_status_ = false;//��ǰ����״̬Ϊfalse
	figure_type_ = kDefault;//��ǰ���Ƶ�ͼ������ΪkDefault
	current_figure_ = NULL;//��ǰ����ͼ��ΪNULL

	ui.setupUi(this);

	//���õ�ǰ����ͼ�����͵���ʾ
	tip_ = new QLabel;
	main_status->addWidget(tip_);
	tip_->setMinimumSize(150, 20);
	tip_->setText("ready");//��ʼΪReady

	//��ʼ������
	pen_ = new QPen;
}

//���current_figure_��2��vector,�ͷ��ڴ�
ViewWidget::~ViewWidget()
{
	if (current_figure_)
	{
		delete current_figure_;
		current_figure_ = NULL;
	}
	figures_.swap(vector<Figure*>());
	figures_.clear();
	undo_figures_.swap(vector<Figure*>());
	undo_figures_.clear();
}

void ViewWidget::mousePressEvent(QMouseEvent * event)
{
	if (Qt::LeftButton == event->button())//������
	{
		start_point_ = end_point_ = event->pos();//����ͼ�ε������յ�

		//����ǰ����״̬λtrue(�����ڻ��ƶ����),���µĵ���ĵ����points_��
		//����,���ݵ�ǰ���Ƶ�ͼ������,current_figure_=��Ӧ���͵��½�����
		//�ر��,�����ǰ�½���ͼ���Ƕ���λ���������,��ֻ����ʼ�����points_��,ֱ��ͼ�λ�����ɲ��½���Ӧ���͵Ķ���
		if (draw_status_)
		{
			points_.append(QPointF(start_point_));
		}
		else
		{
			switch (figure_type_)
			{
			case kDefault:
				break;
			case kLine:
				current_figure_ = new Line(start_point_.rx(), start_point_.ry(), end_point_.rx(), end_point_.ry(), pen_->width(), pen_->color());
				break;
			case kEllipse:
				current_figure_ = new Ellipse(start_point_.rx(), start_point_.ry(), end_point_.rx(), end_point_.ry(), pen_->width(), pen_->color());
				break;
			case kRectangle:
				current_figure_ = new Rectangle(start_point_.rx(), start_point_.ry(), end_point_.rx(), end_point_.ry(), pen_->width(), pen_->color());
				break;
			case kPolygon:
			case kFreehand:
				points_.append(start_point_);
				break;
			default:
				break;
			}
			if (kDefault != figure_type_)
				draw_status_ = true;
		}
	}
	else if (Qt::RightButton == event->button())//����һ�
	{
		endPolygonDrawing();//��ɶ���λ���
	}
}

void ViewWidget::mouseMoveEvent(QMouseEvent * event)
{
	//����ǰ����״̬Ϊtrue,�һ��Ƶ�ͼ������Ϊ��������,����굱ǰ���ڵĵ����points_
	//��������ǰ����ͼ�����Ͳ��Ƕ����,��ͼ�ε��յ����ó���굱ǰ���ڵĵ�
	if (draw_status_)
	{
		end_point_ = event->pos();
		if (kFreehand == figure_type_)
		{
			points_.append(end_point_);
			return;
		}
		else if (kPolygon == figure_type_)
			return;
		current_figure_->setEnd(end_point_.rx(), end_point_.ry());
	}
}

void ViewWidget::mouseReleaseEvent(QMouseEvent * event)
{
	//����ǰ����״̬Ϊtrue,�һ���ͼ�������ǲ��Ƕ���κ���������,�򽫵�ǰͼ�μ��뵽�Ѿ����ƺõ�ͼ��vector��,���õ�ǰ����״̬Ϊfalse,��ǰͼ��ΪNULL
	//�����Ƶ�ͼ������Ϊ��������,���Ƚ���ǰͼ�����ó��������ߵ��¶���,���points_,Ȼ��ִ�������ᵽ�����в���
	if (draw_status_)
	{
		if (kPolygon == figure_type_)
			return;
		if (kFreehand == figure_type_)
		{
			current_figure_ = new Freehand(points_, pen_->width(), pen_->color());
			points_.clear();
		}
		figures_.push_back(current_figure_);
		draw_status_ = false;
		current_figure_ = NULL;
	}
}

void ViewWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);

	painter.begin(this);//���ƿ�ʼ

	//��������ʽ�޸ĳɵ�ǰ������
	painter.setPen(*pen_);

	//����ǰ����״̬Ϊtrue,��points_�ǿ�(�����ڻ��Ƶ�ͼ��Ϊ����λ���������),�����points_��ɵ�����
	//����,���õ�ǰͼ�ε��������Ӧ��draw����
	if (draw_status_) {
		if (points_.empty())
			current_figure_->draw(painter);
		else
			painter.drawPolyline(points_);
	}

	painter.setRenderHint(QPainter::Antialiasing, true);//���û���ͼ�εķ�����

	//��figures_�����е�ͼ��ȫ�����Ƴ���
	for (size_t i = 0; i < figures_.size(); i++)
	{
		figures_[i]->draw(painter);
	}

	painter.end();//���ƽ���

	update();//���»���
}

//��������λ���
void ViewWidget::endPolygonDrawing()
{
	//����ǰ����״̬Ϊtrue,�һ��Ƶ�ͼ������Ϊ�����,����ǰͼ����ɶ���ε��¶���,�����뵽�Ѿ����ƺõ�ͼ��vector��,���õ�ǰ����״̬Ϊfalse,��ǰͼ��ΪNULL
	if (draw_status_&&kPolygon == figure_type_)
	{
		figures_.push_back(new Polygon(points_, pen_->width(), pen_->color()));
		draw_status_ = false;
		current_figure_ = NULL;
		points_.clear();
	}
}

void ViewWidget::setFigureTypeToLine()
{
	endPolygonDrawing();
	figure_type_ = kLine;
	tip_->setText("Line");
}

void ViewWidget::setFigureTypeToEllipse()
{
	endPolygonDrawing();
	figure_type_ = kEllipse;
	tip_->setText("Ellipse");
}

void ViewWidget::setFigureTypeToRectangle()
{
	endPolygonDrawing();
	figure_type_ = kRectangle;
	tip_->setText("Rectangle");
}

void ViewWidget::setFigureTypeToPolygon()
{
	endPolygonDrawing();
	figure_type_ = kPolygon;
	tip_->setText("Polygon");
}

void ViewWidget::setFigureTypeToFreehand()
{
	endPolygonDrawing();
	figure_type_ = kFreehand;
	tip_->setText("Freehand");
}

void ViewWidget::set_Width(int w)
{
	endPolygonDrawing();
	pen_->setWidth(w);
}

void ViewWidget::undoFigures()
{
	endPolygonDrawing();
	//���ѻ��ƺõ�ͼ�μ��Ϸǿ�,�������Ƶ�ͼ���Ƴ�����,���뱻������ͼ�μ���
	if (!figures_.empty())
	{
		undo_figures_.push_back(figures_[figures_.size() - 1]);
		figures_.pop_back();
	}
}

void ViewWidget::doFigures()
{
	endPolygonDrawing();
	//���������ĵ�ͼ�μ��Ϸǿ�,����󱻳�����ͼ���Ƴ�����,�����ѻ��ƺõ�ͼ�μ���
	if (!undo_figures_.empty())
	{
		figures_.push_back(undo_figures_[undo_figures_.size() - 1]);
		undo_figures_.pop_back();
	}
}

//��ջ���,����ѻ��ƺõ�ͼ�μ��Ϻͱ�������ͼ�μ���,�ͷ���Ӧ���ڴ�
void ViewWidget::clear()
{
	endPolygonDrawing();
	figures_.swap(vector<Figure*>());
	figures_.clear();
	undo_figures_.swap(vector<Figure*>());
	undo_figures_.clear();
}

//������ɫ��,�����ʵ���ɫ���ó���Ҫ����ɫ
void ViewWidget::changeColor()
{
	endPolygonDrawing();
	QColor c = QColorDialog::getColor();
	pen_->setColor(c);
}
