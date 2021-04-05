#ifndef SETTINGS_H
#define SETTINGS_H

#include <QStringList>

enum FileType {TXT, BIN};

class Settings
{
private:
    static FileType fileType;
    static bool convert;
    static bool getMatrix;
    static bool integrateFirst;
    static bool integrateSecond;
    static double leftEdge;
    static double rightEdge;
public:
    static void loadSettings(const QStringList &);
    static bool getConvert();
    static bool getIntegrateFirst();
    static bool getIntegrateSecond();
    static bool getGetMatrix();
    static double getLeftEdge();
    static double getRightEdge();
    static FileType getFileType();
};

#endif // SETTINGS_H
