#include "playwidget.h"

PlayWidget::PlayWidget(QStandardItemModel* showPazle_,  QPushButton **btn_, QLCDNumber *lcd_, QWidget *obj = 0):
	QWidget(obj),
	showPazle(showPazle_),
	setUserData(new QStandardItemModel(9,9,this)),
	click_row(-1),
	click_col(-1),
	userNumber(0),
	btn(btn_),
	lcd(lcd_),
	hint(false),
	buttonHint(new bool[9]),
	stepFinish(0),
	createNewGame(false)
{
	setFocusPolicy(Qt::StrongFocus);
	buttonHint[0] = 0;
	for(int row = 0; row < 9; row++){
		buttonHint[row+1] = 0;
		for(int col = 0; col < 9; col++){
			if(showPazle->data(showPazle->index(row, col)).toInt() != 0){
				setUserData->setData(setUserData->index(col,row),-1);
			}
		}
	}
	click_row = -1;
	click_col = -1;
	enableDisableButton(hint);
	showFinish();
}

PlayWidget::~PlayWidget()
{
}

void PlayWidget::resetData()
{
	for(int row = 0; row < 9; row++){
		buttonHint[row+1] = 0;
		for(int col = 0; col < 9; col++){
			if(showPazle->data(showPazle->index(row, col)).toInt() != 0){
				setUserData->setData(setUserData->index(col,row),-1);
			}
			else{
				setUserData->setData(setUserData->index(col,row),0);
			}
		}
	}
	click_row = -1;
	click_col = -1;
	repaint();
	enableDisableButton(hint);
	showFinish();
}

bool PlayWidget::getStatusNewGame()
{
	return createNewGame;
}

void PlayWidget::enableDisableButton(bool act)
{
		if(click_row == -1 && click_col == -1){
			for(int i = 0; i < 10; i++)
					btn[i]->setEnabled(false);
		}
		else{
			if(!hint){
				for(int i = 0; i < 10; i++)
					btn[i]->setDisabled(act);
			}
			else{
				for(int i = 0; i < 9; i++)
					buttonHint[i] = true;
				for(int i = 0; i < 9; i++){
					if(showPazle->data(showPazle->index(click_col, i)).toInt())
						buttonHint[showPazle->data(showPazle->index(click_col, i)).toInt()-1] = false;
					if(setUserData->data(setUserData->index(i, click_col)).toInt())
						buttonHint[setUserData->data(setUserData->index(i, click_col)).toInt()-1] = false;
				}
				for(int i = 0; i < 9; i++){
					if(showPazle->data(showPazle->index(i, click_row)).toInt())
						buttonHint[showPazle->data(showPazle->index(i, click_row)).toInt()-1] = false;
					if(setUserData->data(setUserData->index(click_row, i)).toInt())
						buttonHint[setUserData->data(setUserData->index(click_row, i)).toInt()-1] = false;
				}
				int s_col, e_col, s_row, e_row;
				if(click_col >= 0 && click_col <=2)
					(s_col = 0, e_col =2);
				else if(click_col >= 3 && click_col <=5)
					(s_col = 3, e_col =5);
				else
					(s_col = 6, e_col =8);
				if(click_row >= 0 && click_row <=2)
					(s_row = 0, e_row =2);
				else if(click_row >= 3 && click_row <=5)
					(s_row = 3, e_row =5);
				else
					(s_row = 6, e_row =8);
				for(int col = s_col; col <= e_col; col++)
					for(int row = s_row; row <= e_row; row++){
						if(showPazle->data(showPazle->index(col, row)).toInt())
							buttonHint[showPazle->data(showPazle->index(col, row)).toInt()-1] = false;
						if(setUserData->data(setUserData->index(row, col)).toInt())
							buttonHint[setUserData->data(setUserData->index(row, col)).toInt()-1] = false;
					}
				for(int i = 1; i < 10; i++)
						btn[i]->setEnabled(buttonHint[i-1]);
			}
		}
}

void PlayWidget::setHint(bool hint_)
{
	hint = hint_;
	if(click_row != -1 && click_col != -1)
		enableDisableButton(hint);
}

