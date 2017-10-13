#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MiniDraw.h"

class MiniDraw : public QMainWindow
{
	Q_OBJECT

public:
	MiniDraw(QWidget *parent = Q_NULLPTR);

private:
	Ui::MiniDrawClass ui;
};
