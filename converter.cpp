#include "converter.h"

Converter::Converter(QTime * _timer)
{
    timer = _timer;
}

QList<Data> & Converter::getDataList()
{
    return dataList;
}

QString Converter::createFirstIntMatrixRaw(int rowNumber)
{
    QString row = QString::number(dataList[0].getDataVect()[rowNumber].field);
    foreach(Data el, dataList)
    {
        row += ' ';
        row += QString::number(el.getDataVect()[rowNumber].firstIntegral);
    }
    return row;
}

QString Converter::createSecIntMatrixRaw(int rowNumber)
{
    QString row = QString::number(dataList[0].getDataVect()[rowNumber].field);
    foreach(Data el, dataList)
    {
        row += ' ';
        row += QString::number(el.getDataVect()[rowNumber].secondIntegral);
    }
    return row;
}

QString Converter::createMatrixRaw(int rowNumber)
{
    QString row = QString::number(dataList[0].getDataVect()[rowNumber].field);
    foreach(Data el, dataList)
    {
        row += ' ';
        row += QString::number(el.getDataVect()[rowNumber].intensity);
    }
    return row;
}

int Converter::getDataVectSize()
{
    return dataList[0].getDataVect().size();
}

void Converter::integrateAllData(const QStringList & srcFiles)
{
    QString outStr;
    for(int i = 0; i < dataList.size(); ++i)
    {
        dataList[i].integrate();
        outStr = QString("File %1 integrated. %2 msec").arg(srcFiles[i]).arg(timer->elapsed());
        std::cout << outStr.toStdString() << std::endl;
    }
}
