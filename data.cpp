#include "data.h"

Point::Point(double _field, double _intensity)
{
    field = _field;
    intensity = _intensity;
}

Data::Data()
{

}

Data::Data(QStringList & list)
{
    QStringList valueStr;
    for(int i = 0; i < list.size(); ++i)
    {
        valueStr = list[i].split(' ');
        for(int j = 0; j < valueStr.size();)
        {
            if(valueStr[j].toDouble())
            {
                ++j;
            }
            else
            {
                valueStr.removeAt(j);
            }
        }
        dataVect << Point(valueStr[1].toDouble(), valueStr[0].toDouble());
    }
}

QTextStream &operator<<(QTextStream & out, const Data & obj)
{
    QVector<Point> dataLocal = obj.getDataVect();
    for(int i = 0; i < dataLocal.size(); ++i)
    {
        out << dataLocal[i].field << '\t' << dataLocal[i].intensity << '\n';
    }
    return out;
}

QTextStream &operator>>(QTextStream & in, Data & obj)
{
    QVector<Point> dataLocal = obj.getDataVect();

    QStringList lines = in.readAll().split('\n');
    QStringList value;

    for(int i = 0; i < lines.size(); ++i)
    {
        value = lines[i].split('\t');
        dataLocal << Point(value[1].toDouble(), value[0].toDouble());
    }
    return in;
}

QVector<Point> Data::getDataVect() const
{
    return dataVect;
}

void Data::setDataVect(QVector<Point> & tempVect)
{
    dataVect = std::move(tempVect);
}

void Data::integrate()
{
    dataVect[0].firstIntegral = 0;
    dataVect[0].secondIntegral = 0;
    double deltaField = 0, deltaIntegral = 0;
    for(int i = 1; i < dataVect.size(); ++i)
    {
        deltaField = dataVect[i].field - dataVect[0].field;
        dataVect[i].firstIntegral = dataVect[i - 1].firstIntegral + dataVect[i].intensity * deltaField;
        deltaIntegral = dataVect[i].firstIntegral - dataVect[0].firstIntegral;
        dataVect[i].secondIntegral = dataVect[i - 1].firstIntegral + dataVect[i].intensity * deltaIntegral;
    }
}

int Data::findEdgeIndex(double edge)
{
    int leftIndex = 0, rightIndex = dataVect.size() - 1;

    int middleIndex;

    while (rightIndex > leftIndex)
    {
        middleIndex = (leftIndex + rightIndex) / 2;

        if (dataVect[middleIndex].field < edge)
        {
            leftIndex = middleIndex + 1;
        }
        else if (dataVect[middleIndex].field > edge)
        {
            rightIndex = middleIndex - 1;
        }
        else
        {
            return middleIndex;
        }
    }

    return leftIndex;

    //    return std::find_if(dataVect.begin(), dataVect.end(), [leftEdge](Point dataObj){return dataObj.field > leftEdge;}) - dataVect.begin();
}
