#include "converter.h"

Converter::Converter()
{

}

QList<Data> & Converter::getDataList()
{
    return dataList;
}

QString Converter::createFirstIntMatrixRaw(int rowNumber)
{
    QString row = QString::number(dataList[0].getDataVect()[rowNumber].field, 'f', DOUBLE_PRECISION);
    foreach(Data el, dataList)
    {
        row += ' ';
        row += QString::number(el.getDataVect()[rowNumber].firstIntegral, 'f', DOUBLE_PRECISION);
    }
    return row;
}

QString Converter::createSecIntMatrixRaw(int rowNumber)
{
    QString row = QString::number(dataList[0].getDataVect()[rowNumber].field, 'f', DOUBLE_PRECISION);
    foreach(Data el, dataList)
    {
        row += ' ';
        row += QString::number(el.getDataVect()[rowNumber].secondIntegral, 'f', DOUBLE_PRECISION);
    }
    return row;
}

QString Converter::createMatrixRaw(int rowNumber)
{
    QString row = QString::number(dataList[0].getDataVect()[rowNumber].field, 'f', DOUBLE_PRECISION);
    foreach(Data el, dataList)
    {
        row += ' ';
        row += QString::number(el.getDataVect()[rowNumber].intensity, 'f', DOUBLE_PRECISION);
    }
    return row;
}

int Converter::getDataVectSize()
{
    return dataList[0].getDataVect().size();
}

void Converter::integrateAllData(const QStringList & srcFiles)
{
    for(int i = 0; i < dataList.size(); ++i)
    {
        dataList[i].integrateFirst();
        dataList[i].integrateSecond();
        Message::writeFileIntegrated(srcFiles[i]);
    }
}
