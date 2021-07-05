#include "file.h"


File::File()
{

}

QStringList & File::loadSettings()
{
    QString srcFile = QString("%1/%2").arg(QDir::currentPath()).arg("Settings.txt");
    QFile file(srcFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        exit(1);
    }
    QTextStream inputStream(&file);
    QString text = inputStream.readAll();
    dataString = text.split('\n');
    QRegExp expr("[a-zA-Z:space:]");
    for(int i = 0; i < dataString.size(); ++i)
    {
        dataString[i].remove(expr);
    }
    return dataString;
}

void File::loadPotList()
{
    QString srcFile = QString("%1/%2").arg(QDir::currentPath()).arg("Potentials.txt");
    QFile file(srcFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream inputStream(&file);
    QString text = inputStream.readAll();
    potList = text.split('\n');
}

void File::readAllFiles(QList<Data> & dataList)
{
    dataString.clear();
    foreach(const QString el, srcFiles)
    {
        QString srcFile = QString("%1/%2/%3").arg(QDir::currentPath()).arg("Src").arg(el);
        QFile file(srcFile);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }
        purifyFile(file);

        Data obj(dataString);
        dataList.append(obj);

        Message::writeReadFileName(el);
        dataString.clear();
    }
}

void File::readAllBinFiles(QList<Data> & dataList)
{
    foreach(const QString el, srcFiles)
    {
        QString srcFile = QString("%1/%2/%3").arg(QDir::currentPath()).arg("Src").arg(el);
        std::shared_ptr<BinExtractor> binExtr = BinExtractor::createInstBinExtr();
        Data obj;
        binExtr->readBinFile(srcFile);
        binExtr->parceBinData(obj);
        dataList.append(obj);
        Message::writeReadFileName(el);
    }
}

void File::writeAllFiles(QList<Data> & dataList)
{

    if(dataList.size() == potList.size())
    {
        for(int i = 0; i < srcFiles.count(); ++i)
        {
            QString finFile = QString("%1/%2/%3").arg(QDir::currentPath()).arg("Fin").arg(srcFiles[i]);
            finFile.truncate(finFile.lastIndexOf('.'));         //Remove extension
            QFile file(finFile);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                return;
            }
            QTextStream out(&file);
            out << QString("%1\n%2\n").arg(srcFiles[i]).arg(potList[i]);
            out << dataList[i];
            Message::writeFinishedFileName(srcFiles[i]);
            file.close();
        }
    }
    else
    {
        for(int i = 0; i < srcFiles.count(); ++i)
        {
            QString finFile = QString("%1/%2/%3").arg(QDir::currentPath()).arg("Fin").arg(srcFiles[i]);
            QFile file(finFile);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                return;
            }
            QTextStream out(&file);
            out << QString("%1\n").arg(srcFiles[i]);
            out << dataList[i];
            Message::writeFinishedFileName(srcFiles[i]);
            file.close();
        }
    }
}

QString File::genFileNameLine()
{
    QString line = srcFiles[0];
    for(int i = 1; i < srcFiles.size(); ++i)
    {
        line += ' ';
        line += srcFiles[i];
    }
    line += '\n';
    return line;
}

QString File::genPotLine(int dataListSize)
{
    QString line;
    if(dataListSize == potList.size())
    {
        line = potList[0];
        for(int i = 1; i < potList.size(); ++i)
        {
            line += ' ';
            line += potList[i];
        }
        line += '\n';
    }
    return line;
}

void File::writeFirstIntegrationMatrix(Converter & conv, double leftEdge = 0, double rightEdge = 0)
{
    QString finFile = QString("%1/%2/FirstIntegrMatrix.txt").arg(QDir::currentPath()).arg("Fin");
    QFile file(finFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);

    out << genFileNameLine();

    out << genPotLine(conv.getDataList().size());

    int leftIndex = 1, rightIndex = conv.getDataVectSize();

    if(leftEdge && rightEdge)
    {
        leftIndex = conv.getDataList()[0].findEdgeIndex(leftEdge);
        rightIndex = conv.getDataList()[0].findEdgeIndex(rightEdge) - 1;
    }

    for(int i = leftIndex; i < rightIndex; ++i)
    {
        out << QString("%1\n").arg(conv.createFirstIntMatrixRaw(i));
    }
    Message::writeFirstIntMatrixIsReady();
    file.close();
}

