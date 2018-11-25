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

    //Input will always be minimized by the model
    virtual void input(QList<float> inputs) = 0;
    virtual QList<float> output() = 0;

signals:
    void outputChanged();

protected:
    QList<float> _output;
    //struct AlgorithmInterfacePrivate;
    //AlgorithmInterfacePrivate *d;
};

Q_DECLARE_INTERFACE(AlgorithmInterface, "org.ibexcps.woptimizer.plugins.Algorithm")
