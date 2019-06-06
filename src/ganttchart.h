#ifndef GANTTCHART_H
#define GANTTCHART_H
#include <QDateTime>
#include "timeline.h"
#include "iterator.h"

namespace Gantt {

template <class T>
    class GanttChart
    {
    private:
        QDateTime minDate;
        QDateTime maxDate;
        std::vector<Timeline<T>, Allocator<Timeline<T>>> *timelines; // <TimelineItem<T>>


    public:
    //    template <class T>
        class Invariant
        {
        public:
            Invariant();
            ~Invariant();

            static bool isSorted(GanttChart<T> *container){
                for(int i = 0; i < container->getTimelines()->size()-1;i++){
                    if(!(container->getTimelines()->at(i).getIntervals()->size() == 0)){
                        for(int j = 0; j < container->getTimelines()->at(i).getIntervals()->size()-1; j++){
                            if (container->getTimelines()->at(i).getIntervals()->at(j).getStart() > container->getTimelines()->at(i).getIntervals()->at(j+1).getStart()){
                                return false;
                            }
                        }
                        if(container->getTimelines()->at(i).getStartDate() > container->getTimelines()->at(i+1).getStartDate()){
                            return false;
                        }
                    }
                }
                return true;
            }

        };


        GanttChart(){
            this->setMinDate(QDateTime(QDate(2000,1,1), QTime(0,0)));
            this->setMaxDate(QDateTime(QDate(2020,1,1), QTime(0,0)));

            this->timelines = new std::vector<Timeline<T>, Allocator<Timeline<T>>>;
        }

        ~GanttChart() {}

        //For github
        void sortTimelines(){
            std::sort(this->getTimelines()->begin(),
                      this->getTimelines()->end(), timelineGreater());
        }

        void addTimeline(Timeline<T> *timeLine){
            this->timelines->push_back( *timeLine); // было без *
            //For gituhub
            this->sortTimelines();

        }

        QDateTime getMinDate() const
        {
            return minDate;
        }
        void setMinDate(const QDateTime &value)
        {
            minDate = value;
        }
        QDateTime getMaxDate() const
        {
            return maxDate;
        }
        void setMaxDate(const QDateTime &value)
        {
            maxDate = value;
        }
        std::vector<Timeline<T>, Allocator<Timeline<T>>> *getTimelines() const //<TimelineItem<T>>
        {
            return timelines;
        }
        void setTimelines(const std::vector<Timeline<T>, Allocator<Timeline<T>>> &value) // <TimelineItem<T>>
        {
            timelines = value;
        }


        //    typedef Iterator<T>* iterator;

        //               iterator begin(){
        //                   return new Iterator<T>(timelines, 0);
        //               }
        //               iterator end(){
        //                   return new Iterator<T>(this->timelines, this->timelines->size());
        //               }


        //EditItems
        bool editTimelineItem(std::string nameOfTimeline, T oldContent, T newContent, QDateTime newStart, QDateTime newEnd){
            if(GanttChart<T>::Invariant::isSorted(this)){
                Timeline<T> *timelineToChange = this->findTimeline(nameOfTimeline);
                if(oldContent == newContent){
                    //Редактирование только времени
                    timelineToChange->editItemTimeByContent(oldContent, newStart, newEnd);
                    return true;
                }
                //редактирование имени и времени
                else {
                    timelineToChange->editItemData(oldContent, newContent, newStart, newEnd);
                    return true;
                }
            }
            else return false;
        }

    //    bool deleteItem(std::string nameOfTimeline,  T content){
    //        Timeline<T> *timelineToChange = this->findTimeline(nameOfTimeline);
    //        timelineToChange->deleteItemByName(content);
    //        return true;
    //    }

        bool deleteItemFromTimeline(Timeline<T> *curTimeline, T content ){
            if(GanttChart<T>::Invariant::isSorted(this)){

                if(curTimeline != nullptr){
                    curTimeline->deleteItemByName(content);
                    return true;
                }
                else throw NoTimelineForDeleteException(content);
            }
        }

        //EditTimelines
        bool checkFreeTimelineName(std::string newName){
            for(auto iter = this->getTimelines()->begin(); iter != this->getTimelines()->end(); ++iter){
                if(iter->getName() == newName){
                    return false; //  iter
                }
            }
           return true;
        }

