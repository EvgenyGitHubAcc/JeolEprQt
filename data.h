#ifndef DATA_H
#define DATA_H

#include "settings.h"

#include <QPointF>
#include <QTextStream>
#include <QVector>
#include <QByteArray>
#include <QList>

struct Point
{
    double field;
    double intensity;
    double firstIntegral;
    double secondIntegral;

    Point() = default;
    Point(double _field, double _intensity);
};

class Data
{
private:
    QVector<Point> dataVect;
public:
    Data();
    Data(QStringList &);
    QVector<Point> getDataVect() const;
    void integrate();
    int findLeftEdgeIndex(double);
    int findRightEdgeIndex(double);
};

QTextStream & operator<<(QTextStream &, const Data &);
QTextStream & operator>>(QTextStream &, Data &);

#endif // DATA_H
