#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ganttchart.h"
#include "timeline.h"
#include "timelineitem.h"
#include "allocator.h"
#include "iterator.h"
#include "exception.h"
#include "serializer.h"

#include <QMessageBox>


#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Diagram = new Gantt::GanttChart<std::string>();

    Serializer<Gantt::GanttChart<std::string>>& serializer = Serializer<Gantt::GanttChart<std::string>>::instance();
    serializer.importFromJson(Diagram);

    bool cool = Gantt::GanttChart<std::string>::Invariant::isSorted(Diagram);


    // Определить текущие дату и день (текущее время, или данные из первого TimeLine)
    if (Diagram->getTimelines()->size() == 0 ||
            Diagram->getTimelines()->at(0).getIntervals()->size()==0) { // Возможно, если кол-во Item в 1-ом TimeLine==0, следует переходить к следующему TimeLine
        // Устанавливаем текущую дату и TimeLine
        curDay = ui->calendarWidget->selectedDate();
        curTimeline = Diagram->checkExisting(QDateTime(curDay));
    } else {
        // Устанавливаем дату первого TimeLine
        curTimeline = &Diagram->getTimelines()->at(0);
        QDateTime startDate = curTimeline->getIntervals()->at(0).getStart();
        ui->calendarWidget->setSelectedDate(startDate.date());
        curDay = startDate.date();
    }

    // Текущий элемент для редактирования (+флаг - элемент для редактирования найден)
    curElem = -1;

    // Текущий элемент для отображения при переходе между TimeLine
    curTimeLineIndex = -1;

    // Make colors vector for Gantt chart drawing
    colors = new QVector<QColor>();
    colors->push_back(Qt::red);
    colors->push_back(Qt::magenta);
    colors->push_back(Qt::blue);
    colors->push_back(Qt::yellow);



////   // Timeline
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

//        Diagram->addTimeline(new Timeline<std::string>("TEST", QDateTime(QDate(2019,6,17)),
//                                                               QDateTime(QDate(2019,6,23), QTime(23,59))));


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

    if(curTimeline != nullptr){
        drawGantt();
    }
    else{
        drawEmptyGantt();
    }

    doAlgorithm();

}


void MainWindow::resizeGanttArea(int row)
{
    QTableWidget *wg = ui->tableWidget;
    wg->setColumnCount(1+7*24);
    wg->setRowCount(2+row);
    wg->clear();

    int clSize = 25 /*(wg->width() - wg->columnWidth(0))/(7*24)*/;
    for (int i=1; i < wg->columnCount(); i++)
    {
        wg->setColumnWidth(i, clSize);
    }

}

void MainWindow::drawTimeLineItem(Gantt::TimelineItem<std::string> item, int row, QColor color)
{
//    qDebug() << "Dates: " << item.getStart().toString() << " -> " << item.getEnd().toString();
    QDateTime startDate = item.getStart();
    QDateTime endDate = item.getEnd();

    qint64 intervalSec = startDate.secsTo(endDate);
//    qDebug() << "\tTime diff ms: " <<QString::number(intervalSec);

    qint64 intervalH = intervalSec/3600;
    // Проверка на то, что задача длится в неполные часы (час начала и час конца)
    intervalH = (startDate.time().minute() != 0) ? intervalH+1 : intervalH;
    intervalH = (endDate.time().minute() != 0) ? intervalH+1 : intervalH;
//    qDebug() << "\tTime diff h: " <<QString::number(intervalH);

    int dayOfWeek = startDate.date().dayOfWeek();
    int hour = startDate.time().hour();
//    qDebug() << "Start date: dayOfWeek" << dayOfWeek << "; " << hour << "h";

    QTableWidget *wg = ui->tableWidget;

    // Show timeline
    for (int i=0; i < intervalH; i++)
    {
        QTableWidgetItem *task = new QTableWidgetItem;
        task->setBackground(color);
        wg->setItem(2+row, (dayOfWeek-1)*24 + 1+hour+i, task);  // setItem(<item_index>, <column>, task)!!!
    }

    // Show item name
    QTableWidgetItem *task = new QTableWidgetItem;
    task->setText(QString::fromStdString(item.getContent()));
    wg->setItem(2+row, 0, task);
}

