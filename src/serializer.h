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
        obj["dateToStart"] = iter->getStartDate().toString("dd.MM.yyyy hh:mm:ss");
        obj["dateToEnd"] = iter->getEndDate().toString("dd.MM.yyyy hh:mm:ss");

        for(auto iterInterv = iter->getIntervals()->begin(); iterInterv!=iter->getIntervals()->end(); ++iterInterv)
        {
                QJsonObject item;
                item["end"] = iterInterv->getEnd().toString("dd.MM.yyyy hh:mm:ss");
                item["Content"] = QString::fromStdString(iterInterv->getContent());
                item["start"] = iterInterv->getStart().toString("dd.MM.yyyy hh:mm:ss");
                jIntervals.push_back(item);
        }
        obj["Intervals"] = jIntervals;
        jTimelines.push_back(obj);
    }
    json["Timelines"] = jTimelines;
    json["minDate"] = gant->getMinDate().toString("dd.MM.yyyy hh:mm:ss");
    json["maxDate"] = gant->getMaxDate().toString("dd.MM.yyyy hh:mm:ss");

    manipulator->write(json);
}

template <class T>
void Serializer<T>::importFromJson(T* gant){
    QJsonObject json = manipulator->read();

    QJsonArray jTimelines = json["Timelines"].toArray();
    QJsonArray jIntervals;

    for(auto iter = jTimelines.begin();iter!=jTimelines.end(); ++iter)
    {
        QJsonObject obj = iter->toObject();

        //Timeline<std::string> *firstTimeline = new Timeline<std::string>("First_long_Timeline");

//         qDebug() << "test  " << obj["dateToStart"];
//          qDebug() << "test  " << obj["dateToStart"].toString();
//           qDebug() << "test  " << (QDateTime::fromString(obj["dateToStart"].toString(),"dd.MM.yyyy hh:mm:ss")).toString("dd.MM.yyyy hh:mm:ss");
//        qDebug() << "test  " << (QDateTime::fromString(obj["dateToStart"].toString(),"yyyy hh:mm:ss")).toString();


//        QString date_string_on_db = obj["dateToEnd"].toString();
//        QString dat22 = "2019-12-10 00:00:00";
//        QDateTime Date0 = QDateTime::fromString(dat22,"yyyy-MM-dd hh:mm:ss");

//         QDateTime date1 = QDateTime::fromString(obj["dateToEnd"].toString(),"dd.MM.yyyy hh:mm:ss");
//         date1 = date1;
//         //QLocale locale(QLocale::English, QLocale::UnitedStates);
//         //QDateTime dt = QLocale::toDateTime(obj["dateToEnd"].toString(), "dd.MM.yyyy hh:mm:ss");

        Timeline<std::string> *newTimeline = new Timeline<std::string>(obj["name"].toString().toStdString(),QDateTime::fromString(obj["dateToStart"].toString(),"dd.MM.yyyy hh:mm:ss"),
                QDateTime::fromString(obj["dateToEnd"].toString("dd.MM.yyyy hh:mm:ss"),"dd.MM.yyyy hh:mm:ss"));

        jIntervals = obj["Intervals"].toArray();
        for(auto iterItem = jIntervals.begin();iterItem!=jIntervals.end(); ++iterItem)
        {
            QJsonObject objInt = iterItem->toObject();

                newTimeline->addItem(new TimelineItem<std::string>(QDateTime::fromString(objInt["start"].toString(),"dd.MM.yyyy hh:mm:ss"),
                                                                  QDateTime::fromString(objInt["end"].toString(),"dd.MM.yyyy hh:mm:ss"),
                                                                  std::string(objInt["Content"].toString().toStdString())));
        }
        gant->addTimeline(newTimeline);
    }

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
