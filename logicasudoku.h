#ifndef LOGICASUDOKU_H
#define LOGICASUDOKU_H

#include <QStandardItemModel>
#include <QTime>
#include <QDebug>

class LogicaSudoku: public QStandardItemModel
{
	QStandardItemModel *gameModel;
	QStandardItemModel *pazleModel;
	const int capasity;
	const int capasity_mix;

	int num1, num2, num3, num4;
	bool st_num;

	void showTableGameModel();
	void showTablePazleModel();
	bool checkRectThree(int col,  int row, int n);
	void mix_value();
	void createUserPuzzle();
public:
	LogicaSudoku(QObject *obj);
	~LogicaSudoku();
	QStandardItemModel *createPuzzle();
	bool checkErrPuzzle();
	void setModel(QStandardItemModel *gameModel_);
};

#endif // LOGICASUDOKU_H
