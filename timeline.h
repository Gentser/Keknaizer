#ifndef TIMELINE_H
#define TIMELINE_H

#include "timelineitem.h"
#include "allocator.h"

template <class T>
class Timeline
{
private:
    std::vector<TimelineItem<T>/*, Allocator<T>*/> intervals;
public:
    Timeline(){}

    ~Timeline(){}

    std::vector<TimelineItem<T>/*, Allocator<T>*/> getIntervals() const{
        return this->intervals;
    }
    void setIntervals(const std::vector<TimelineItem<T>/*, Allocator<T>*/> &value){
        this->intervals = value;
    }

    void addItem(TimelineItem<T> item){
        this->intervals.push_back(item);
        std::sort(this->intervals.begin(),
                  this->intervals.end(), itemGreater()); // Сортировка
    }
};

#endif // TIMELINE_H
