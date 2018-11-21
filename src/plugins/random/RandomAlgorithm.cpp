#include "RandomAlgorithm.h"

QString RandomAlgorithm::name() const
{
    return {"random"};
};

QList<float> RandomAlgorithm::output()
{
    return {i++};
};
