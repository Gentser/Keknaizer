#ifndef MANIPULATOR_H
#define MANIPULATOR_H
#include <QString>
#include <QJsonObject>


class Manipulator
{
private:
    QString pathToFile;

public:
    Manipulator();

    QJsonObject read();
    void write(QJsonObject obj);
};

#endif // MANIPULATOR_H
