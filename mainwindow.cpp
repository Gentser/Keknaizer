#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"
#include "allocator.h"
#include "iterator.h"
#include "exception.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GanttChart<std::string> *Diagram =
            new GanttChart<std::string>();

    //Timeline
    Timeline<std::string> *firstTimeline = new Timeline<std::string>("First_long_Timeline");


    try{
        TimelineItem <std::string> *item = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
                                                   QDateTime(QDate(2010,2,3), QTime(15,35)),
                                                   std::string("Задача"));

        TimelineItem <std::string> *newItem = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
                                                                        QDateTime(QDate(2009,2,3), QTime(15,35)),
                                                                        std::string("Задача"));

        //Item
        firstTimeline->addItem(item);

    } catch (StartGreaterThanEndException e){
        qCritical() << "CATCH EXCEPT" << QString::fromStdString(e.getMessage()) ;
    }



    firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2009,5,13), QTime(13,45)),
                                                    QDateTime(QDate(2009,5,13), QTime(20,00)),
                                                    std::string("А это вторая задача!")
                              ));

    firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2008,2,29), QTime(17,59)),
                                                         QDateTime(QDate(2008,10,31), QTime(2,20)),
                                                         std::string("А это вторая задача!")
                                   ));


    Diagram->addTimeline(firstTimeline);

    qDebug() << "Name of firstTimeline " << QString::fromStdString(firstTimeline->getName());

    //Только для тетсирования
    for (int i = 0; i < Diagram->getTimelines()->at(0).getIntervals()->size(); i++){
        Diagram->getTimelines()->at(0).getIntervals()->at(i).print();
    }

    //Iterator (ИСПОЛЬЗУЙТЕ ТАКОЙ ОБХОД ПО TimelineItem - ам)
    for (auto iter = Diagram->getTimelines()->at(0).getIntervals()->begin();
         iter != Diagram->getTimelines()->at(0).getIntervals()->end(); ++iter){
        qDebug() << "Итерация" ;
        iter->print();
    }

    //ТУТ ПРОБЛЕМА С ИТЕРАТОРОМ(который написали)
//    for (auto iter = Diagram->getTimelines().at(0).begin();
//         iter != Diagram->getTimelines().at(0).end(); ++iter){
//        iter->get_value.print();
//    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
