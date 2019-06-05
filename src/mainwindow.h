#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"
#include "itemdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GanttChart<std::string> *Diagram;

    Timeline<std::string> *curTimeline;



private slots:
    void on_PushButton_addTask_clicked();
    void on_PushButton_editTask_clicked();

    void on_calendarWidget_clicked(const QDate &date);

private:
    Ui::MainWindow *ui;
    itemdialog *itemDialog;

    void drawGantt();
};

#endif
