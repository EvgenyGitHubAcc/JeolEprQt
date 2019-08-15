#ifndef CONVERTER_H
#define CONVERTER_H

#include <QList>
#include <QDir>
#include <QTime>
#include <iostream>
#include "data.h"
#include "message.h"

class Converter
{
private:
    QList <Data> dataList;
public:
    Converter();
    void integrateAllData(const QStringList &);
    QList<Data> & getDataList();
    QString createFirstIntMatrixRaw(int);
    QString createSecIntMatrixRaw(int);
    QString createMatrixRaw(int);
    int getDataVectSize();
};

#endif // CONVERTER_H
