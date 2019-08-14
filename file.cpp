
#include "file.h"

File::File(QTime * _timer)
{
    timer = _timer;
    QDir fileInputPath = QDir(QString("%1/%2").arg(QDir::currentPath()).arg("Src"));
    QStringList nameFilter("*.txt");
    srcFiles = fileInputPath.entryList(nameFilter);
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

        writeReadFileName(el);
        dataString.clear();
    }
}

void File::writeAllFiles(QList<Data> & dataList)
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
        out << dataList[i];
        writeFinishedFileName(srcFiles[i]);
        file.close();
    }
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

    QString line = srcFiles[0];
    for(int i = 1; i < srcFiles.size(); ++i)
    {
        line += ' ';
        line += srcFiles[i];
    }
    line += '\n';
    out << line;

    int leftIndex = 1, rightIndex = conv.getDataVectSize();

    if(leftEdge && rightEdge)
    {
        leftIndex = conv.getDataList()[0].findLeftEdgeIndex(leftEdge);
        rightIndex = conv.getDataList()[0].findRightEdgeIndex(rightEdge);
    }

    for(int i = leftIndex; i < rightIndex; ++i)
    {
        line = QString("%1\n").arg(conv.createFirstIntMatrixRaw(i));
        out << line;
    }
    writeFirstIntMatrixIsReady();
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

    QString line = srcFiles[0];
    for(int i = 1; i < srcFiles.size(); ++i)
    {
        line += ' ';
        line += srcFiles[i];
    }
    line += '\n';
    out << line;

    int leftIndex = 1, rightIndex = conv.getDataVectSize();

    if(leftEdge && rightEdge)
    {
        leftIndex = conv.getDataList()[0].findLeftEdgeIndex(leftEdge);
        rightIndex = conv.getDataList()[0].findRightEdgeIndex(rightEdge);
    }

    for(int i = leftIndex; i < rightIndex; ++i)
    {
        line = QString("%1\n").arg(conv.createSecIntMatrixRaw(i));
        out << line;
    }
    writeSecIntMatrixIsReady();
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

    QString line = srcFiles[0];
    for(int i = 1; i < srcFiles.size(); ++i)
    {
        line += ' ';
        line += srcFiles[i];
    }
    line += '\n';
    out << line;

    line = QString("%1\n").arg(conv.createMatrixRaw(0));
    out << line;

    int size = conv.getDataVectSize();

    for(int i = 1; i < size; ++i)
    {
        line = QString("%1\n").arg(conv.createMatrixRaw(i));
        out << line;
    }
    writeMatrixIsReady();
    file.close();
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

void File::writeFinishedFileName(const QString & inStr)
{
    QString outStr = QString("File %1 ready. %2 msec").arg(inStr).arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void File::writeReadFileName(const QString & inStr)
{
    QString outStr = QString("File %1 loaded. %2 msec").arg(inStr).arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void File::writeMatrixIsReady()
{
    QString outStr = QString("Total matrix is ready. %1 msec").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void File::writeFirstIntMatrixIsReady()
{
    QString outStr = QString("First integration data matrix is ready. %1 msec").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void File::writeSecIntMatrixIsReady()
{
    QString outStr = QString("Second integration data matrix is ready. %1 msec").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void File::writeSettingsLoaded()
{
    QString outStr = QString("Settings form %1 loaded. %2 msec").arg("Settings.txt").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}
