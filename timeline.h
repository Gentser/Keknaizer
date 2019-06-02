#ifndef TIMELINE_H
#define TIMELINE_H

#include "timelineitem.h"
#include "allocator.h"

#include "iterator.h"

template <class T>
class Timeline
{
private:
    std::vector<TimelineItem<T>, Allocator<T>> *intervals; // было без звездочки
public:
    Timeline(){
        this->intervals = new std::vector<TimelineItem<T>, Allocator<T>>; //Раньше тут было пусто
    }

    ~Timeline(){
        delete this->intervals; // не было раньше
    }

    std::vector<TimelineItem<T>, Allocator<T>> * getIntervals() const{ //было без звездочки
        return this->intervals; //.
    }
    void setIntervals(const std::vector<TimelineItem<T>, Allocator<T>> &value){
        this->intervals = value;
    }

    void addItem(TimelineItem<T> *item){ // было без *
        this->intervals->push_back(*item); //. было без *
        std::sort(this->intervals->begin(), //.
                  this->intervals->end(), itemGreater()); // Сортировка
    }

    typedef Iterator<TimelineItem<T>>* iterator;

    iterator begin(){
        return new Iterator<TimelineItem<T>>(intervals, 0); //пока * (указатель)
    }

    iterator end(){
        return new Iterator<TimelineItem<T>>(this->intervals, this->intervals->size());
    }

};

#endif // TIMELINE_H
