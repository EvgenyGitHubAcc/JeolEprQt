#ifndef FILE_H
#define FILE_H

#include <QStringList>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "data.h"
#include "converter.h"
#include "message.h"
#include "binextractor.h"

class File
{
private:
    QStringList srcFiles;
    QStringList dataString;
    QStringList potList;
    void purifyFile(QFile &);
public:
    File();
    QStringList & loadSettings();
    void loadPotList();
    void readAllFiles(QList<Data> &);
    void readAllBinFiles(QList<Data> &);
    void writeAllFiles(QList<Data> &);
    void writeFirstIntegrationMatrix(Converter &, double, double);
    void writeSecondIntegrationMatrix(Converter &, double, double);
    void writeSettingsLoaded();
    void writeTotalMatrix(Converter &);
    void getFileNameInSrcDir();
    QString genPotLine(int);
    QString genFileNameLine();
    const QStringList & getSrcFiles();
};

#endif // FILE_H
