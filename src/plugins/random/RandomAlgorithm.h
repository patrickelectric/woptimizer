#pragma once

#include "AlgorithmInterface.h"

class RandomAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ibexcps.woptimizer.plugins.Algorithm")
    Q_INTERFACES(AlgorithmInterface)

public:
    RandomAlgorithm();

    QString name() const;

    void input(QList<float> inputs);
    QList<float> output();

private:
    int i = 0;
};
