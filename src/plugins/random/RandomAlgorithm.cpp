#include "RandomAlgorithm.h"

#include <cstdlib>
#include <ctime>

#include <QDebug>

RandomAlgorithm::RandomAlgorithm()
{
    // Use current time as seed for random generator
    std::srand(std::time(nullptr));
};

QString RandomAlgorithm::name() const
{
    return {"Random"};
};

void RandomAlgorithm::input(QList<float> inputs)
{
    int inputSize = inputs.size();
    if(!inputSize) {
        qDebug() << "No valid input";
    }

    //TODO: Update this clear method to something better
    _output.clear();
    _output.reserve(inputSize);
    while(inputSize-- > 0) {
        _output.append((float)std::rand()/(float)RAND_MAX);
    }
    emit outputChanged();
};

QList<float> RandomAlgorithm::output()
{
    return _output;
};
