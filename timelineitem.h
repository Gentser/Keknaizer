#ifndef TIMELINEITEM_H
#define TIMELINEITEM_H

#include <QDateTime>
#include "allocator.h"


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
        this->setStart(start);
        this->setEnd(end);
        this->setContent(content);
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
//        qDebug() << (std::string) this->getContent() ;
        qDebug() << this->getStart().toString() ;
        qDebug() << this->getEnd().toString() ;
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
