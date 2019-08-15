#ifndef DATA_H
#define DATA_H

#include "settings.h"

#include <QTextStream>
#include <QVector>

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
    int findEdgeIndex(double);
};

QTextStream & operator<<(QTextStream &, const Data &);
QTextStream & operator>>(QTextStream &, Data &);

#endif // DATA_H
