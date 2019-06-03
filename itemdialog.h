#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>

namespace Ui {
class itemdialog;
}

class itemdialog : public QDialog
{
    Q_OBJECT

public:
    explicit itemdialog(QWidget *parent = nullptr);
    ~itemdialog();

private:
    Ui::itemdialog *ui;
};

#endif // ITEMDIALOG_H
