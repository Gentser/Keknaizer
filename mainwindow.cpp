#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"
#include "allocator.h"
#include "iterator.h"
#include "exception.h"

#include <QDebug>
#include <itemdialog.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GanttChart<std::string> *Diagram =
            new GanttChart<std::string>();

    //Timeline
    Timeline<std::string> *firstTimeline = new Timeline<std::string>("First_long_Timeline",
                                                                     QDateTime(QDate(2005,1,1), QTime(0,0)),
                                                                     QDateTime(QDate(2020,2,3), QTime(15,35)) );


    try{
        TimelineItem <std::string> *item = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
                                                       QDateTime(QDate(2010,2,3), QTime(15,35)),
                                                       std::string("Задача"));

            //Здесь exception
    //        TimelineItem <std::string> *newItem = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
    //                                                                        QDateTime(QDate(2009,2,3), QTime(15,35)),
    //                                                                        std::string("Задача"));

            //Item
        firstTimeline->addItem(item);





        firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2009,5,13), QTime(13,45)),
                                                        QDateTime(QDate(2009,5,13), QTime(20,00)),
                                                        std::string("А это вторая задача!")
                                  ));

        firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2008,2,20), QTime(17,59)),
                                                             QDateTime(QDate(2008,10,31), QTime(2,20)),
                                                             std::string("А это третья задача!")
                                       ));


        Diagram->addTimeline(firstTimeline);

        qDebug() << "Name of firstTimeline " << QString::fromStdString(firstTimeline->getName());

    //    //Iterator (ИСПОЛЬЗУЙТЕ ТАКОЙ ОБХОД ПО TimelineItem - ам)
    //    for (auto iter = Diagram->getTimelines()->at(0).getIntervals()->begin();
    //         iter != Diagram->getTimelines()->at(0).getIntervals()->end(); ++iter){
    //        qDebug() << "Итерация" ;
    //        iter->print();
    //    }


        qDebug() << "ДО РЕДАКТИРОВАНИЯ" ;
        int i = 0;
        for (auto iter = Diagram->getTimelines()->at(0).getIntervals()->begin();
             iter != Diagram->getTimelines()->at(0).getIntervals()->end(); ++iter){
            qDebug() << "Итерация " << i++ << "name= " << QString::fromStdString(iter->getContent());
            iter->print();
        }

        try{


        } catch (Exception e){
            qCritical() << "CATCH EXCEPT" << QString::fromStdString(e.getMessage()) ;
        }

    } catch (StartGreaterThanEndException e){
        qCritical() << "CATCH EXCEPT" << QString::fromStdString(e.getMessage()) ;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PushButton_addTask_clicked()
{
    itemDialog = new itemdialog;
    itemDialog->setModal(true);
    itemDialog->exec();
}

void MainWindow::on_PushButton_editTask_clicked()
{
    itemDialog = new itemdialog;
    itemDialog->setModal(true);
    itemDialog->exec();
}
