#ifndef TIMELINE_H
#define TIMELINE_H

#include "timelineitem.h"
#include "allocator.h"

#include "iterator.h"

namespace Gantt {

template <class T>
    class Timeline
    {
    private:
        std::vector<TimelineItem<T>/*, Allocator<T>*/> *intervals; // было без звездочки
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
            this->intervals = new std::vector<TimelineItem<T>/*, Allocator<T>*/>; //Раньше тут было пусто
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



        std::vector<TimelineItem<T>/*, Allocator<T>*/> * getIntervals() const{ //было без звездочки
            return this->intervals; //.
        }
        void setIntervals(const std::vector<TimelineItem<T>/*, Allocator<T>*/> &value){
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

    //    iterator begin(){
    //        return new Iterator<TimelineItem<T>>(intervals, 0); //пока * (указатель)
    //    }

    //    iterator end(){
    //        return new Iterator<TimelineItem<T>>(this->intervals, this->intervals->size());
    //    }

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
         //Надо ставить !() == так правильно, типа не нашлось такого имени
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


        //НЕ ТЕСТИЛОСЬ
        bool editItemContentByName(T oldContent, T newContent){
            TimelineItem<T> *itemToChange = this->findItemByName(oldContent);
            if(!(findWithoutException(newContent))){
                itemToChange->editConntentByContent(newContent);
                return true;
            }
            else throw TheSameNameException(newContent);
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

        //Editing Timeline
        void changeNameOfTimeline(std::string newName){
            this->setName(newName);
        }

        //Check newStart with Start of First item
        bool checkStartWithFirstItem(QDateTime newStartDate){
            QDateTime forChecking = this->intervals->front().getStart();
            if(!this->intervals->empty() && newStartDate <= forChecking){
                return true;
            }
            else throw TimelineNewStartGreaterFirstItemException(newStartDate, forChecking);

        }

        QDateTime getMaxDateOfItems(){
            if(!this->getIntervals()->empty()){
                QDateTime maxDate = QDateTime(QDate(1500,1,1),QTime(0,0));
                for(auto iter = this->intervals->begin(); iter != this->intervals->end(); ++iter ){
                    if (iter->getEnd() > maxDate){
                        maxDate = iter->getEnd();
                    }
                }
                return maxDate;
            }
            else throw EmptyVectorOfItemsException(this->getName());
        }

        //Change Timeline's Start
        bool changeStartDate(QDateTime newStartDate){
            if(checkStartWithFirstItem(newStartDate)){
                this->setStartDate(newStartDate);
                return true;
            }
            else throw TimelineStartBorderException(newStartDate, this->getIntervals()->front().getStart());

        }

        //Change Timeline's End
        bool changeEndDate(QDateTime newEndDate){
            QDateTime maxDateOfItem = getMaxDateOfItems();
            if(newEndDate >= maxDateOfItem){
                this->setEndDate(newEndDate);
                return true;
            }
            else throw TimelineEndBorderException(newEndDate, maxDateOfItem);
        }

        //Change Timeline's borders
        bool changeAllDates(QDateTime newStartDate, QDateTime newEndDate){
            if(checkStartWithFirstItem(newStartDate)){
                QDateTime maxDateOfItem = getMaxDateOfItems();
                if(newEndDate >= maxDateOfItem){
                    this->setStartDate(newStartDate);
                    this->setEndDate(newEndDate);
                    return true;
                }
                else throw TimelineEndBorderException(newEndDate, maxDateOfItem);
            }
            else throw TimelineStartBorderException(newStartDate, this->intervals->front().getStart());
        }


        //NEW EDIT METHOD
        bool editItemData(T oldContent, T newContent, QDateTime newStart, QDateTime newEnd){
            TimelineItem<T> *itemToChange = this->findItemByName(oldContent);
            if(!findWithoutException(newContent)){
                if (checkEndBorder(newEnd) && checkStartBorder(newStart)){
                    itemToChange->editTimeByContent(newStart,newEnd);
                    //А теперь редактируем имя
                    itemToChange->editConntentByContent(newContent);
                    this->sortIntervals(); //Сортировка интервалов

                    return true;
                }
                else throw TimelineBorderException(newStart, newEnd, this->getStartDate(),this->getEndDate());

            }
            else throw TheSameNameException(newContent);
        }

        bool deleteAllItems(){
    //        for(auto iter = this->intervals->begin(); iter != this->intervals->end(); ++iter){
    //            this->intervals->erase(iter);
    //        }
            this->intervals->clear();
            return true;
        }

    };

    //New for GITHUB
    struct timelineGreater{
        template <class T>
        bool operator()(const Timeline<T>& left, const Timeline<T>& right) const{
            return left.getStartDate() < right.getStartDate();
        }
    };
}



#endif // TIMELINE_H
