#include "converter.h"
#include "file.h"
#include "settings.h"
#include "message.h"
#include "binextractor.h"

int main()
{
    QTime timer;

    File fileWork;
    Converter conv;

    Settings::loadSettings(fileWork.loadSettings());

    Message::setTimer(&timer);

    timer.start();

    std::cout << "Starting software..." << std::endl;

    if(Settings::getFileType() == FileType::BIN)
    {
        fileWork.readAllBinFiles(conv.getDataList());
    }
    else if (Settings::getFileType() == FileType::TXT)
    {
        fileWork.readAllFiles(conv.getDataList());
    }
    else
    {
        std::cout << "Unable to define type of file. Exit" << std::endl;
        return 1;
    }

    fileWork.loadPotList();

    if(Settings::getConvert())
    {
        fileWork.writeAllFiles(conv.getDataList());
    }
    if(Settings::getGetMatrix())
    {
        fileWork.writeTotalMatrix(conv);
    }
    if(Settings::getIntegrateFirst() || Settings::getIntegrateSecond())
    {
        conv.integrateAllData(fileWork.getSrcFiles());
        if(Settings::getIntegrateFirst())
        {
            fileWork.writeFirstIntegrationMatrix(conv, Settings::getLeftEdge(), Settings::getRightEdge());
        }
        if (Settings::getIntegrateSecond())
        {
            fileWork.writeSecondIntegrationMatrix(conv, Settings::getLeftEdge(), Settings::getRightEdge());
        }
    }

    std::cout << "Finished" << std::endl;
    std::cout << "This software was created by Evgeny Bondarenko (Minsk, 2019)" << std::endl;

    system("pause");

    return 0;
}
