#include <QDebug>

#include "LinearAlgorithm.h"

QString LinearAlgorithm::name() const
{
    return {"linear"};
};

QList<float> LinearAlgorithm::output()
{
    return {0};
};
