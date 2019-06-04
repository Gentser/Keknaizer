#include "itemdialog.h"
#include "ui_itemdialog.h"

itemdialog::itemdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::itemdialog)
{
    ui->setupUi(this);
}

itemdialog::~itemdialog()
{
    delete ui;
}

void itemdialog::setTitleName(QString name)
{
    ui->Title->setText(name);
}
