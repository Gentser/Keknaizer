#include "itemdialog.h"
#include "ui_itemdialog.h"

#include "exception"
#include <QMessageBox>

itemdialog::itemdialog( QDateTime startOfWeek, QDateTime endOfWeek, GanttChart<std::string> *diag, QWidget *parent) : //new constructor
    QDialog(parent),
    ui(new Ui::itemdialog)
{
    ui->setupUi(this);

    ui->dateTimeEdit_Begin_2->setDateTime(startOfWeek);
    ui->dateTimeEdit_End_2->setDateTime(endOfWeek);

    this->Diagram = diag;
}

itemdialog::~itemdialog()
{
    delete ui;
}

void itemdialog::setTitleName(QString name)
{
    ui->Title->setText(name);
}

void itemdialog::on_buttonBox_accepted()
{
    QDateTime start = ui->dateTimeEdit_Begin_2->dateTime();
    QDateTime end = ui->dateTimeEdit_End_2->dateTime();

    QMessageBox msgBox;

    //тут возможно T
    std::string newContent = ui->lineEdit_TaskName_2->text().toStdString();

    if(newContent == ""){
        msgBox.setText("Введите название задачи");
        msgBox.exec();
    }
    else{
        try{
            Diagram->addItemNew(start, end, newContent);

        } catch(Exception e){
            msgBox.setText(QString::fromStdString(e.getMessage()));
            msgBox.exec();
//            on_buttonBox_accepted();
//            itemdialog newItemdialog(ui->dateTimeEdit_Begin_2->dateTime(), ui->dateTimeEdit_End_2->dateTime(), Diagram);
//            newItemdialog.setModal(true);
//            newItemdialog.setTitleName("Добавление задачи");

//            newItemdialog.exec();
        }
    }


}

void itemdialog::on_addPushButton_clicked()
{
    QDateTime start = ui->dateTimeEdit_Begin_2->dateTime();
    QDateTime end = ui->dateTimeEdit_End_2->dateTime();

    QMessageBox msgBox;

    //тут возможно T
    std::string newContent = ui->lineEdit_TaskName_2->text().toStdString();

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