        Timeline<T> *findTimeline(std::string name){ //iterator
           int i = 0;
           for(auto iter = this->getTimelines()->begin(); iter != this->getTimelines()->end(); ++iter, i++){
               if(iter->getName() == name){
                   return &this->timelines->at(i); //  iter
               }
           }
           throw TimelineNameNotFoundException(name);
           return nullptr;
       }

        int findTimelineIndex(std::string name){
           int i = 0;
           for(auto iter = this->getTimelines()->begin(); iter != this->getTimelines()->end(); ++iter, i++){
               if(iter->getName() == name){
                   return i; //  iter
               }
           }
           return -1;
       }

        void editTimelineName(std::string oldName, std::string newName){
            Timeline<T> *timelineToChange = this->findTimeline(oldName);
            if(checkFreeTimelineName(newName)){
                timelineToChange->changeNameOfTimeline(newName);
            }
            else throw TheSameTimelineNameException(newName);
        }

        //Проверка на существование Timeline-а с днем из календаря
        Timeline<T> *checkExisting(QDateTime checkTimeStart){
            int i = 0;
            for(auto iter = this->timelines->begin(); iter!= this->timelines->end(); ++iter, i++){
                if(iter->getStartDate() <= checkTimeStart && checkTimeStart <= iter->getEndDate()){
                    return &this->timelines->at(i);
                }
            }
            return nullptr; //Возврат пустого указателя, если нет такого таймлайна
        }


        bool addItemNew(QDateTime newStart, QDateTime newEnd, T newContent){ // с проверкой на наличие соответствующего timeline-а
            if(GanttChart<T>::Invariant::isSorted(this)){
                Timeline<T> *timelineForAddingItem = checkExisting(newStart);
                if(timelineForAddingItem == nullptr){
                    //Добавление нового таймлайна автоматически
                    QDateTime startOfWeek = QDateTime(QDate(newStart.date().addDays(-newStart.date().dayOfWeek()+1)));
                    QDateTime endOfWeek = QDateTime(QDate(startOfWeek.date().addDays(6)), QTime(23,59));
                    std::string nameOfTimeline = "Week_" + QString::number(startOfWeek.date().weekNumber()).toStdString() + "_" +  QString::number(startOfWeek.date().year()).toStdString();
                    Timeline<T> *newTimeline = new Timeline<T>(nameOfTimeline, startOfWeek, endOfWeek);
                    this->addTimeline(newTimeline);
                    //Добавление нового итема в таймлайн
                    timelineForAddingItem = checkExisting(newStart);
                    timelineForAddingItem->addItem(new TimelineItem<T>(newStart, newEnd, newContent));
                }
                else timelineForAddingItem->addItem(new TimelineItem<T>(newStart, newEnd, newContent));
            }
        }

        //Удаление Работает хреново
    //    bool deleteAllTimelines(){
    //        if(!this->timelines->empty()){
    //            int i = 0;
    //            for(auto iter = this->timelines->begin(); iter != this->timelines->end(); ++iter, i++){
    //                this->deleteTimeline(&this->timelines->at(i));
    //            }
    //            this->timelines->clear();
    //            return true;
    //        }
    //        return false;

    //    }



        bool deleteTimeline(Timeline<T> *curTimeline){
            if(curTimeline != nullptr){
                for(auto iter = this->timelines->begin(); iter != this->timelines->end(); ++iter){
                    if(curTimeline->getName() == iter->getName()){
                        this->timelines->erase(iter);
                        return true;
                    }
                }
            }
            else throw NotExistingTimelineException();
        }


        bool deleteTimelineByName(std::string name){
    //        if(curTimeline != nullptr){
    //        if(this->findTimeline())
            Timeline<T> *timelineToDelete = this->findTimeline(name);
            if(timelineToDelete->deleteAllItems()){
                for(auto iter = this->timelines->begin(); iter!=this->timelines->end(); ++iter){
                    if(timelineToDelete->getName() == iter->getName()){
                        this->timelines->erase(iter);
                        return true;
                    }
                }
            }
    //        }
    //        else throw NotExistingTimelineException();
        }

        bool deleteAll(){
            this->timelines->clear();
            return true;
        }


    };

}

#endif // GANTTCHART_H
