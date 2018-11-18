#pragma once

#include <QObject>

class AlgorithmInterface : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    AlgorithmInterface();
    ~AlgorithmInterface() = default;

    virtual QString name() const = 0;

private:
    //struct AlgorithmInterfacePrivate;
    //AlgorithmInterfacePrivate *d;
};

Q_DECLARE_INTERFACE(AlgorithmInterface, "org.ibexcps.woptimizer.plugins.AlgorithmInterface")
