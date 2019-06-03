#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "manipulator.h"
#include <cmath>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <singletone.h>
#include "ganttchart.h"

template <class T>
class Serializer : public Singleton<Serializer<T>>
{
private:
    Serializer();
    Manipulator* manipulator;

public:
    void exportToJson(T* gant);
    void importFromJson(T* gant);
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer &) = delete;
    Serializer(Serializer &&) = delete;
    Serializer & operator=(Serializer &&) = delete;

    static Serializer& instance(){
        static Serializer test;
        return test;
    }
};


template <class T>
Serializer<T>::Serializer(){
    manipulator = new Manipulator();
}

template <class T>
void Serializer<T>::exportToJson(T* gant){
    QJsonObject json;
    QJsonArray jTimelines;
    for(auto iter = gant->getTimelines()->begin();iter!=gant->getTimelines()->end(); ++iter)
    {
        QJsonArray jIntervals;
        QJsonObject obj;
        obj["name"] = QString::fromStdString(iter->getName());
        obj["dateToStart"] = iter->getStartDate().toString("ddd MMMM  d  hh:mm:ss yyyy");
        obj["dateToEnd"] = iter->getEndDate().toString("ddd MMMM  d  hh:mm:ss yyyy");

        for(auto iterInterv = iter->getIntervals()->begin(); iterInterv!=iter->getIntervals()->end(); ++iterInterv)
        {
                QJsonObject item;
                item["end"] = iterInterv->getEnd().toString("ddd MMMM  d  hh:mm:ss yyyy");
                item["Content"] = QString::fromStdString(iterInterv->getContent());
                item["start"] = iterInterv->getStart().toString("ddd MMMM  d  hh:mm:ss yyyy");
                jIntervals.push_back(item);
        }
        obj["Intervals"] = jIntervals;
        jTimelines.push_back(obj);
    }
    json["Timelines"] = jTimelines;
    json["minDate"] = gant->getMinDate().toString("ddd MMMM  d  hh:mm:ss yyyy");
    json["maxDate"] = gant->getMaxDate().toString("ddd MMMM  d  hh:mm:ss yyyy");

    manipulator->write(json);
}

template <class T>
void Serializer<T>::importFromJson(T* gant){
    QJsonObject json = manipulator->read();

    QJsonArray jTimelines = json["Timelines"].toArray();
    QJsonArray jIntervals;

//    for(auto iter = jTimelines.begin();iter!=jTimelines.end(); ++iter)
//    {
//        QJsonObject obj = iter->toObject();

//        Timeline<std::string> *firstTimeline = new Timeline<std::string>("First_long_Timeline");

//        gant->addTimeline(new TimeLine<std::string>(obj["name"].toString().toStdString()));

//       // gant->addTimeline(new TimeLine<std::string>(obj["id"].toInt(),obj["name"].toString().toStdString(),obj["pos_x"].toDouble(),obj["pos_y"].toDouble()));
//        jIntervals = obj["Intervals"].toArray();
//        for(auto iter = jIntervals.begin();iter!=jIntervals.end(); ++iter)
//        {
//            QJsonObject objInt = iter->toObject();
//            try {
//                gant->add_edge(obj["id"].toInt(),new Edge(objEdges["id"].toInt(),objEdges["to_id"].toInt(),objEdges["fly_time"].toInt()));
//                item["end"] = iterInterv->getEnd().toString("ddd MMMM  d  hh:mm:ss yyyy");
//                item["Content"] = QString::fromStdString(iterInterv->getContent());
//                item["start"] = iterInterv->getStart().toString("ddd MMMM  d  hh:mm:ss yyyy");
//            } catch (EdgeLoopException e) {
//                std::cerr<<"loop exception"<<std::endl;
//            }

//        }
//    }

//    QJsonArray jVertices = json["vertices"].toArray();
//    QJsonArray jEdges;
//    for(auto iter = jVertices.begin();iter!=jVertices.end(); ++iter)
//    {
//        QJsonObject obj = iter->toObject();
//        graph->add_vertex(new Vertex<Edge>(obj["id"].toInt(),obj["name"].toString().toStdString(),obj["pos_x"].toDouble(),obj["pos_y"].toDouble()));
//        jEdges = obj["edges"].toArray();
//        for(auto iter = jEdges.begin();iter!=jEdges.end(); ++iter)
//        {
//            QJsonObject objEdges = iter->toObject();
//            try {
//                graph->add_edge(obj["id"].toInt(),new Edge(objEdges["id"].toInt(),objEdges["to_id"].toInt(),objEdges["fly_time"].toInt()));
//            } catch (EdgeLoopException e) {
//                std::cerr<<"loop exception"<<std::endl;
//            }

//        }
//    }
}

#endif // SERIALIZER_H
