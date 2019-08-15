#ifndef FILE_H
#define FILE_H

#include <QStringList>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "data.h"
#include "converter.h"

class File
{
private:
    QTime * timer;
    QStringList srcFiles;
    QStringList dataString;
    QStringList potList;
    void purifyFile(QFile &);
public:
    File(QTime *);
    QStringList & loadSettings();
    void loadPotList();
    void readAllFiles(QList<Data> &);
    void writeAllFiles(QList<Data> &);
    void writeFirstIntegrationMatrix(Converter &, double, double);
    void writeSecondIntegrationMatrix(Converter &, double, double);
    void writeSettingsLoaded();
    void writeTotalMatrix(Converter &);
    void writeTime();
    void writeFinishedFileName(const QString &);
    void writeReadFileName(const QString &);
    void writeMatrixIsReady();
    void writeFirstIntMatrixIsReady();
    void writeSecIntMatrixIsReady();
    QString genPotLine(int);
    QString genFileNameLine();
    const QStringList & getSrcFiles();
};

#endif // FILE_H
