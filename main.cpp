#include "GraphicGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GraphicGUI w;
	w.setFixedSize(600, 600);
	w.show();
	return a.exec();
}
