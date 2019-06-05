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

    Serializer<GanttChart<std::string>>& serializer = Serializer<GanttChart<std::string>>::instance();
    serializer.importFromJson(Diagram);

//   // Timeline
//    Timeline<std::string> *firstTimeline = new Timeline<std::string>("First_long_Timeline", QDateTime(QDate(2008,1,1), QTime(0,0)), QDateTime(QDate(2019,1,1), QTime(0,0)));


//    try{
//        TimelineItem <std::string> *item = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
//                                                   QDateTime(QDate(2010,2,3), QTime(15,35)),
//                                                   std::string("Task 1"));

//        TimelineItem <std::string> *newItem = new TimelineItem<std::string>(QDateTime(QDate(2010,1,1), QTime(0,0)),
//                                                                        QDateTime(QDate(2012,2,3), QTime(15,35)),
//                                                                        std::string("Task 2"));

//        //Item
//        firstTimeline->addItem(item);

//    } catch (StartGreaterThanEndException e){
//        qCritical() << "CATCH EXCEPT" << QString::fromStdString(e.getMessage()) ;
//    }


//    try{
//        firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2009,5,13), QTime(13,45)),
//                                                        QDateTime(QDate(2009,5,13), QTime(20,00)),
//                                                        std::string("This is pervaya zadacha!")
//                                  ));

//        firstTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2008,2,12), QTime(17,59)),
//                                                             QDateTime(QDate(2008,10,31), QTime(2,20)),
//                                                             std::string("This is vtoraya zadacha!")
//                                       ));


//        Diagram->addTimeline(firstTimeline);
//        qDebug() << "Name of firstTimeline " << QString::fromStdString(firstTimeline->getName());


//        //Timeline 2
//        Timeline<std::string> *secondTimeline = new Timeline<std::string>("Second_long_Timeline", QDateTime(QDate(2001,1,1), QTime(0,0)), QDateTime(QDate(2019,1,1), QTime(0,0)));


//        secondTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2011,4,11), QTime(11,45)),
//                                                        QDateTime(QDate(2012,4,13), QTime(20,00)),
//                                                        std::string("First task!")
//                                  ));

//        secondTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2012,2,10), QTime(17,59)),
//                                                             QDateTime(QDate(2013,10,31), QTime(2,20)),
//                                                             std::string("And this is second task!")
//                                       ));

//        Diagram->addTimeline(secondTimeline);

//        //Timeline 3
//        Timeline<std::string> *thirdTimeline = new Timeline<std::string>("thirdTimeline", QDateTime(QDate(2001,1,1), QTime(0,0)), QDateTime(QDate(2019,1,12), QTime(0,0)));


//        thirdTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2011,3,11), QTime(11,45)),
//                                                        QDateTime(QDate(2012,5,13), QTime(20,00)),
//                                                        std::string("First task!")
//                                  ));

//        thirdTimeline->addItem(new TimelineItem<std::string>(QDateTime(QDate(2012,1,10), QTime(17,59)),
//                                                             QDateTime(QDate(2013,1,31), QTime(2,20)),
//                                                             std::string("And this is second task!")
//                                       ));

//        Diagram->addTimeline(thirdTimeline);


//        qDebug() << "Name of thirdTimeline " << QString::fromStdString(thirdTimeline->getName());

//        qDebug() << "Before edit All" ;

//        QLocale curLocale(QLocale("US"));
//        QLocale::setDefault(curLocale);

//        qDebug() << thirdTimeline->getStartDate().toString() << " and " << QLocale().toString(thirdTimeline->getEndDate());
//        thirdTimeline->changeAllDates(QDateTime(QDate(2009,2,20), QTime(18,59)),
//                               QDateTime(QDate(2019,2,20), QTime(18,59)));
//        qDebug() << "After edit All" ;
//        qDebug() << thirdTimeline->getStartDate().toString() << " and " << thirdTimeline->getEndDate().toString();



//    } catch (Exception e){

