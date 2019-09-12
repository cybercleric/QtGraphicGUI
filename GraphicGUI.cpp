#include "GraphicGUI.h"
#include <QGraphicsScene>

#define WH_SIZE 400
#define STEP	35

GraphicGUI::GraphicGUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.comboBox->addItem("y = sin(x)");
	ui.comboBox->addItem("y = x ^ 2");
	ui.comboBox->addItem("y = x");
	ui.comboBox->addItem("y = x ^ 2 + random()");

	ui.limitLeft->setValidator(new QIntValidator(-99, 99, this));
	ui.limitRight->setValidator(new QIntValidator(-99, 99, this));
	ui.limitDown->setValidator(new QIntValidator(-99, 99, this));
	ui.limitUp->setValidator(new QIntValidator(-99, 99, this));

	connect(ui.pushButton, &QPushButton::clicked, this, &GraphicGUI::build);
}

void GraphicGUI::build() {
	if (ui.limitLeft->text().toInt() >= ui.limitRight->text().toInt()) {
		scene = new QGraphicsScene(ui.graphicsView);
		scene->addText("Invalid left and right limit.");
		ui.graphicsView->setScene(scene);
		return;
	}

	if (ui.limitDown->text().toInt() >= ui.limitUp->text().toInt()) {
		scene = new QGraphicsScene(ui.graphicsView);
		scene->addText("Invalid down and up limit.");
		ui.graphicsView->setScene(scene);
		return;
	}

	double stepHorizontal = WH_SIZE / (ui.limitRight->text().toInt() - ui.limitLeft->text().toInt());
	double stepVertical = WH_SIZE / (ui.limitUp->text().toInt() - ui.limitDown->text().toInt());

	scene = new QGraphicsScene(ui.graphicsView);
	QLine line;
	QGraphicsTextItem * text;
	QPainterPath path;

	//Оси
	line = QLine(0, WH_SIZE / 2, WH_SIZE, WH_SIZE / 2);
	scene->addLine(line);
	line = QLine(WH_SIZE / 2, 0, WH_SIZE / 2, WH_SIZE);
	scene->addLine(line);

	
	//Разметка из центра вправо
	double counter = (ui.limitRight->text().toInt() + ui.limitLeft->text().toInt()) / 2.0 - STEP / stepHorizontal;
	for(int i = WH_SIZE / 2 - STEP; i > 0; i -= STEP) {
		line = QLine(i, WH_SIZE / 2 + 5, i, WH_SIZE / 2 - 5);
		scene->addLine(line);

		path.addText(i - 10, WH_SIZE / 2 + 20, QFont("Avqest", 7, 7), QString::number(counter, 'f', 2));
		scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

		counter -= STEP / stepHorizontal;
	}
	line = QLine(0, WH_SIZE / 2 + 5, 0, WH_SIZE / 2 - 5);
	scene->addLine(line);
	path.addText(0, WH_SIZE / 2 - 12, QFont("Avqest", 7, 7), ui.limitLeft->text());
	scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

	//Разметка из центра влево
	counter = (ui.limitRight->text().toInt() + ui.limitLeft->text().toInt()) / 2.0 + STEP / stepHorizontal;
	for(int i = WH_SIZE / 2 + STEP; i < WH_SIZE; i += STEP) {
		line = QLine(i, WH_SIZE / 2 + 5, i, WH_SIZE / 2 - 5);
		scene->addLine(line);

		path.addText(i - 10, WH_SIZE / 2 + 20, QFont("Avqest", 7, 7), QString::number(counter, 'f', 2));
		scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

		counter += STEP / stepHorizontal;
	}
	line = QLine(WH_SIZE, WH_SIZE / 2 + 5, WH_SIZE, WH_SIZE / 2 - 5);
	scene->addLine(line);
	path = QPainterPath();
	path.addText(WH_SIZE, WH_SIZE / 2 - 12, QFont("Avqest", 7, 7), ui.limitRight->text());
	scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

	//Разметка из центра вверх
	counter = (ui.limitUp->text().toInt() + ui.limitDown->text().toInt()) / 2.0 + STEP / stepVertical;
	for(int i = WH_SIZE / 2 - STEP; i > 0; i -= STEP) {
		line = QLine(WH_SIZE / 2 -5, i, WH_SIZE / 2 + 5, i);
		scene->addLine(line);

		path.addText(WH_SIZE / 2 + 10, i + 3, QFont("Avqest", 7, 7), QString::number(counter, 'f', 2));
		scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

		counter += STEP / stepVertical;
	}
	line = QLine(WH_SIZE / 2 - 5, 0, WH_SIZE / 2 + 5, 0);
	scene->addLine(line);
	path.addText(WH_SIZE / 2 + 10, 3, QFont("Avqest", 7, 7), ui.limitUp->text());
	scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

	//Разметка из центра вниз
	counter = (ui.limitUp->text().toInt() + ui.limitDown->text().toInt()) / 2.0 - STEP / stepVertical;
	for(int i = WH_SIZE / 2 + STEP; i < WH_SIZE; i += STEP) {
		line = QLine(WH_SIZE / 2 - 5, i, WH_SIZE / 2 + 5, i);
		scene->addLine(line);

		path.addText(WH_SIZE / 2 + 10, i + 3, QFont("Avqest", 7, 7), QString::number(counter, 'f', 2));
		scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

		counter -= STEP / stepVertical;
	}
	line = QLine(WH_SIZE / 2 - 5, WH_SIZE, WH_SIZE / 2 + 5, WH_SIZE);
	scene->addLine(line);
	path.addText(WH_SIZE / 2 + 10, WH_SIZE + 3, QFont("Avqest", 7, 7), ui.limitDown->text());
	scene->addPath(path, QPen(QBrush(Qt::black), 1), QBrush(Qt::black));

	ui.graphicsView->setScene(scene);

	switch (ui.comboBox->currentIndex())
	{
	case 0:
		buildSin();
		break;
	case 1:
		buildX2();
		break;
	case 2:
		buildX();
		break;
	case 3:
		buildX2rand();
		break;
	}
}

