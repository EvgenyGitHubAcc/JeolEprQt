#ifndef BINEXTRACTOR_H
#define BINEXTRACTOR_H

#include <QFile>
#include <QByteArray>
#include <QTextStream>
#include "data.h"
#include <memory>
#include <stdio.h>

const int X_POINTS_COUNT_TXT = 8192;                        //Count of points from txt file
const int SPECTRA_Y_START_BYTES_POS = 9500;                 //251C from hex editor
const unsigned char BYTES_Y_FLOATING = 4;                   //Count of bytes for floating y value (4 byte float)

class BinExtractor
{
private:
    static std::weak_ptr<BinExtractor> weakPtr;
    QByteArray binArr;
    float first_X_Value = 0.0;
    float deltaLast_X = 0.0;
    float X_slope = 0.0;

    QVector<Point> dataVect;

    union BytesToFloat
    {
        unsigned char bytes[4] = {0};
        float floatVal;
    };

    void calcIncrCoeff();
    void parceParams();
    void parceSpectrum();
    BinExtractor();
public:
    static std::shared_ptr<BinExtractor> createInstBinExtr();
    void readBinFile(const QString &);
    void parceBinData(Data &);
    ~BinExtractor();
};
#endif // BINEXTRACTOR_H
