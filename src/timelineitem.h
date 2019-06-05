#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H

#include <QDateTime>
#include "allocator.h"
#include <sstream>
#include <QString>
#include "exception.h"


template <class T>
class TimelineItem
{
private:
    QDateTime start;
    QDateTime end;
    T content;

public:
    TimelineItem(){}

    TimelineItem(QDateTime start, QDateTime end, T content){
        if(end <= start){ // Добавил <=
            throw StartGreaterThanEndException(start, end);
        }
        else{
            this->setStart(start);
            this->setEnd(end);
            this->setContent(content);
        }
    }

    ~TimelineItem(){}

    QDateTime getStart() const
    {
        return start;
    }

    void setStart(const QDateTime &value)
    {
        start = value;
    }

    QDateTime getEnd() const
    {
        return end;
    }

    void setEnd(const QDateTime &value)
    {
        end = value;
    }

    T getContent() const
    {
        return content;
    }

    void setContent(const T &value)
    {
        content = value;
    }

    bool operator < (const TimelineItem<T>& item) const{
        return (this->getStart()< item.getStart());
    }

    void print(){
        qDebug() << this->getStart().toString()  << this->getEnd().toString();
//        qDebug() << this->getEnd().toString() ;
    }

    template<typename E>
    std::string toString(const E& value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    //Edit methods
    bool editConntentByContent(T newContent){
        this->setContent(newContent);
        return true;
    }

    bool editStartByContent(QDateTime newStartTime){
        if(this->getEnd() <= newStartTime){
            throw EditItemNewStartException(newStartTime, this->getEnd());
        }
        else{
            this->setStart(newStartTime);
            return true;
        }
    }

    bool editEndByContent(QDateTime newEndTime){
        if(newEndTime <= this->getStart()){
            throw EditItemNewEndException(this->getStart(), newEndTime);
        }
        else
        {
            this->setEnd(newEndTime);
            return true;
        }
    }

    bool editTimeByContent(QDateTime newStartTime, QDateTime newEndTime){ //Start and End
        if(newEndTime <= newStartTime){
            throw StartGreaterThanEndException(newStartTime, newEndTime); //may be new Exception?
        }
        else{
            this->setStart(newStartTime);
            this->setEnd(newEndTime);
            return true;
        }

    }
};


struct itemGreater{
    template <class T>
    bool operator()(const TimelineItem<T>& left, const TimelineItem<T>& right) const{
        return left.getStart() < right.getStart();
    }
};

template <class T>
std::ostream& operator<<(std::ostream &strm, const TimelineItem<T> &item) {
  std::string cont = (std::string) item.getContent();
  return strm << "Item="<< "(from " << item.getStart().toString() << " until " << item.getEnd().toString() << ")";
}


#endif // TIMELINEITEM_H
