#pragma once

#include "AlgorithmInterface.h"

class LinearAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ibexcps.woptimizer.plugins.Algorithm")
    Q_INTERFACES(AlgorithmInterface)
public:

    QString name() const;

private:
    //struct AlgorithmInterfacePrivate;
    //AlgorithmInterfacePrivate *d;
};
