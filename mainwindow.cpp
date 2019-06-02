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

    firstTimeline.addItem(TimelineItem<std::string>(QDateTime(QDate(2009,5,13), QTime(13,45)),
                                                    QDateTime(QDate(2009,5,13), QTime(20,00)),
                                                    std::string("А это вторая задача!")
                              ));

    Diagram->addTimeline(firstTimeline);
    //Diagram->getTimelines().at(0).getIntervals().at(0).getStart()
//    std::cout << "Check" << item;
//    item.print();

//    firstTimeline.getIntervals().at(0).print();

    //ПОКА какая-то ошибка при итерирвании (без итератора)
//    for (auto iter = Diagram->getTimelines().at(0).getIntervals().begin();
//         iter!=Diagram->getTimelines().at(0).getIntervals().end(); ++iter){

//        iter->print();
//    }

    //Только для тетсирования
    for (int i = 0; i < Diagram->getTimelines().at(0).getIntervals().size(); i++){
        Diagram->getTimelines().at(0).getIntervals().at(i).print();
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
