#include "settings.h"

bool Settings::getConvert() const
{
    return convert;
}

bool Settings::getIntegrateFirst() const
{
    return integrateFirst;
}

bool Settings::getIntegrateSecond() const
{
    return integrateSecond;
}

bool Settings::getGetMatrix() const
{
    return getMatrix;
}

double Settings::getLeftEdge() const
{
    return leftEdge;
}

double Settings::getRightEdge() const
{
    return rightEdge;
}

Settings::Settings()
{

}

Settings::Settings(const QStringList & list)
{
    convert = list[0].toInt();
    getMatrix = list[1].toInt();
    integrateFirst = list[2].toInt();
    integrateSecond = list[3].toInt();
    leftEdge = list[4].toDouble();
    rightEdge = list[5].toDouble();
}
