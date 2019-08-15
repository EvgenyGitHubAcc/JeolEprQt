#include "converter.h"
#include "file.h"
#include "settings.h"

int main()
{
    QTime timer;

    File fileWork(&timer);
    Converter conv(&timer);
    Settings sett(fileWork.loadSettings());

    timer.start();

    std::cout << "Starting software..." << std::endl;

    fileWork.readAllFiles(conv.getDataList());
    fileWork.loadPotList();

    if(sett.getConvert())
    {
        fileWork.writeAllFiles(conv.getDataList());
    }
    if(sett.getGetMatrix())
    {
        fileWork.writeTotalMatrix(conv);
    }
    if(sett.getIntegrateFirst() || sett.getIntegrateSecond())
    {
        conv.integrateAllData(fileWork.getSrcFiles());
        if(sett.getIntegrateFirst())
        {
            fileWork.writeFirstIntegrationMatrix(conv, sett.getLeftEdge(), sett.getRightEdge());
        }
        if (sett.getIntegrateSecond())
        {
            fileWork.writeSecondIntegrationMatrix(conv, sett.getLeftEdge(), sett.getRightEdge());
        }
    }

    std::cout << "Finished" << std::endl;
    std::cout << "This software was created by Evgeny Bondarenko (Minsk, 2019)" << std::endl;

    system("pause");

    return 0;
}
