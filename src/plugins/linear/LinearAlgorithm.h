#pragma once

#include "AlgorithmInterface.h"

class LinearAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ibexcps.woptimizer.plugins.Algorithm")
    Q_INTERFACES(AlgorithmInterface)

public:
    QString name() const;

    void input(QList<float> inputs);
    QList<float> output();

    // y = a*x + b
    struct linear {
        float x1 = 0.0;
        float x2 = 0.0;
        float y1 = 0.0;
        float y2 = 0.0;
    };
    QList<linear> _lines;
};
