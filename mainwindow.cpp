#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	newGame();

	QHBoxLayout* buttonsLayout1 = new QHBoxLayout();
	QHBoxLayout* buttonsLayout2 = new QHBoxLayout();
	btn =  new QPushButton*[10];
	for(int i = 0; i < 10; i++){
		btn[i] =  new QPushButton(QString::number(i),this);
		i < 5? buttonsLayout1->addWidget(btn[i]): buttonsLayout2->addWidget(btn[i]);
		btn[i]->setMinimumHeight(btn[i]->width());
		btn[i]->setFont(QFont("Times", 30, QFont::Bold));
		btn[i]->setDisabled(true);
	}

	lcd = new QLCDNumber();
	playFeeld = new PlayWidget(pazle, btn, lcd, this);

	vl = new QVBoxLayout();
	vl->addWidget(playFeeld);

	QHBoxLayout* driver = new QHBoxLayout();
	lcd->setFixedSize(100,30);
	hint =  new QCheckBox("Підказати");
	hint->setChecked(false);
	driver->addWidget(hint);
	driver->addWidget(lcd);


	ui->verticalLayout_2->addLayout(vl);
	ui->verticalLayout_2->addLayout(driver);
	ui->verticalLayout_2->addLayout(buttonsLayout1);
	ui->verticalLayout_2->addLayout(buttonsLayout2);

	qDebug()<<this->geometry().width();
	qDebug()<<this->geometry().height();

	connect(btn[0],SIGNAL(clicked(bool)),SLOT(clickButton0()));
	connect(btn[1],SIGNAL(clicked(bool)),SLOT(clickButton1()));
	connect(btn[2],SIGNAL(clicked(bool)),SLOT(clickButton2()));
	connect(btn[3],SIGNAL(clicked(bool)),SLOT(clickButton3()));
	connect(btn[4],SIGNAL(clicked(bool)),SLOT(clickButton4()));
	connect(btn[5],SIGNAL(clicked(bool)),SLOT(clickButton5()));
	connect(btn[6],SIGNAL(clicked(bool)),SLOT(clickButton6()));
	connect(btn[7],SIGNAL(clicked(bool)),SLOT(clickButton7()));
	connect(btn[8],SIGNAL(clicked(bool)),SLOT(clickButton8()));
	connect(btn[9],SIGNAL(clicked(bool)),SLOT(clickButton9()));

	connect(hint,SIGNAL(toggled(bool)),SLOT(changeFlagHint(bool)));

	connect(ui->actionExit,SIGNAL(triggered(bool)),SLOT(close()));
	connect(ui->actionReset,SIGNAL(triggered(bool)),SLOT(resetGame()));
	connect(ui->actionNew_game,SIGNAL(triggered(bool)),SLOT(restartGame()));
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::removeGame()
{
	delete logSud;
	delete playFeeld;
	newGame();
	playFeeld = new PlayWidget(pazle, btn, lcd, this);
	vl->addWidget(playFeeld);
	hint->setChecked(false);

}

void MainWindow::restartGame()
{
	removeGame();
}


void MainWindow::newGame()
{
	logSud = new LogicaSudoku(this);
	pazle = logSud->createPuzzle();
}

void MainWindow::clickButton0()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_0, Qt::NoModifier,"0");
	playFeeld->keyPressEvent(pe);
}

void MainWindow::clickButton1()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier,"1");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton2()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_2, Qt::NoModifier,"2");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton3()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_3, Qt::NoModifier,"3");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton4()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_4, Qt::NoModifier,"4");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton5()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_5, Qt::NoModifier,"5");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton6()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_6, Qt::NoModifier,"6");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton7()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_7, Qt::NoModifier,"7");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton8()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_8, Qt::NoModifier,"8");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::clickButton9()
{
	QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress, Qt::Key_9, Qt::NoModifier,"9");
	playFeeld->keyPressEvent(pe);
	if(playFeeld->getStatusNewGame())
		emit restartGame();
}

void MainWindow::resetGame()
{
	playFeeld->resetData();
}

void MainWindow::changeFlagHint(bool hint_)
{
	playFeeld->setHint(hint_);
}
