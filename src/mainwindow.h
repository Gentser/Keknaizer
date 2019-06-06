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

    Gantt::GanttChart<std::string> *Diagram;

    Gantt::Timeline<std::string> *curTimeline;
    int curTimeLineIndex;

    QDate curDay;
    int curElem = -1;

    void doAlgorithm();



private slots:
    void on_PushButton_addTask_clicked();
    void on_PushButton_editTask_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_tableWidget_cellClicked(int row, int column);

    void on_PushButton_deleteTask_clicked();

    void on_pushButton_nextTimeLine_clicked();

    void on_pushButton_prevTimeLine_clicked();

private:
    Ui::MainWindow *ui;
    itemdialog *itemDialog;
    QVector<QColor> *colors;

    void resizeGanttArea(int row);
    void drawGanntHeader();
    void drawGantt();
    void drawTimeLineItem(Gantt::TimelineItem<std::string> item, int row, QColor color=QColor(0,0,255));
    void drawTimeLine(Gantt::Timeline<std::string> timeL);
    void drawEmptyGantt();
};

#endif
