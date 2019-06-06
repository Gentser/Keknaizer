#include "itemdialog.h"
#include "ui_itemdialog.h"

#include "exception"
#include <QMessageBox>

itemdialog::itemdialog( QDateTime startOfWeek, QDateTime endOfWeek, GanttChart<std::string> *diag, Timeline<std::string> *timeline, int curElement, QWidget *parent) : //new constructor
    QDialog(parent),
    ui(new Ui::itemdialog)
{
    ui->setupUi(this);

    ui->dateTimeEdit_Begin_2->setDateTime(startOfWeek);
    ui->dateTimeEdit_End_2->setDateTime(endOfWeek);

    this->Diagram = diag;

    this->curTimeline = timeline;

    this->curElem = curElement;

    if(this->curElem != -1){
        ui->lineEdit_TaskName_2->setText(QString::fromStdString(timeline->getIntervals()->at(curElement).getContent()));
        ui->dateTimeEdit_Begin_2->setDateTime(timeline->getIntervals()->at(curElement).getStart());
        ui->dateTimeEdit_End_2->setDateTime(timeline->getIntervals()->at(curElement).getEnd());
    }
    else{
        ui->dateTimeEdit_Begin_2->setDateTime(startOfWeek);
        ui->dateTimeEdit_End_2->setDateTime(endOfWeek);

    }
}

itemdialog::~itemdialog()
{
    delete ui;
}

void itemdialog::setTitleName(QString name)
{
    ui->Title->setText(name);
}


void itemdialog::on_addPushButton_clicked()
{
    QDateTime start = ui->dateTimeEdit_Begin_2->dateTime();
    QDateTime end = ui->dateTimeEdit_End_2->dateTime();
    QMessageBox msgBox;
    //тут возможно T
    std::string newContent = ui->lineEdit_TaskName_2->text().toStdString();
    if(this->windowTitle()=="Изменение задачи"){
        try{
            Diagram->editTimelineItem(curTimeline->getName(), curTimeline->getIntervals()->at(this->curElem).getContent(), newContent, start, end);
            this->close();
        } catch(Exception e){
            msgBox.setText(QString::fromStdString(e.getMessage()));
            msgBox.exec();
        }
    }
    else{
        if(newContent == ""){
            msgBox.setText("Введите название задачи");
            msgBox.exec();
        }
        else{
            try{
                Diagram->addItemNew(start, end, newContent);
                this->close();

            } catch(Exception e){
                msgBox.setText(QString::fromStdString(e.getMessage()));
                msgBox.exec();
            }
        }
    }
}
