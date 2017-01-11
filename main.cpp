#include "mainwindow.h"
#include <QApplication>

#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle("Sudoku");
	QDesktopWidget* dw = a.desktop();

	qDebug()<< w.height();
	qDebug()<< dw->height();
	QRect newSize(0,0,w.height(), dw->height());
	w.setGeometry(newSize);
	w.show();

	return a.exec();
}
