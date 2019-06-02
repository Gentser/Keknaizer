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
    std::string name;
public:
//    Timeline(){
//        this->intervals = new std::vector<TimelineItem<T>, Allocator<T>>; //Раньше тут было пусто
//    }

    Timeline(std::string name){
        this->intervals = new std::vector<TimelineItem<T>, Allocator<T>>; //Раньше тут было пусто
        this->name = name;
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

    std::string getName() const
    {
        return name;
    }

    void setName(const std::string &value)
    {
        name = value;
    }

    //Editing Items (with i++)
     TimelineItem<T> *findItemByName(T content){ //iterator
        int i = 0;
        for(auto iter = this->intervals->begin(); iter != this->intervals->end(); ++iter, i++){
            if(iter->getContent() == content){
                return &this->intervals->at(i); //  iter
            }
        }
        throw ItemNameNotFoundException(content);
        return nullptr;
    }
};

#endif // TIMELINE_H
