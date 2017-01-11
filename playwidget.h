#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QLCDNumber>
#include <QMessageBox>
#include <QDebug>

#include "logicasudoku.h"

class PlayWidget: public QWidget
{
	float step_line;
	QStandardItemModel *showPazle;
	QStandardItemModel *setUserData;
	int click_row;
	int click_col;
	float width;
	float heigth;
	int userNumber;
	QPushButton **btn;
	QLCDNumber* lcd;
	bool hint;
	bool* buttonHint;
	int stepFinish;
	bool createNewGame;
private:
	void showFinish();

protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void paintEvent(QPaintEvent *);
	void enableDisableButton(bool act);

public:
	void setHint(bool hint_);
	virtual void keyPressEvent(QKeyEvent *event);
	PlayWidget(QStandardItemModel* showPazle_, QPushButton **btn_, QLCDNumber* lcd_, QWidget *obj);
	~PlayWidget();
	void resetData();
	bool getStatusNewGame();
};

#endif // PLAYWIDGET_H