void GraphicGUI::buildSin() {
	double stepHorizontal = WH_SIZE / (ui.limitRight->text().toInt() - ui.limitLeft->text().toInt());
	double stepVertical = WH_SIZE / (ui.limitUp->text().toInt() - ui.limitDown->text().toInt());

	float step = 1 / stepHorizontal;
	float countX = ui.limitLeft->text().toInt();
	float countY = 0;
	int y;
	for (int x = 0; x <= WH_SIZE; x += 1) {
		countY = sin(countX);
		scene->addRect(x,  WH_SIZE / 2 + countY * stepVertical * -1, 1, 1, QPen(QColor(Qt::GlobalColor::blue)));
		countX += step;
	}

	ui.graphicsView->setScene(scene);
}

void GraphicGUI::buildX2() {
	double stepHorizontal = WH_SIZE / (ui.limitRight->text().toInt() - ui.limitLeft->text().toInt());
	double stepVertical = WH_SIZE / (ui.limitUp->text().toInt() - ui.limitDown->text().toInt());

	float step = 1 / stepHorizontal;
	float countX = ui.limitLeft->text().toInt();
	float countY = 0;
	int y;
	for (int x = 0; x <= WH_SIZE; x += 1) {
		countY = countX * countX;
		scene->addRect(x,  WH_SIZE / 2 + countY * stepVertical * -1, 1, 1, QPen(QColor(Qt::GlobalColor::blue)));
		countX += step;
	}

	ui.graphicsView->setScene(scene);
}

void GraphicGUI::buildX() {
	double stepHorizontal = WH_SIZE / (ui.limitRight->text().toInt() - ui.limitLeft->text().toInt());
	double stepVertical = WH_SIZE / (ui.limitUp->text().toInt() - ui.limitDown->text().toInt());

	float step = 1 / stepHorizontal;
	float countX = ui.limitLeft->text().toInt();
	float countY = 0;
	int y;
	for (int x = 0; x <= WH_SIZE; x += 1) {
		countY = countX;
		scene->addRect(x,  WH_SIZE / 2 + countY * stepVertical * -1, 1, 1, QPen(QColor(Qt::GlobalColor::blue)));
		countX += step;
	}

	ui.graphicsView->setScene(scene);
}

void GraphicGUI::buildX2rand() {
	double stepHorizontal = WH_SIZE / (ui.limitRight->text().toInt() - ui.limitLeft->text().toInt());
	double stepVertical = WH_SIZE / (ui.limitUp->text().toInt() - ui.limitDown->text().toInt());

	float step = 1 / stepHorizontal;
	float countX = ui.limitLeft->text().toInt();
	float countY = 0;
	int y;
	for (int x = 0; x <= WH_SIZE; x += 1) {
		countY = countX * countX + rand() % 5;
		scene->addRect(x,  WH_SIZE / 2 + countY * stepVertical * -1, 1, 1, QPen(QColor(rand())));
		countX += step;
	}

	ui.graphicsView->setScene(scene);
}