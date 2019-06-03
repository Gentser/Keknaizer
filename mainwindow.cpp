#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"
#include "allocator.h"
#include "iterator.h"
#include "exception.h"
#include "serializer.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Diagram = new GanttChart<std::string>();

    //Serializer<GanttChart<std::string>>& serializer = Serializer<GanttChart<std::string>>::instance();
    //serializer.importFromJson(Diagram);

    //Timeline
    Timeline<std::string> *firstTimeline = new Timeline<std::string>("First_long_Timeline", QDateTime(QDate(2008,1,1), QTime(0,0)), QDateTime(QDate(2019,1,1), QTime(0,0)));


    try{
        TimelineItem <std::string> *item = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
                                                   QDateTime(QDate(2010,2,3), QTime(15,35)),
                                                   std::string("Задача 1"));

        TimelineItem <std::string> *newItem = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
                                                                        QDateTime(QDate(2012,2,3), QTime(15,35)),
                                                                        std::string("Задача 2"));

        //Item
        firstTimeline->addItem(item);

    } catch (StartGreaterThanEndException e){
        qCritical() << "CATCH EXCEPT" << QString::fromStdString(e.getMessage()) ;
    }


    try{
        firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2009,5,13), QTime(13,45)),
                                                        QDateTime(QDate(2009,5,13), QTime(20,00)),
                                                        std::string("А это pervaya задача!")
                                  ));

        firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2008,2,12), QTime(17,59)),
                                                             QDateTime(QDate(2008,10,31), QTime(2,20)),
                                                             std::string("А это вторая задача!")
                                       ));


        Diagram->addTimeline(firstTimeline);
        qDebug() << "Name of firstTimeline " << QString::fromStdString(firstTimeline->getName());


        //Timeline 2
        Timeline<std::string> *secondTimeline = new Timeline<std::string>("Second_long_Timeline", QDateTime(QDate(2001,1,1), QTime(0,0)), QDateTime(QDate(2019,1,1), QTime(0,0)));


        secondTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2011,4,11), QTime(11,45)),
                                                        QDateTime(QDate(2012,4,13), QTime(20,00)),
                                                        std::string("First task!")
                                  ));

        secondTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2012,2,10), QTime(17,59)),
                                                             QDateTime(QDate(2013,10,31), QTime(2,20)),
                                                             std::string("And this is second task!")
                                       ));

        Diagram->addTimeline(secondTimeline);

        //Timeline 3
        Timeline<std::string> *thirdTimeline = new Timeline<std::string>("thirdTimeline", QDateTime(QDate(2001,1,1), QTime(0,0)), QDateTime(QDate(2019,1,12), QTime(0,0)));


        thirdTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2011,3,11), QTime(11,45)),
                                                        QDateTime(QDate(2012,5,13), QTime(20,00)),
                                                        std::string("First task!")
                                  ));

        thirdTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2012,1,10), QTime(17,59)),
                                                             QDateTime(QDate(2013,1,31), QTime(2,20)),
                                                             std::string("And this is second task!")
                                       ));

        Diagram->addTimeline(thirdTimeline);


        qDebug() << "Name of thirdTimeline " << QString::fromStdString(thirdTimeline->getName());

        qDebug() << "Before edit All" ;
        qDebug() << thirdTimeline->getStartDate().toString() << " and " << thirdTimeline->getEndDate().toString();
        thirdTimeline->changeAllDates(QDateTime(QDate(2009,2,20), QTime(18,59)),
                               QDateTime(QDate(2019,2,20), QTime(18,59)));
        qDebug() << "After edit All" ;
        qDebug() << thirdTimeline->getStartDate().toString() << " and " << thirdTimeline->getEndDate().toString();



        Serializer<GanttChart<std::string>>& serializer = Serializer<GanttChart<std::string>>::instance();

        //Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>& serializer = Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>::instance();
        serializer.exportToJson(Diagram);

    } catch (Exception e){

    }




}

MainWindow::~MainWindow()
{
    //Serializer<GanttChart<Timeline<TimelineItem<std::string>>>>& serializer = Serializer<GanttChart<Timeline<TimelineItem<std::string>>>::instance();


    Serializer<GanttChart<std::string>>& serializer = Serializer<GanttChart<std::string>>::instance();

    //Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>& serializer = Serializer::Serialize<GraphLib::Graph<Vertex,Edge>>::instance();
    //serializer.exportToJson(Diagram);
    delete ui;
}
