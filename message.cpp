#include "message.h"

QTime * Message::timer;

void Message::writeFinishedFileName(const QString & inStr)
{
    QString outStr = QString("File %1 ready. %2 msec").arg(inStr).arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::writeReadFileName(const QString & inStr)
{
    QString outStr = QString("File %1 loaded. %2 msec").arg(inStr).arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::writeMatrixIsReady()
{
    QString outStr = QString("Total matrix is ready. %1 msec").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::writeFirstIntMatrixIsReady()
{
    QString outStr = QString("First integration data matrix is ready. %1 msec").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::writeSecIntMatrixIsReady()
{
    QString outStr = QString("Second integration data matrix is ready. %1 msec").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::writeSettingsLoaded()
{
    QString outStr = QString("Settings form %1 loaded. %2 msec").arg("Settings.txt").arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::writeFileIntegrated(const QString & srcFile)
{
    QString outStr = QString("File %1 integrated. %2 msec").arg(srcFile).arg(timer->elapsed());
    std::cout << outStr.toStdString() << std::endl;
}

void Message::setTimer(QTime * _timer)
{
    timer = _timer;
}
