#include "settings.h"

FileType Settings::fileType = TXT;
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

FileType Settings::getFileType()
{
    return fileType;
}

void Settings::loadSettings(const QStringList & list)
{
    if(list[0].toInt())
    {
        fileType = BIN;
    }
    else
    {
        fileType = TXT;
    }
    convert = list[1].toInt();
    getMatrix = list[2].toInt();
    integrateFirst = list[3].toInt();
    integrateSecond = list[4].toInt();
    leftEdge = list[5].toDouble();
    rightEdge = list[6].toDouble();
}
