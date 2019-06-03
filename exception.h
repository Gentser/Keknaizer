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

class TheSameNameException: public FindItemNameException{
private:
    std:: string nameToAdd;
public:
    TheSameNameException(std::string name): FindItemNameException("Item with Name= " + name + " EXISTS"){
        this->nameToAdd = name;
    }
};

class TimelineExcetion: public Exception{
public:
    TimelineExcetion(std::string msg): Exception(msg) {}
};

class MoreThanTimelineEndException: public TimelineExcetion{
private:
    QDateTime end;
    std::string name;
    QDateTime maxEnd;
public:
    MoreThanTimelineEndException(QDateTime end, std::string nameOfTimeline, QDateTime maxEndDate):
        TimelineExcetion("END DATE= " + end.toString().toStdString() + " more than maxEndDate= " + maxEndDate.toString().toStdString() + "of these timeline= " + nameOfTimeline){


        this->end = end;
        this->name = nameOfTimeline;
        this->maxEnd = maxEndDate;
    }
};

class LessThanTimelineStartException: public TimelineExcetion{
private:
    QDateTime start;
    std::string name;
    QDateTime minStart;
public:
    LessThanTimelineStartException(QDateTime start, std::string nameOfTimeline, QDateTime minStartDate):
        TimelineExcetion("START DATE= " + start.toString().toStdString() + " less than minStartDate= " + minStartDate.toString().toStdString() + "of these timeline= " + nameOfTimeline){


        this->start = start;
        this->name = nameOfTimeline;
        this->minStart = minStartDate;
    }
};

class TimelineBorderException: public TimelineExcetion{
private:
    QDateTime userStart;
    QDateTime userEnd;
    QDateTime trueStart;
    QDateTime trueEnd;
public:
    TimelineBorderException(QDateTime userSt, QDateTime userEn, QDateTime trueSt, QDateTime trueEn): TimelineExcetion("Users start= " + userSt.toString().toStdString() + " end=" + userEn.toString().toStdString() + " are not in interval: TRUEstart= " + trueSt.toString().toStdString() + ", TRUEend= " + trueEn.toString().toStdString()){
        this->userStart = userSt;
        this->userEnd = userEn;
        this->trueStart = trueSt;
        this->trueEnd = trueEn;
    }
};

class TimelineStartBorderException: public TimelineExcetion{
private:
    QDateTime userStart;
    QDateTime trueStart;
public:
    TimelineStartBorderException(QDateTime userSt, QDateTime trueSt): TimelineExcetion("Users start= " + userSt.toString().toStdString() + " is not in <=: TRUEstart= " + trueSt.toString().toStdString()){
        this->userStart = userSt;
        this->trueStart = trueSt;
    }
};

class TimelineEndBorderException: public TimelineExcetion{
private:
    QDateTime userEnd;
    QDateTime trueEnd;
public:
    TimelineEndBorderException(QDateTime userEn, QDateTime trueEn): TimelineExcetion("End=" + userEn.toString().toStdString() + " is not in >=: TRUEend= " + trueEn.toString().toStdString()){
        this->userEnd = userEn;
        this->trueEnd = trueEn;
    }
};

class TimelineNewStartGreaterFirstItemException: public TimelineExcetion{
private:
    QDateTime userStart;
    QDateTime firstItem;
public:
    TimelineNewStartGreaterFirstItemException(QDateTime userStart, QDateTime firstItem): TimelineExcetion("IN EDIT new START= " + userStart.toString().toStdString() + " greater than start of first item= " + firstItem.toString().toStdString()){
        this->userStart = userStart;
        this->firstItem = firstItem;
    }

};

class TimelineNewEndLessLastItemException: public TimelineExcetion{
private:
    QDateTime userEnd;
    QDateTime lastItem;
public:
    TimelineNewEndLessLastItemException(QDateTime userEnd, QDateTime lastItem): TimelineExcetion("IN EDIT new END= " + userEnd.toString().toStdString() + " less than end of last item= " + lastItem.toString().toStdString()){
        this->userEnd = userEnd;
        this->lastItem = lastItem;
    }

};

class EmptyVectorOfItemsException: public TimelineExcetion{
private:
    std::string nameOfTimeline;
public:
    EmptyVectorOfItemsException(std::string name): TimelineExcetion("Vector of Items is EMPTY in Timeline= " + name){
        this->nameOfTimeline = name;
    }
};

#endif // EXCEPTION_H
