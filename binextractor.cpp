#include "binextractor.h"

#include <iostream>

std::weak_ptr<BinExtractor> BinExtractor::weakPtr;

void BinExtractor::calcIncrCoeff()
{
    X_slope = deltaLast_X / X_POINTS_COUNT_TXT;
}

void BinExtractor::parceParams()
{
    BytesToFloat conv;
    memcpy(conv.bytes, binArr.constData() + 112, 4);            //70 in hex
    first_X_Value = conv.floatVal;
    memcpy(conv.bytes, binArr.constData() + 116, 4);            //74 in hex
    deltaLast_X = conv.floatVal;
}

void BinExtractor::parceSpectrum()
{
    BytesToFloat conv;

    int endIndex = SPECTRA_Y_START_BYTES_POS + (binArr.size() - SPECTRA_Y_START_BYTES_POS) / 2 - BYTES_Y_FLOATING;
    float sum = 0;
    for (int i = SPECTRA_Y_START_BYTES_POS, j = 1, k = 0; i < endIndex; i += BYTES_Y_FLOATING, ++j)
    {
        memcpy(conv.bytes, binArr.constData() + i, BYTES_Y_FLOATING);
        sum += conv.floatVal;
        if(!(j % 8))                                                        //Average data by 8 points
        {
            sum /= 8;
            dataVect << Point(first_X_Value + k * X_slope, sum);
            ++k;
            sum = 0.0;
        }
    }
}

std::shared_ptr<BinExtractor> BinExtractor::createInstBinExtr()             //Implementation of Singleton
{
    auto shrdPtr = weakPtr.lock();
    if(!shrdPtr)
    {
        shrdPtr = std::make_shared<BinExtractor>(BinExtractor());
        weakPtr = shrdPtr;
    }
    return shrdPtr;
}

BinExtractor::BinExtractor()
{
//    std::cout << "Created" << std::endl;
}

BinExtractor::~BinExtractor()
{
//    std::cout << "Destroyed" << std::endl;
}

void BinExtractor::readBinFile(const QString & fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        return;
    }
    binArr = std::move(file.readAll());
}

void BinExtractor::parceBinData(Data & data)
{
    parceParams();
    calcIncrCoeff();
    parceSpectrum();
    data.setDataVect(dataVect);
}
