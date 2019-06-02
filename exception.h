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

class EditTimeException: public Exception{
public:
    EditTimeException(std::string msg): Exception(msg){

    }

};


class StartGreaterThanEndException : public EditTimeException{
private:
    QDateTime start;
    QDateTime end;
public:
    StartGreaterThanEndException(QDateTime start, QDateTime end): EditTimeException("Start " + start.toString().toStdString() + " greater than end " + end.toString().toStdString()){
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


class EditItemNewStartException: public EditTimeException{// end <= newStart
private:
    QDateTime newStart;
    QDateTime end;
public:
    EditItemNewStartException(QDateTime newStart, QDateTime end): EditTimeException("While Editing NEWSTART= " + newStart.toString().toStdString() + " greater than old end " + end.toString().toStdString()){
        this->newStart = newStart;
        this->end = end;
    }

    QString getNewStart(){
        return this->newStart.toString();
    }

    QString getEnd(){
        return this->end.toString();
    }
};

class EditItemNewEndException: public EditTimeException{
private:
    QDateTime start;
    QDateTime newEnd;
public:
    EditItemNewEndException(QDateTime start, QDateTime newEnd): EditTimeException("While Editing NEWEND= " + newEnd.toString().toStdString() + " less than old start " + start.toString().toStdString()){
        this->start = start;
        this->newEnd = newEnd;
    }

    QString getStart(){
        return this->start.toString();
    }

    QString getNewEnd(){
        return this->newEnd.toString();
    }

};

class FindItemNameException: public Exception
{
public:
    FindItemNameException(std::string msg): Exception(msg) {}
};

class ItemNameNotFoundException: public FindItemNameException{
private:
    std::string nameToFind;
public:
    ItemNameNotFoundException(std::string name): FindItemNameException("Item with Name= " + name + " is NOT FOUND"){
        this->nameToFind = name;
    }
};

#endif // EXCEPTION_H
