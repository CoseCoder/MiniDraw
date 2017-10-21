#include "ViewWidget.h"
#include "Line.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Freehand.h"

//初始化
ViewWidget::ViewWidget(QStatusBar *main_status, QWidget *parent)
	: QWidget(parent)
{
	draw_status_ = false;//当前绘制状态为false
	figure_type_ = kDefault;//当前绘制的图形类型为kDefault
	current_figure_ = NULL;//当前绘制图形为NULL

	ui.setupUi(this);

	//设置当前绘制图形类型的提示
	tip_ = new QLabel;
	main_status->addWidget(tip_);
	tip_->setMinimumSize(150, 20);
	tip_->setText("ready");//初始为Ready

	//初始化画笔
	pen_ = new QPen;
}

//清空current_figure_和2个vector,释放内存
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
	if (Qt::LeftButton == event->button())//鼠标左击
	{
		start_point_ = end_point_ = event->pos();//设置图形的起点和终点

		//若当前绘制状态位true(即正在绘制多边形),则将新的点击的点加入points_中
		//否则,根据当前绘制的图形类型,current_figure_=相应类型的新建对象
		//特别地,如果当前新建的图形是多边形或自由曲线,则只将起始点加入points_中,直到图形绘制完成才新建相应类型的对象
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
	else if (Qt::RightButton == event->button())//鼠标右击
	{
		endPolygonDrawing();//完成多边形绘制
	}
}

void ViewWidget::mouseMoveEvent(QMouseEvent * event)
{
	//若当前绘制状态为true,且绘制的图形类型为自由曲线,则将鼠标当前所在的点加入points_
	//此外若当前绘制图形类型不是多边形,将图形的终点设置成鼠标当前所在的点
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
	//若当前绘制状态为true,且绘制图形类型是不是多边形和自由曲线,则将当前图形加入到已经绘制好的图形vector中,设置当前绘制状态为false,当前图形为NULL
	//若绘制的图形类型为自由曲线,则先将当前图形设置成自由曲线的新对象,清空points_,然后执行上述提到的所有操作
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

	painter.begin(this);//绘制开始

	//将画笔样式修改成当前的设置
	painter.setPen(*pen_);

	//若当前绘制状态为true,且points_非空(即正在绘制的图形为多边形或自由曲线),则绘制points_组成的折线
	//否则,调用当前图形的类型相对应的draw函数
	if (draw_status_) {
		if (points_.empty())
			current_figure_->draw(painter);
		else
			painter.drawPolyline(points_);
	}

	painter.setRenderHint(QPainter::Antialiasing, true);//设置绘制图形的反走样

	//将figures_集合中的图形全部绘制出来
	for (size_t i = 0; i < figures_.size(); i++)
	{
		figures_[i]->draw(painter);
	}

	painter.end();//绘制结束

	update();//更新画布
}

//结束多边形绘制
void ViewWidget::endPolygonDrawing()
{
	//若当前绘制状态为true,且绘制的图形类型为多边形,将当前图形设成多边形的新对象,并加入到已经绘制好的图形vector中,设置当前绘制状态为false,当前图形为NULL
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
	//若已绘制好的图形集合非空,则将最后绘制的图形移出集合,移入被撤销的图形集合
	if (!figures_.empty())
	{
		undo_figures_.push_back(figures_[figures_.size() - 1]);
		figures_.pop_back();
	}
}

void ViewWidget::doFigures()
{
	endPolygonDrawing();
	//若被撤销的的图形集合非空,则将最后被撤销的图形移出集合,移入已绘制好的图形集合
	if (!undo_figures_.empty())
	{
		figures_.push_back(undo_figures_[undo_figures_.size() - 1]);
		undo_figures_.pop_back();
	}
}

//清空画布,清除已绘制好的图形集合和被撤销的图形集合,释放相应的内存
void ViewWidget::clear()
{
	endPolygonDrawing();
	figures_.swap(vector<Figure*>());
	figures_.clear();
	undo_figures_.swap(vector<Figure*>());
	undo_figures_.clear();
}

//调出调色板,将画笔的颜色设置成需要的颜色
void ViewWidget::changeColor()
{
	endPolygonDrawing();
	QColor c = QColorDialog::getColor();
	pen_->setColor(c);
}
