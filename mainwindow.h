#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QKeyEvent>
#include <QMenu>
#include <QLCDNumber>
#include <QLabel>

#include "playwidget.h"
#include "logicasudoku.h"
#include "camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	QStandardItemModel *pazle;
	PlayWidget* playFeeld;
	QLCDNumber* lcd;
	QPushButton** btn;
	LogicaSudoku* logSud;
	QVBoxLayout* vl;
	QCheckBox* hint;
	QMenu* contextMenu;
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void enabledAllButtons();
private:
	Ui::MainWindow *ui;
	void newGame();
	void removeGame();

private slots:
	void clickButton0();
	void clickButton1();
	void clickButton2();
	void clickButton3();
	void clickButton4();
	void clickButton5();
	void clickButton6();
	void clickButton7();
	void clickButton8();
	void clickButton9();
	void resetGame();
	void restartGame();

	void changeFlagHint(bool hint_);
};


#endif // MAINWINDOW_H
