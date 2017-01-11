#include "dialogfinish.h"
#include "ui_dialogfinish.h"

DialogFinish::DialogFinish(bool status_, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DialogFinish)
{
	ui->setupUi(this);
}

DialogFinish::~DialogFinish()
{
	delete ui;
}
