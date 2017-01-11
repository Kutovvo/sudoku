#include "logicasudoku.h"


LogicaSudoku::LogicaSudoku(QObject *obj = 0):
	QStandardItemModel(obj), capasity(9), capasity_mix(1000), num1(0), num2(0),  num3(0), num4(0), st_num(false)
{
	gameModel = new QStandardItemModel(capasity,capasity,this);
	pazleModel = new QStandardItemModel(capasity,capasity,this);
}

LogicaSudoku::~LogicaSudoku()
{
	delete gameModel;
//	delete pazleModel;
}

QStandardItemModel* LogicaSudoku::createPuzzle()
{
	QTime midnight(0,0,0);
	qsrand(midnight.secsTo(QTime::currentTime()));

	QList <int> stList;
	int step = qrand() % capasity;
	if(step == 0 || step == 3 || step == 6)
		stList <<1<<4<<7<<2<<5<<8<<3<<6<<9;
	else if(step == 1 || step == 4 || step == 7)
		stList <<3<<4<<7<<1<<5<<8<<2<<6<<9;
	else
		stList <<3<<6<<7<<1<<4<<8<<2<<5<<9;
	for(uint j = 0; j<3; j++)
		for(uint i = 0; i<3; i++){
			int numb = stList.at(step++);
			for(uint col = j*3; col < j*3+3; col++)
				for(uint row = i*3; row < i*3+3; row++){
					if(numb>9)numb-=9;
					gameModel->setData( gameModel->index(col, row), numb++);
				}
			if(step > 8)
				step = 0;
		}
	if(checkErrPuzzle())
		for(int i = 0; i <= capasity_mix; i++)
			mix_value();
	if(checkErrPuzzle())
		pazleModel = gameModel;
//	showTableGameModel();
//	int level  = 54;//hard
	int level  = 33;//midle
	for(int i =0; i < level; i++)
		createUserPuzzle();
//	showTablePazleModel();
	return pazleModel;
}

bool LogicaSudoku::checkErrPuzzle()
{
	for(uint check_row = 0; check_row<9; check_row++)
		for(int check_val = 1; check_val < 10; check_val ++){
			bool find_check_val = false;
			for(uint col = 0; col<9; col++){
				if(gameModel->data(gameModel->index(col, check_row)).toInt() == check_val){
					find_check_val = true;
					col = 10;
				}
			}
			if(!find_check_val) return false;
		}
	for(uint check_col = 0; check_col<9; check_col++)
		for(int check_val = 1; check_val < 10; check_val ++){
			bool find_check_val = false;
			for(uint row = 0; row<9; row++){
				if(gameModel->data(gameModel->index(check_col, row)).toInt() == check_val){
					find_check_val = true;
					row = 10;
				}
			}
			if(!find_check_val) return false;
		}
	for(uint i = 0; i < 9; i++){
		uint col, row;
		switch (i) {
		case 0:
			col = 0;
			row = 0;
			break;
		case 1:
			col = 3;
			row = 0;
			break;
		case 2:
			col = 6;
			row = 0;
			break;
		case 3:
			row = 3;
			col = 0;
			break;
		case 4:
			row = 3;
			col = 3;
			break;
		case 5:
			row = 3;
			col = 6;
			break;
		case 6:
			row = 6;
			col = 0;
			break;
		case 7:
			row = 6;
			col = 3;
			break;
		default:
			row = 6;
			col = 6;
			break;
		}
		int sum = 0;
		for(uint col_ = col; col_ < col+3; col_++){
			for(uint row_ = row; row_ < row+3; row_++){
				sum += gameModel->data(gameModel->index(col_, row_)).toInt();
			}
		}
		if(sum != 45)
			return false;
	}
	return true;
}

void LogicaSudoku::setModel(QStandardItemModel *gameModel_)
{
	gameModel = gameModel_;
}