//    }

    try{

//        QDateTime some = QDateTime(QDate(2009,2,21), QTime(18,59));
//        qDebug() << some.date().dayOfWeek();
//        qDebug() << some.date().weekNumber();

//        qDebug() << some.date().addDays(-some.date().dayOfWeek()+1).dayOfWeek();
//        qDebug() << some.date().addDays(-some.date().dayOfWeek()+1).weekNumber();
//        qDebug() << some.date().addDays(-some.date().dayOfWeek()+1);

//        QDateTime newDate = QDateTime(QDate(some.date().addDays(-some.date().dayOfWeek()+1)));

//        qDebug() << newDate.toString();

//        QDateTime finishDate = QDateTime(QDate(newDate.date().addDays(6)));

//        qDebug() << finishDate.toString();

//        qDebug() << finishDate.date().weekNumber() << " == " << newDate.date().weekNumber();

//        qDebug() << "New name of Timeline= " << "Week_" +QString::number(newDate.date().weekNumber()) + "_" +  QString::number(newDate.date().year());

//        QDateTime newSome = QDateTime(QDate());

        Diagram->addItemNew(QDateTime(QDate(2030,3,20), QTime(18,59)),
                            QDateTime(QDate(2030,3,21), QTime(13,45)), "Something new");


    } catch (Exception e){

    }


    // Change Gantt Chart
    QTableWidget *wg = ui->tableWidget;
    wg->setRowCount(3);
    wg->clear();
    wg->setColumnCount(1+7*24);

    int clSize = 25 /*(wg->width() - wg->columnWidth(0))/(7*24)*/;
    for (int i=1; i < wg->columnCount(); i++)
        wg->setColumnWidth(i, clSize);

    drawGantt();

}

void MainWindow::drawGantt()
{
    QTableWidget *wg = ui->tableWidget;
    wg->clear();

    // Заполняем шапку с часами
    for (int i = 0; i < 7; i++) // Проходим по дням недели, объединяя часы в дни
    {
        wg->setSpan(0, 1+i*24, 1, 24);
        QTableWidgetItem *task = new QTableWidgetItem;
        task->setTextAlignment(Qt::AlignVCenter);
        task->setFont(QFont("Times", 10, QFont::Bold));
        if (i%2==0)
            task->setBackground(Qt::gray);

        switch (i) {
            case 0:
                task->setText("Понедельник");
                break;
            case 1:
                task->setText("Вторник");
                break;
            case 2:
                task->setText("Среда");
                break;
            case 3:
                task->setText("Четверг");
                break;
            case 4:
                task->setText("Пятница");
                break;
            case 5:
                task->setText("Суббота");
                break;
            case 6:
                task->setText("Воскресенье");
                break;
        }

        wg->setItem(0, 1+i*24, task);
    }

    for (int i = 0; i < 24*7; i++) // Проходим по дням недели и рисуем каждый час
    {
        QTableWidgetItem *task = new QTableWidgetItem;
        task->setTextAlignment(Qt::AlignVCenter);
        //        QFont font(QFont("Helvetica [Cronyx]", 8, QFont::DemiBold));
        //        task->setTextColor(Qt::gray);
        QFont font(QFont("Helvetica [Cronyx]", 8, QFont::Light));
        font.setStyle(QFont::StyleItalic);
        task->setFont(font);
        task->setText(QString::number(i%24));
        wg->setItem(1, 1+i, task);
    }
}

MainWindow::~MainWindow()
{
    //Serializer<GanttChart<Timeline<TimelineItem<std::string>>>>& serializer = Serializer<GanttChart<Timeline<TimelineItem<std::string>>>::instance();


    Serializer<GanttChart<std::string>>& serializer = Serializer<GanttChart<std::string>>::instance();

    serializer.exportToJson(Diagram);
    delete ui;
}

void MainWindow::on_PushButton_addTask_clicked()
{
    itemDialog = new itemdialog;
    itemDialog->setModal(true);
    itemDialog->setTitleName("Добававление задачи");
    itemDialog->exec();

    // Redraw Gantt chart
    drawGantt();
}

void MainWindow::on_PushButton_editTask_clicked()
{
    itemDialog = new itemdialog;
    itemDialog->setModal(true);
    itemDialog->setTitleName("Изменение задачи");
    itemDialog->exec();
}