void PlayWidget::showFinish()
{
	stepFinish = 0;
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 9; col++){
			if(setUserData->data(setUserData->index(col, row)).toInt() != -1 && setUserData->data(setUserData->index(col, row)).toInt() < 1)
				stepFinish++;
		}
	}
	lcd->display(stepFinish);

	if(stepFinish == 0){
		QStandardItemModel* finish = new QStandardItemModel(9,9,this);
		for(int row = 0; row < 9; row++)
			for(int col = 0; col < 9; col++)
					finish->setData(finish->index(row,col),setUserData->data(setUserData->index(row, col)).toInt());
		for(int row = 0; row < 9; row++)
			for(int col = 0; col < 9; col++)
				if(showPazle->data(showPazle->index(col, row)).toInt() != 0)
					finish->setData(finish->index(row,col),showPazle->data(showPazle->index(col, row)).toInt());
		LogicaSudoku *lS = new LogicaSudoku(this);
		lS->setModel(finish);
//		bool deside = lS->checkErrPuzzle();
		QMessageBox* msgBox = new QMessageBox(this);
		msgBox->setWindowTitle("Sudoku");
		if(lS->checkErrPuzzle()){
			msgBox->setText("Вітаємо судоку вирішено вірно!");
			msgBox->setInformativeText("Створити ще гру?");
			msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
		}
		else{
			msgBox->setText("Нажаль у рішенні є помилка, перевірте!");
			msgBox->setStandardButtons(QMessageBox::Close);
		}
		switch (msgBox->exec()) {
		case QMessageBox::Ok:
			createNewGame = true;
			break;
		case QMessageBox::Cancel:
			createNewGame = false;
			break;
		default:
			qDebug()<<"Close";
			break;
		}
		delete lS;


//		df->show();
//		df->exec();
//		qDebug()<<deside;

//		QString tab = " |   ";
//		qDebug() << " \n\n                                      finish                                \n\n";
//		for(int k = 0; k < 9; k++)
//			tab = tab + " " + QString::number(k+1);
//		qDebug() << tab;
//		qDebug() <<  "------------------------------------------------";
//		tab = "";
//		for(int k = 0; k < 9; k++){
//			for(int k1 = 0; k1 < 9; k1++){
//				int val = finish->data(finish->index(k1, k, QModelIndex()), Qt::DisplayRole).toInt();
//				if(val == 0)
//					tab = tab + "   ";
//				else
//					tab = tab + " " + QString("%1").arg(val);
//			}
//			qDebug() << k+1<<"|"<<tab;
//			tab = "";
//		}
//		qDebug() << "======================================";
	}
}

void PlayWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() &  Qt::LeftButton){
		if((event->x() < width && event->x() > 0) && (event->y() < heigth && event->y() > 0)){
			click_row = 0;
			click_col = 0;
			while (step_line*click_row < event->x()) {
				click_row++;
			}
			while (step_line*click_col < event->y()) {
				click_col++;
			}
			click_row -= 1;
			click_col -= 1;
			if(showPazle->data(showPazle->index(click_col, click_row)).toInt() != 0){
				click_row = -1;
				click_col = -1;
				enableDisableButton(true);
			}
			else{
				enableDisableButton(false);
			}
		}
		else{
			click_row = -1;
			click_col = -1;
		}
		repaint();
	}
}

