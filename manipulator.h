<<<<<<< HEAD
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
=======
#ifndef MANIPULATOR_H
#define MANIPULATOR_H


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
>>>>>>> 70376e58ffc9b3f7820f5e9b2bcc0cad92d33f44
