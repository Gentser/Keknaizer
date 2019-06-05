#ifndef GANTTCHART_H
#define GANTTCHART_H
#include <QDateTime>
#include "timeline.h"
#include "iterator.h"

template <class T>
class GanttChart
{
private:
    QDateTime minDate;
    QDateTime maxDate;
    std::vector<Timeline<T>> *timelines; // <TimelineItem<T>>

public:
    GanttChart(){
        this->setMinDate(QDateTime(QDate(2000,1,1), QTime(0,0)));
        this->setMaxDate(QDateTime(QDate(2020,1,1), QTime(0,0)));

        this->timelines = new std::vector<Timeline<T>>;
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
    std::vector<Timeline<T>> *getTimelines() const //<TimelineItem<T>>
    {
        return timelines;
    }
    void setTimelines(const std::vector<Timeline<T>> &value) // <TimelineItem<T>>
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


    //New for GITHUB

    //EditItems
    bool editTimelineItem(std::string nameOfTimeline, T oldContent, T newContent, QDateTime newStart, QDateTime newEnd){
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

    bool addTimelineItem(std::string nameOfTimeline,  QDateTime newStart, QDateTime newEnd, T newContent){
        Timeline<T> *timelineToChange = this->findTimeline(nameOfTimeline);
        timelineToChange->addItem(new TimelineItem<T>(newStart, newEnd, newContent));

    }

    bool deleteItem(std::string nameOfTimeline,  T content){
        Timeline<T> *timelineToChange = this->findTimeline(nameOfTimeline);
        timelineToChange->deleteItemByName(content);
        return true;
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

    void editTimelineName(std::string oldName, std::string newName){
        Timeline<T> *timelineToChange = this->findTimeline(oldName);
        if(checkFreeTimelineName(newName)){
            timelineToChange->changeNameOfTimeline(newName);
        }
        else throw TheSameTimelineNameException(newName);
    }

    //Нужные ли эти методы (если будем делать Timeline-ы как недели)
//    editTimelineStartTime(){

//    }

//    editTimelineEndTime(){

//    }

//    editTimelineAllTime(){

//    }



};

#endif // GANTTCHART_H
