#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
