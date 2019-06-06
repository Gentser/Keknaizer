#ifndef ITEMDIALOG_H
#define ITEMDIALOG_H

#include <QDialog>
#include "ganttchart.h"

namespace Ui {
class itemdialog;
}

class itemdialog : public QDialog
{
    Q_OBJECT

public:
    explicit itemdialog(QDateTime startOfWeek, QDateTime endOfWeek, GanttChart<std::string> *diag, Timeline<std::string> *timeline, int curElement, QWidget *parent = nullptr);

    void setTitleName(QString str);
    ~itemdialog();

private slots:
//    void on_buttonBox_accepted();

    void on_addPushButton_clicked();

private:
    Ui::itemdialog *ui;

    //T
    GanttChart<std::string> *Diagram;

    Timeline<std::string> *curTimeline;

    int curElem;
};

#endif // ITEMDIALOG_H
