#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QDateTime>
#include <iostream>
#include <QDebug>
#include <QErrorMessage>

//#include <QTextCodec>




class Exception
{
private:
    std::string message;
public:
    Exception(){
        printMessage();
    }

    Exception(const std::string& msg): message(msg){
        printMessage();
    }

    ~Exception(){}

    std::string getMessage() const {
        return message;
    }

    void printMessage(){
//        QTextCodec::setCodecForLocale(QTextCodec::codecForName("IBM 866"));
        std::cerr << getMessage() << std::endl; //Русские буквы не отображеются
        qCritical() << "ERROR: " << QString::fromStdString(getMessage());
    }
};

class StartGreaterThanEndException : public Exception{
private:
    QDateTime start;
    QDateTime end;
public:
    StartGreaterThanEndException(QDateTime start, QDateTime end): Exception("Start " + start.toString().toStdString() + " greater than end " + end.toString().toStdString()){
        this->start = start;
        this->end = end;
    }

    QString getStart(){
        return this->start.toString();
    }

    QString getEnd(){
        return this->end.toString();
    }

};

#endif // EXCEPTION_H
