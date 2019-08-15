#include "settings.h"

bool Settings::convert = 0;
bool Settings::getMatrix = 0;
bool Settings::integrateFirst = 0;
bool Settings::integrateSecond = 0;
double Settings::leftEdge = 0;
double Settings::rightEdge = 0;

bool Settings::getConvert()
{
    return convert;
}

bool Settings::getIntegrateFirst()
{
    return integrateFirst;
}

bool Settings::getIntegrateSecond()
{
    return integrateSecond;
}

bool Settings::getGetMatrix()
{
    return getMatrix;
}

double Settings::getLeftEdge()
{
    return leftEdge;
}

double Settings::getRightEdge()
{
    return rightEdge;
}

void Settings::loadSettings(const QStringList & list)
{
    convert = list[0].toInt();
    getMatrix = list[1].toInt();
    integrateFirst = list[2].toInt();
    integrateSecond = list[3].toInt();
    leftEdge = list[4].toDouble();
    rightEdge = list[5].toDouble();
}
