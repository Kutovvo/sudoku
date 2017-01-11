#ifndef DIALOGFINISH_H
#define DIALOGFINISH_H

#include <QDialog>

namespace Ui {
class DialogFinish;
}

class DialogFinish : public QDialog
{
	Q_OBJECT
public:
	explicit DialogFinish(bool status_, QWidget *parent = 0);
	~DialogFinish();

private:
	Ui::DialogFinish *ui;
};

#endif // DIALOGFINISH_H
