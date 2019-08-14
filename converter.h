#ifndef CONVERTER_H
#define CONVERTER_H

#include <QList>
#include <QDir>
#include <QTime>
#include <iostream>
#include "data.h"

class Converter
{
private:
    QList <Data> dataList;
    QTime * timer;
public:
    Converter(QTime *);
    void integrateAllData(const QStringList &);
    QList<Data> & getDataList();
    QString createFirstIntMatrixRaw(int);
    QString createSecIntMatrixRaw(int);
    QString createMatrixRaw(int);
    int getDataVectSize();
};

#endif // CONVERTER_H
