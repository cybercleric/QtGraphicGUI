#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GraphicGUI.h"

class GraphicGUI : public QMainWindow
{
	Q_OBJECT

public:
	GraphicGUI(QWidget *parent = Q_NULLPTR);

private slots:
	void build();

private:
	Ui::GraphicGUIClass ui;
	QGraphicsScene * scene;

	void buildSin();
	void buildX2();
	void buildX();
	void buildX2rand();
};
