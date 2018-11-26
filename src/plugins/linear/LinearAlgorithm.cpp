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
            _lines.append({0, 1, 0, 1});
            _output.append(0);
        }
    }

    for(int i = 0; i < inputSize; i++) {
        // This input is a result of the last output
        _lines[i].y1 = inputs[i];

        /* Y is the error and it already includes the setpoint
            The object is to make error equal to 0 (Y = 0)

                y = a*x + b
                y_1 = a*x_1 + b
                y_2 = a*x_2 + b
                a = \frac{y_1 - y_2}{x_1 - x_2}
                b = \frac{y_1 + y_2 - a*(x_1 + x_2))}{2}
                x = \frac{-b}{a} \mid y = 0
                x = \frac{x_2*y_1 - x_1*y_2}{y_1 - y_2} \mid y = 0
        */
        _output[i] = (_lines[i].x2*_lines[i].y1 - _lines[i].x1*_lines[i].y2)/(_lines[i].y1 - _lines[i].y2);

        if(!std::isnormal(_output[i])) {
            _output[i] = 1;
            _lines[i].x2 = 0;
            _lines[i].x1 = -1;
        } else {
            _lines[i].x2 = _lines[i].x1;
            _lines[i].y2 = _lines[i].y1;
            _lines[i].x1 = _output[i];
        }
    }
    emit outputChanged();
};

QList<float> LinearAlgorithm::output()
{
    return _output;
};