void LogicaSudoku::showTableGameModel()
{
	QString tab = " |   ";
	qDebug() << " \n\n                                      GameModel                                \n\n";
	for(int k = 0; k < capasity; k++)
		tab = tab + " " + QString::number(k+1);
	qDebug() << tab;
	qDebug() <<  "------------------------------------------------";
	tab = "";
	for(int k = 0; k < capasity; k++){
		for(int k1 = 0; k1 < capasity; k1++){
			int val = gameModel->data(gameModel->index(k, k1, QModelIndex()), Qt::DisplayRole).toInt();
			if(val == 0)
				tab = tab + "   ";
			else
				tab = tab + " " + QString("%1").arg(val);
		}
		qDebug() << k+1<<"|"<<tab;
		tab = "";
	}
	qDebug() << "======================================";
}


void LogicaSudoku::showTablePazleModel()
{
	QString tab = " |   ";
	qDebug() << " \n\n                                      GameModel                                \n\n";
	for(int k = 0; k < capasity; k++)
		tab = tab + " " + QString::number(k+1);
	qDebug() << tab;
	qDebug() <<  "------------------------------------------------";
	tab = "";
	for(int k = 0; k < capasity; k++){
		for(int k1 = 0; k1 < capasity; k1++){
			int val = pazleModel->data(pazleModel->index(k, k1, QModelIndex()), Qt::DisplayRole).toInt();
			if(val == 0)
				tab = tab + "   ";
			else
				tab = tab + " " + QString("%1").arg(val);
		}
		qDebug() << k+1<<"|"<<tab;
		tab = "";
	}
	qDebug() << "======================================";
}

bool LogicaSudoku::checkRectThree(int col, int row, int n)
{
	int s_col, e_col, s_row, e_row;
	if(col >= 0 && col <=2)
		(s_col = 0, e_col =2);
	else if(col >= 3 && col <=5)
		(s_col = 3, e_col =5);
	else
		(s_col = 6, e_col =8);
	if(row >= 0 && row <=2)
		(s_row = 0, e_row =2);
	else if(row >= 3 && row <=5)
		(s_row = 3, e_row =5);
	else
		(s_row = 6, e_row =8);
	for(int col_ = s_col; col_ <= e_col; col_++)
		for(int row_ = s_row; row_ <= e_row; row_++)
			if(gameModel->data(gameModel->index(col_, row_, QModelIndex()), Qt::DisplayRole).toInt() == n)
				return false;
	return true;
}

void LogicaSudoku::mix_value()
{

	QTime midnight(0,0,0);
	qsrand(midnight.msecsTo(QTime::currentTime()));
	int x = 0;
	while (x == 0 || x == num1 || x == num2 || x == num3 || x == num4){
		x = qrand() % capasity+1;
	}
	int y = 0;
	while (y == 0|| y == x || y == num1  || y == num2 || y == num3 || y == num4){
		 y = qrand() % capasity+1;
	}
	st_num?(num3 = x,num4 = y, st_num = false):(num1 = x,num2 = y, st_num = true);
	for(int col = 0; col < 9; col++)
		for(int row = 0; row < 9; row++){
			if(gameModel->data(gameModel->index(col, row, QModelIndex()), Qt::DisplayRole).toInt() == x)
				gameModel->setData( gameModel->index(col, row), y);
			else if(gameModel->data(gameModel->index(col, row, QModelIndex()), Qt::DisplayRole).toInt() == y)
				gameModel->setData( gameModel->index(col, row), x);
		}
}

void LogicaSudoku::createUserPuzzle()
{
	QTime midnight(0,0,0);
	qsrand(midnight.msecsTo(QTime::currentTime()));
	bool empty = false;
	while(!empty){
		int row = qrand() % capasity;
		int col = qrand() % capasity;
		if(pazleModel->data(pazleModel->index(col, row)).toInt()){
			pazleModel->setData( pazleModel->index(col, row), 0);
			empty = true;
		}
	}
}

