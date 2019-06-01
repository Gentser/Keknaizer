<<<<<<< HEAD
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

template <class T>
class Serializer : public Singleton<Serializer<T>>
{
private:
    Serializer();
    Manipulator* manipulator;

public:
    void exportToJson(T* graph);
    void importFromJson(T* graph);
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer &) = delete;
    Serializer(Serializer &&) = delete;
    Serializer & operator=(Serializer &&) = delete;

    static Serializer& instance(){
        static Serializer test;
        return test;
    }
};
}

template <class T>
Serializer<T>::Serializer(){
    manipulator = new Manipulator();
}

template <class T>
void Serializer<T>::exportToJson(T* graph){
    QJsonObject json;
    QJsonArray jVertices;
    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        QJsonArray jEdges;
        QJsonObject obj;
        obj["id"] = iter->get_id();
        obj["name"] = QString::fromStdString(iter->get_name());
        obj["pos_x"] = std::trunc(iter->get_pos_x() * 100) / 100;
        obj["pos_y"] = std::trunc(iter->get_pos_y() * 100) / 100;
        for(auto iterEdge = iter->get_edges()->begin();iterEdge!=iter->get_edges()->end(); ++iterEdge)
        {
            if(iter->get_id()!=iterEdge->get_to_id()){
                QJsonObject edge;
                edge["id"] = iterEdge->get_id();
                edge["to_id"] = iterEdge->get_to_id();
                edge["fly_time"] = iterEdge->get_fly_time();
                jEdges.push_back(edge);
            }
        }
        obj["edges"] = jEdges;
        jVertices.push_back(obj);
    }
    json["vertices"] = jVertices;

    manipulator->write(json);
}

template <class T>
void Serializer<T>::importFromJson(T* graph){
    QJsonObject json = manipulator->read();

    QJsonArray jVertices = json["vertices"].toArray();
    QJsonArray jEdges;
    for(auto iter = jVertices.begin();iter!=jVertices.end(); ++iter)
    {
        QJsonObject obj = iter->toObject();
        graph->add_vertex(new Vertex<Edge>(obj["id"].toInt(),obj["name"].toString().toStdString(),obj["pos_x"].toDouble(),obj["pos_y"].toDouble()));
        jEdges = obj["edges"].toArray();
        for(auto iter = jEdges.begin();iter!=jEdges.end(); ++iter)
        {
            QJsonObject objEdges = iter->toObject();
            try {
                graph->add_edge(obj["id"].toInt(),new Edge(objEdges["id"].toInt(),objEdges["to_id"].toInt(),objEdges["fly_time"].toInt()));
            } catch (EdgeLoopException e) {
                std::cerr<<"loop exception"<<std::endl;
            }

        }
    }
}

#endif // SERIALIZER_H
=======
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

template <class T>
class Serializer : public Singleton<Serializer<T>>
{
private:
    Serializer();
    Manipulator* manipulator;

public:
    void exportToJson(T* graph);
    void importFromJson(T* graph);
    Serializer(const Serializer&) = delete;
    Serializer& operator=(const Serializer &) = delete;
    Serializer(Serializer &&) = delete;
    Serializer & operator=(Serializer &&) = delete;

    static Serializer& instance(){
        static Serializer test;
        return test;
    }
};
}

template <class T>
Serializer<T>::Serializer(){
    manipulator = new Manipulator();
}

template <class T>
void Serializer<T>::exportToJson(T* graph){
    QJsonObject json;
    QJsonArray jVertices;
    for(auto iter = graph->getVertices()->begin();iter!=graph->getVertices()->end(); ++iter)
    {
        QJsonArray jEdges;
        QJsonObject obj;
        obj["id"] = iter->get_id();
        obj["name"] = QString::fromStdString(iter->get_name());
        obj["pos_x"] = std::trunc(iter->get_pos_x() * 100) / 100;
        obj["pos_y"] = std::trunc(iter->get_pos_y() * 100) / 100;
        for(auto iterEdge = iter->get_edges()->begin();iterEdge!=iter->get_edges()->end(); ++iterEdge)
        {
            if(iter->get_id()!=iterEdge->get_to_id()){
                QJsonObject edge;
                edge["id"] = iterEdge->get_id();
                edge["to_id"] = iterEdge->get_to_id();
                edge["fly_time"] = iterEdge->get_fly_time();
                jEdges.push_back(edge);
            }
        }
        obj["edges"] = jEdges;
        jVertices.push_back(obj);
    }
    json["vertices"] = jVertices;

    manipulator->write(json);
}

template <class T>
void Serializer<T>::importFromJson(T* graph){
    QJsonObject json = manipulator->read();

    QJsonArray jVertices = json["vertices"].toArray();
    QJsonArray jEdges;
    for(auto iter = jVertices.begin();iter!=jVertices.end(); ++iter)
    {
        QJsonObject obj = iter->toObject();
        graph->add_vertex(new Vertex<Edge>(obj["id"].toInt(),obj["name"].toString().toStdString(),obj["pos_x"].toDouble(),obj["pos_y"].toDouble()));
        jEdges = obj["edges"].toArray();
        for(auto iter = jEdges.begin();iter!=jEdges.end(); ++iter)
        {
            QJsonObject objEdges = iter->toObject();
            try {
                graph->add_edge(obj["id"].toInt(),new Edge(objEdges["id"].toInt(),objEdges["to_id"].toInt(),objEdges["fly_time"].toInt()));
            } catch (EdgeLoopException e) {
                std::cerr<<"loop exception"<<std::endl;
            }

        }
    }
}

#endif // SERIALIZER_H
>>>>>>> 70376e58ffc9b3f7820f5e9b2bcc0cad92d33f44
