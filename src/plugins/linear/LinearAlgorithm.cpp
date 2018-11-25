#include <QDebug>

#include "LinearAlgorithm.h"

#include <cmath>

QString LinearAlgorithm::name() const
{
    return {"Linear"};
};

void LinearAlgorithm::input(QList<float> inputs)
{
    int inputSize = inputs.size();
    if(!inputSize) {
        qDebug() << "No valid input";
    }

    if(!_lines.size()) {
        _lines.reserve(inputSize);
        _output.reserve(inputSize);
        for(int i = 0; i < inputSize; i++) {
            _lines.append({-inputs[i], 0, -inputs[i], 0, 0, 0});
            _output.append(0);
        }
    }

    for(int i = 0; i < inputSize; i++) {
        _lines[i].a = (_lines[i].y1 - _lines[i].y2)/(_lines[i].x1 - _lines[i].x2);
        _lines[i].b = ((_lines[i].y1 + _lines[i].y2)/_lines[i].a - _lines[i].x1 - _lines[i].x2)/2;
        _output[i] = -_lines[i].b/_lines[i].a;
        qDebug() << _lines[i].x1 << _lines[i].x2 << _lines[i].y1 << _lines[i].y2 << _output[i];
        _lines[i].x2 = _lines[i].x1;
        _lines[i].y2 = _lines[i].y1;
        _lines[i].y1 = inputs[i];
        if(!std::isnormal(_output[i])) {
            _output[i] = 1;
            _lines[i].x2 = 0;
        }
        _lines[i].x1 = _output[i];
    }

    //TODO: Update this clear method to something better
    /*
    if(!_output.size()) {
        _output.clear();
        _output.reserve(inputSize);
        for(int i = 0; i < inputSize; i++) {
            _output.append(inputs[i]);
        }
    }*/
    //_output.clear();
    /*
    while(inputSize-- > 0) {
        _output.append((float)std::rand()/(float)RAND_MAX);
    }*/
    emit outputChanged();
};

QList<float> LinearAlgorithm::output()
{
    return _output;
};