void PlayWidget::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	QRect rect = this->geometry();
	width = rect.width()*0.99;
	heigth = rect.width()*0.99;
	width > heigth?heigth =  width:width =heigth;
	if(heigth>rect.height()){
		width=rect.height()*0.99;
		heigth=rect.height()*0.99;
	}
	step_line = width/9;

	QFont font = painter.font();
	int sizeFont = step_line/2;
	font.setPixelSize(sizeFont);
	painter.setFont(font);


	QRect boundingRect;
	painter.setBrush(QBrush(QColor("#E6E6FA")));
	for(int row = 0; row < 9; row++){
		for(int col = 0; col < 9; col++){
			if(showPazle->data(showPazle->index(row, col)).toInt() > 0){
				painter.setPen(QPen(QColor("#778899"),0,Qt::NoPen));
				painter.drawRect(QRect(step_line*col,step_line*row,step_line,step_line));
				painter.setPen(QPen(QColor("#778899"),1,Qt::SolidLine));
				painter.drawText(QRect( step_line*col+sizeFont*0.7, step_line*row+sizeFont/2, sizeFont, sizeFont), 0, QString::number(showPazle->data(showPazle->index(row, col)).toInt()), &boundingRect);
			}
			else{
				if(setUserData->data(setUserData->index(col, row)).toInt() > 0)
					painter.drawText(QRect( step_line*col+sizeFont*0.7, step_line*row+sizeFont/2, sizeFont, sizeFont), 0, QString::number(setUserData->data(setUserData->index(col, row)).toInt()), &boundingRect);
			}
		}
	}
	painter.setBrush(QBrush(Qt::NoBrush));
	painter.setPen(QPen(QColor("#778899"),3,Qt::SolidLine));
	painter.drawRect(QRect(0,0,width,heigth));
	for(int i = 1; i <9; i++){
		i == 0||i == 3||i == 6||i == 9?painter.setPen(QPen(QColor("#778899"),3,Qt::SolidLine)):painter.setPen(QPen(QColor("#778899"),1,Qt::SolidLine));
		painter.drawLine(QPointF(step_line*i,0),QPointF(step_line*i,heigth));
		painter.drawLine(QPointF(0,step_line*i),QPointF(heigth, step_line*i));
	}

	if(	click_row > -1 && 	click_col > -1){
		painter.setPen(QPen(QColor("#ff0000"),3,Qt::SolidLine));
		painter.drawRect(QRect(step_line*click_row,step_line*click_col,step_line,step_line));
		if(userNumber != 0){
			painter.drawText(QRect( step_line*click_row+sizeFont*0.7, step_line*click_col+sizeFont/2, sizeFont, sizeFont), 0, QString::number(userNumber), &boundingRect);
			userNumber = 0;
		}
	}
}

void PlayWidget::keyPressEvent(QKeyEvent *event)
{
	if(event->key() > 16777233 || event->key() < 16777238 ){
		if(	click_row == -1 && 	click_col == -1){
			switch (event->key()) {
				case 16777234:
						click_row = 9;
						click_col = 8;
						do {} while (showPazle->data(showPazle->index( 8, --click_row)).toInt());
					break;
				case 16777236:
						click_row = -1;
						click_col = 0;
						do {} while (showPazle->data(showPazle->index(0, ++click_row)).toInt());
					break;
				case 16777235:
						click_row = 8;
						click_col = 9;
						do {} while (showPazle->data(showPazle->index(--click_col, 8)).toInt());
					break;
				case 16777237:
						click_row = 0;
						click_col = -1;
						do {} while (showPazle->data(showPazle->index(++click_col, 0)).toInt());
					break;
			}
		}
		else{
				switch (event->key()) {
					case 16777234:
						do {
							 --click_row;
							if(click_row < 0){
								click_row = 8;
								click_col -= 1;
								if(click_col < 0)
									click_col = 8;
							}
						} while (showPazle->data(showPazle->index(click_col, click_row)).toInt());
						break;
					case 16777236:
						do {
							 ++click_row;
							if(click_row > 8){
								click_row = 0;
								click_col += 1;
								if(click_col > 8)
									click_col = 0;
							}
						} while (showPazle->data(showPazle->index(click_col, click_row)).toInt());
						break;
					case 16777235:
						do {
							 --click_col;
							if(click_col < 0){
								click_col = 8;
								click_row -= 1;
								if(click_row < 0)
									click_row = 8;
							}
						} while (showPazle->data(showPazle->index(click_col, click_row)).toInt());
						break;
					case 16777237:
						do {
							 ++click_col;
							if(click_col > 8){
								click_col = 0;
								click_row += 1;
								if(click_row > 8)
									click_row = 0;
							}
						} while (showPazle->data(showPazle->index(click_col, click_row)).toInt());
						break;
				}
			userNumber = setUserData->data(setUserData->index(click_row, click_col)).toInt();
		}
	}
	if(event->key() > 47 && event->key() < 58){
		userNumber = event->key() - 48;
	}
	if(	click_row > -1 && 	click_col > -1){
		setUserData->setData(setUserData->index(click_row,click_col),userNumber);
		userNumber = 0;
	}

	enableDisableButton(false);
	repaint();
	showFinish();
}
