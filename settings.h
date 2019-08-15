#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QStringList>

class Settings
{
private:
    bool convert;
    bool getMatrix;
    bool integrateFirst;
    bool integrateSecond;
    double leftEdge;
    double rightEdge;
public:
    Settings();
    Settings(const QStringList &);
    bool getConvert() const;
    bool getIntegrateFirst() const;
    bool getIntegrateSecond() const;
    bool getGetMatrix() const;
    double getLeftEdge() const;
    double getRightEdge() const;
};

#endif // SETTINGS_H
