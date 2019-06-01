<<<<<<< HEAD
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"
#include "allocator.h"
#include "iterator.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GanttChart<std::string> *Diagram =
            new GanttChart<std::string>();

    //Timeline
    Timeline<std::string> firstTimeline;


    TimelineItem <std::string> item = TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
                                               QDateTime(QDate(2010,2,3), QTime(15,35)),
                                               std::string("Задача"));

    //Item
    firstTimeline.addItem(item);

    Diagram->addTimeline(firstTimeline);
    //Diagram->getTimelines().at(0).getIntervals().at(0).getStart()
//    std::cout << "Check" << item;
    item.print();

    firstTimeline.getIntervals().at(0).print();

    Diagram->getTimelines().at(0).getIntervals().at(0).print();




}

MainWindow::~MainWindow()
{
    delete ui;
}
=======
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
>>>>>>> 70376e58ffc9b3f7820f5e9b2bcc0cad92d33f44
