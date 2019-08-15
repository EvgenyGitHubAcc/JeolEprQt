#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QTime>
#include <iostream>

class Message
{
private:
    static QTime * timer;
public:
    static void writeFinishedFileName(const QString &);
    static void writeReadFileName(const QString &);
    static void writeMatrixIsReady();
    static void writeFirstIntMatrixIsReady();
    static void writeSecIntMatrixIsReady();
    static void writeSettingsLoaded();
    static void writeFileIntegrated(const QString &);
    static void setTimer(QTime *);
};

#endif // MESSAGE_H