void File::writeSecondIntegrationMatrix(Converter & conv, double leftEdge = 0, double rightEdge = 0)
{
    QString finFile = QString("%1/%2/SecondIntegrMatrix.txt").arg(QDir::currentPath()).arg("Fin");
    QFile file(finFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);

    out << genFileNameLine();

    out << genPotLine(conv.getDataList().size());

    int leftIndex = 1, rightIndex = conv.getDataVectSize();

    if(leftEdge && rightEdge)
    {
        leftIndex = conv.getDataList()[0].findEdgeIndex(leftEdge);
        rightIndex = conv.getDataList()[0].findEdgeIndex(rightEdge) - 1;
    }

    for(int i = leftIndex; i < rightIndex; ++i)
    {
        out << QString("%1\n").arg(conv.createSecIntMatrixRaw(i));;
    }
    Message::writeSecIntMatrixIsReady();
    file.close();
}

void File::writeTotalMatrix(Converter & conv)
{
    QString finFile = QString("%1/%2/TotalMatrix.txt").arg(QDir::currentPath()).arg("Fin");
    QFile file(finFile);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream out(&file);

    out << genFileNameLine();

    out << genPotLine(conv.getDataList().size());

    out << QString("%1\n").arg(conv.createMatrixRaw(0));

    int size = conv.getDataVectSize();

    for(int i = 1; i < size; ++i)
    {
        out << QString("%1\n").arg(conv.createMatrixRaw(i));
    }
    Message::writeMatrixIsReady();
    file.close();
}

void File::getFileNameInSrcDir()
{
    QDir fileInputPath = QDir(QString("%1/%2").arg(QDir::currentPath()).arg("Src"));
    QStringList nameFilter;
    if(Settings::getFileType() == FileType::BIN)
    {
        nameFilter.append("*.bin");
    }
    else if (Settings::getFileType() == FileType::TXT)
    {
        nameFilter.append("*.txt");
    }
    srcFiles = fileInputPath.entryList(nameFilter);
}

const QStringList & File::getSrcFiles()
{
    return srcFiles;
}

void File::purifyFile(QFile & file)
{
   QTextStream inputStream(&file);
   QStringList lines;
   QString line = inputStream.readLine();
   while(!line.contains("mT"))
   {
       line = inputStream.readLine();
   }
   line = inputStream.readLine();
   while(!line.contains("="))
   {
       dataString.append(line);
       line = inputStream.readLine();
   }
}

//void File::writeFinishedFileName(const QString & inStr)
//{
//    QString outStr = QString("File %1 ready. %2 msec").arg(inStr).arg(timer->elapsed());
//    std::cout << outStr.toStdString() << std::endl;
//}

//void File::writeReadFileName(const QString & inStr)
//{
//    QString outStr = QString("File %1 loaded. %2 msec").arg(inStr).arg(timer->elapsed());
//    std::cout << outStr.toStdString() << std::endl;
//}

//void File::writeMatrixIsReady()
//{
//    QString outStr = QString("Total matrix is ready. %1 msec").arg(timer->elapsed());
//    std::cout << outStr.toStdString() << std::endl;
//}

//void File::writeFirstIntMatrixIsReady()
//{
//    QString outStr = QString("First integration data matrix is ready. %1 msec").arg(timer->elapsed());
//    std::cout << outStr.toStdString() << std::endl;
//}

//void File::writeSecIntMatrixIsReady()
//{
//    QString outStr = QString("Second integration data matrix is ready. %1 msec").arg(timer->elapsed());
//    std::cout << outStr.toStdString() << std::endl;
//}

//void File::writeSettingsLoaded()
//{
//    QString outStr = QString("Settings form %1 loaded. %2 msec").arg("Settings.txt").arg(timer->elapsed());
//    std::cout << outStr.toStdString() << std::endl;
//}
