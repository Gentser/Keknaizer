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

    QDateTime startDate;
    QDateTime endDate;
public:
//    Timeline(){
//        this->intervals = new std::vector<TimelineItem<T>, Allocator<T>>; //Раньше тут было пусто
//    }

//    Timeline(std::string name){
//        this->intervals = new std::vector<TimelineItem<T>, Allocator<T>>; //Раньше тут было пусто
//        this->name = name;
//    }

    Timeline(std::string name, QDateTime maxStart, QDateTime maxEnd){
        this->intervals = new std::vector<TimelineItem<T>, Allocator<T>>; //Раньше тут было пусто
        this->name = name;
        this->startDate = maxStart;
        this->endDate = maxEnd;
    }

    ~Timeline(){
        
    }

    QDateTime getEndDate() const
    {
        return endDate;
    }

    void setEndDate(const QDateTime &value)
    {
        endDate = value;
    }

    QDateTime getStartDate() const
    {
        return startDate;
    }

    void setStartDate(const QDateTime &value)
    {
        startDate = value;
    }



    std::vector<TimelineItem<T>, Allocator<T>> * getIntervals() const{ //было без звездочки
        return this->intervals; //.
    }
    void setIntervals(const std::vector<TimelineItem<T>, Allocator<T>> &value){
        this->intervals = value;
    }

    void addItem(TimelineItem<T> *item){ // было без *
        if (findWithoutException(item->getContent())){
            throw TheSameNameException(item->getContent());
        }
        //Если start и end в промежутке данного Timeline, то ОК
        else if (checkStartBorder(item->getStart()) && checkEndBorder(item->getEnd())){
            this->intervals->push_back(*item); //. было без *
            std::sort(this->intervals->begin(), //.
                      this->intervals->end(), itemGreater()); // Сортировка
        }
        //иначе BorderException
        else{
            throw TimelineBorderException(item->getStart(), item->getEnd(), this->getStartDate(), this->getEndDate());
        }
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

     //Времменный костыль
     bool findWithoutException(T content){
         for(auto iter = this->intervals->begin(); iter != this->intervals->end(); ++iter){
             if(iter->getContent() == content){
                 return true; //  iter
             }
         }
        return false;
     }

    void sortIntervals(){
        std::sort(this->intervals->begin(), //.
                  this->intervals->end(), itemGreater()); // Сортировка
    }

    bool editItemContentByName(T oldContent, T newContent){
        TimelineItem<T> *itemToChange = this->findItemByName(oldContent);
        itemToChange->editConntentByContent(newContent);
        return true;
    }

    bool editItemStartByName(T oldContent, QDateTime newStart){
        TimelineItem<T> *itemToChange = this->findItemByName(oldContent);
        if (checkStartBorder(newStart)){
            itemToChange->editStartByContent(newStart);
            this->sortIntervals(); //Сортировка интервалов
            return true;
        }
        else throw TimelineStartBorderException(newStart, this->getStartDate());

    }

    bool editItemEndByName(T oldContent, QDateTime newEnd){
        TimelineItem<T> *itemToChange = this->findItemByName(oldContent);
        if (checkEndBorder(newEnd)){
            itemToChange->editEndByContent(newEnd);
            this->sortIntervals(); //Сортировка интервалов
            return true;
        }
        else throw TimelineEndBorderException(newEnd, this->getEndDate());
    }

    bool editItemTimeByContent(T oldContent, QDateTime newStart, QDateTime newEnd){
        TimelineItem<T> *itemToChange = this->findItemByName(oldContent);
        if (checkEndBorder(newEnd) && checkStartBorder(newStart)){
            itemToChange->editTimeByContent(newStart,newEnd);
            this->sortIntervals(); //Сортировка интервалов
            return true;
        }
        else throw TimelineBorderException(newStart, newEnd, this->getStartDate(),this->getEndDate());

    }

    //CHeck this function!!!
    bool deleteItemByName(T content){
        for(auto iter = this->intervals->begin(); iter != this->intervals->end(); ++iter){
            if(iter->getContent() == content){
                this->intervals->erase(iter); //  iter
                return true;
            }
        }
        throw ItemNameNotFoundException(content);
    }

    bool checkStartBorder(QDateTime start){
        if (start >= this->getStartDate()){
            return true;
        }
        else return false;
    }

    bool checkEndBorder(QDateTime end){
        if (end <= this->getEndDate()){
            return true;
        }
        else return false;

    }


};

#endif // TIMELINE_H
