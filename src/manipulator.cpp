#include "manipulator.h"

#include <QDebug>

#include <qfile.h>
#include <qjsondocument.h>
//#include <qjsonobject.h>

#include <exception>

Manipulator::Manipulator() {
    #if (defined (_WIN32) || defined (_WIN64))
        pathToFile = "new_gantt.json"; //resolve this
    #endif
}

QJsonObject Manipulator::read() {

    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly)) {
        throw std::exception(); // some file exception? pathToFile.toStdString()
    }
    QByteArray rawData = QByteArray::fromBase64(file.readAll());
//    QByteArray rawData = file.readAll();
    file.close();


    QJsonDocument doc(QJsonDocument::fromJson(rawData));
    QJsonObject root = doc.object();

   // root.keys().at(0);
    qDebug() << "O5 DEBAZHIM " <<root.keys().at(0);
    return doc.object();
}

void Manipulator::write(QJsonObject json) {
    QJsonDocument json_doc(json);
    QString json_string = json_doc.toJson();

    QFile save_file(pathToFile); //"new_" +
    if (save_file.exists())
        save_file.remove();
   // if (!save_file.open(QIODevice::WriteOnly)) {
     //   throw std::exception(); //some file exception ? pathToFile.toStdString()
    //}

    save_file.open(QIODevice::WriteOnly);
    save_file.write(json_string.toLocal8Bit().toBase64()); //.toBase64());
//    save_file.write(json_string.toLocal8Bit());
    save_file.close();
}