void MainWindow::drawGanntHeader()
{
    QTableWidget *wg = ui->tableWidget;

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

void MainWindow::drawGantt()
{
    QColor color(255,0,0);  // Цвет заливки времени

//    std::vector<TimelineItem<std::string>> *timeLineItems = Diagram->getTimelines()->at(2).getIntervals();
    std::vector<Gantt::TimelineItem<std::string>, Allocator<Gantt::TimelineItem<std::string>>> *timeLineItems = curTimeline->getIntervals();
    int itemNubmer = timeLineItems->size();

    resizeGanttArea(itemNubmer);    // Меняем кол-во строк в таблице (кол-во задач)
    drawGanntHeader();              // Заполняем шапку с часами

    for (int i=0; i < timeLineItems->size(); i++)
    {
        Gantt::TimelineItem<std::string> item = timeLineItems->at(i);
//        drawTimeLineItem(item, i, color);
        drawTimeLineItem(item, i, colors->at(i%colors->size()));  // FORWARD LINE NUMBER!!!
    }
}

void MainWindow::drawEmptyGantt()
{
    QTableWidget *wg = ui->tableWidget;
    wg->clear();
    wg->setColumnCount(0);
    wg->setRowCount(0);

    QMessageBox msgBox;
    msgBox.setText("На этой неделе у вас не существует задач!");
    msgBox.exec();
}

MainWindow::~MainWindow()
{
    //Serializer<GanttChart<Timeline<TimelineItem<std::string>>>>& serializer = Serializer<GanttChart<Timeline<TimelineItem<std::string>>>::instance();


    Serializer<Gantt::GanttChart<std::string>>& serializer = Serializer<Gantt::GanttChart<std::string>>::instance();

    serializer.exportToJson(Diagram);
    delete ui;
}

void MainWindow::on_PushButton_addTask_clicked()
{

    itemDialog = new itemdialog(QDateTime(curDay, QTime(1,0)), QDateTime(curDay, QTime(23,50)), Diagram, curTimeline, curElem);
    itemDialog->setModal(true);
    itemDialog->setTitleName("Добавление задачи");
    itemDialog->setWindowTitle("Добавление задачи");


    itemDialog->exec();

    // Redraw Gantt chart
    curTimeline = Diagram->checkExisting(QDateTime(curDay));
    drawGantt();
    doAlgorithm();
}

void MainWindow::on_PushButton_editTask_clicked()
{
    itemDialog = new itemdialog(QDateTime(curDay, QTime(1,0)), QDateTime(curDay, QTime(23,50)), Diagram, curTimeline, curElem);
    itemDialog->setModal(true);
    itemDialog->setTitleName("Изменение задачи");
    itemDialog->setWindowTitle("Изменение задачи");
    itemDialog->exec();

    // Redraw Gantt chart
    curTimeline = Diagram->checkExisting(QDateTime(curDay));
    drawGantt();
    doAlgorithm();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    curElem = -1;
    curDay = date;
    QMessageBox msgBox;
    curTimeline = Diagram->checkExisting(QDateTime(date));

    // Redraw Gantt chart in right way
    if(curTimeline == nullptr){
        drawEmptyGantt();
    } else{
        drawGantt();
    }

    doAlgorithm();
}

void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if(column == 0){
        if(row >= 2){
            curElem = row-2;
            ui->PushButton_deleteTask->setEnabled(true);
            ui->PushButton_editTask->setEnabled(true);
//            qDebug() << row << "_" << column;
            return;
        }
    }
    curElem = -1;
    ui->PushButton_deleteTask->setEnabled(false);
    ui->PushButton_editTask->setEnabled(false);
//    qDebug() << row << "_" << column;
}

void MainWindow::on_PushButton_deleteTask_clicked()
{
    QMessageBox msgBox;
    try{
        Diagram->deleteItemFromTimeline(curTimeline, curTimeline->getIntervals()->at(curElem).getContent());

        if(curTimeline->getIntervals()->empty()){
            Diagram->deleteTimeline(curTimeline);
            drawEmptyGantt();
        }
        else{
            drawGantt();
        }

        // Redraw Gantt chart
        curTimeline = Diagram->checkExisting(QDateTime(curDay));

        curElem = -1;
        ui->PushButton_deleteTask->setEnabled(false);
        ui->PushButton_editTask->setEnabled(false);

    } catch(Exception e){
        msgBox.setText(QString::fromStdString(e.getMessage()));
        msgBox.exec();
    }

    doAlgorithm();
}

