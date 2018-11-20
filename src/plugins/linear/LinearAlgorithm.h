#pragma once

#include "AlgorithmInterface.h"

class LinearAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ibexcps.woptimizer.plugins.Algorithm")
    Q_INTERFACES(AlgorithmInterface)
public:

    QString name() const;

    void input(QList<float> inputs) { Q_UNUSED(inputs) };
    QList<float> output() { return {0}; };

private:
    //struct AlgorithmInterfacePrivate;
    //AlgorithmInterfacePrivate *d;
};