void MainWindow::on_pushButton_nextTimeLine_clicked()
{
    if (curTimeLineIndex > -1){
        curTimeLineIndex++;
    } else {

        if (curTimeline == nullptr) {
            curTimeLineIndex = Diagram->getTimelines()->size()-1;
        } else {
            curTimeLineIndex = Diagram->findTimelineIndex(curTimeline->getName());
            if (curTimeLineIndex == -1) {
                curTimeLineIndex = Diagram->getTimelines()->size()-1;
            } else {
                curTimeLineIndex++;
            }
        }
    }

    if (curTimeLineIndex > Diagram->getTimelines()->size()-1)
        curTimeLineIndex = Diagram->getTimelines()->size()-1;

    curTimeline = &Diagram->getTimelines()->at(curTimeLineIndex);
    QDate date;
    if (curTimeline->getIntervals()->size() > 0)
        date = curTimeline->getIntervals()->at(0).getStart().date();
    else
        date = curTimeline->getStartDate().date();

    ui->calendarWidget->setSelectedDate(date);
    curDay = date;

    // Redraw Gantt chart in right way
    drawGantt();
    doAlgorithm();
}

void MainWindow::on_pushButton_prevTimeLine_clicked()
{
    if (curTimeLineIndex > -1){
        curTimeLineIndex--;
    } else {

        if (curTimeline == nullptr) {
            curTimeLineIndex = 0;
        } else {
            curTimeLineIndex = Diagram->findTimelineIndex(curTimeline->getName());
            if (curTimeLineIndex == -1) {
                curTimeLineIndex = 0;
            } else {
                curTimeLineIndex--;
            }
        }
    }

    curTimeLineIndex = (curTimeLineIndex < 0) ? 0 : curTimeLineIndex;

    curTimeline = &Diagram->getTimelines()->at(curTimeLineIndex);
    QDate date;
    if (curTimeline->getIntervals()->size() > 0)
        date = curTimeline->getIntervals()->at(0).getStart().date();
    else
        date = curTimeline->getStartDate().date();

    ui->calendarWidget->setSelectedDate(date);
    curDay = date;

    // Redraw Gantt chart in right way
    drawGantt();
    doAlgorithm();
}

void MainWindow::doAlgorithm(){
    qint64 sumOfBusy = 0;
    qint64 sumOfIntersections = 0;
    if (curTimeline != nullptr){
        int i = 0;
        for(auto iter = curTimeline->getIntervals()->begin(); iter != curTimeline->getIntervals()->end(), i < curTimeline->getIntervals()->size()-1; ++iter, i++){
            QDateTime startDate = curTimeline->getIntervals()->at(i).getStart();
            QDateTime endDate = curTimeline->getIntervals()->at(i).getEnd();

            qint64 intervalSec = startDate.secsTo(endDate);
            sumOfBusy+= intervalSec;

            QDateTime nextStartTime = curTimeline->getIntervals()->at(i+1).getStart();
            QDateTime nextEndTime = curTimeline->getIntervals()->at(i+1).getEnd();

            if(nextStartTime <= endDate && nextEndTime > endDate){
                sumOfIntersections += nextStartTime.secsTo(endDate);

            } else if(nextStartTime <= endDate && nextEndTime <= endDate){
                sumOfIntersections += nextStartTime.secsTo(nextEndTime);

            }

        }
        int end = curTimeline->getIntervals()->size()-1;
        QDateTime startDate = curTimeline->getIntervals()->at(end).getStart();
        QDateTime endDate = curTimeline->getIntervals()->at(end).getEnd();

        sumOfBusy += startDate.secsTo(endDate);
        sumOfBusy /= 3600;
        sumOfIntersections /= 3600;


        int result = sumOfBusy - sumOfIntersections;

//        qDebug() << "Result of ALg= " << result ;
        ui->label_freeTime->setText("Занято времени: " + QString::number(result) + "ч/" + QString::number(16*7) + "ч");
        ui->label_freeTime->setAlignment(Qt::AlignCenter);
    }
    else{
        ui->label_freeTime->setText("Свободного времени: " + QString::number(16*7) + "ч");
        ui->label_freeTime->setAlignment(Qt::AlignCenter);
    }
}
