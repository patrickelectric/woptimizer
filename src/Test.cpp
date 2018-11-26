#define private public
#define protected public

#include <cmath>

#include <QDebug>

#include "Test.h"

#include "AlgorithmInterface.h"

void Test::initTestCase()
{
}

void Test::loadPlugins()
{
    // Loading plugins
    QStringList paths;
    paths.prepend(QCoreApplication::applicationDirPath() + QStringLiteral("/plugins"));
    paths.prepend(QCoreApplication::applicationDirPath() + QStringLiteral("/../../../plugins"));

    QPluginLoader pluginLoader;
    for (const auto &path : paths) {
        //qDebug() << "Checking path: " << path;
        auto files = QDir(path).entryList(QDir::Files);
        for(auto file : files) {
            //qDebug() << "Checking file: " << file;
            pluginLoader.setFileName(QString("%1/%2").arg(path, file));
            if (pluginLoader.load()) {
                auto objectCast = qobject_cast<AlgorithmInterface *>(pluginLoader.instance());
                _pluginsPointer[objectCast->name()] = objectCast;
                //qDebug() << "Valid plugin. Name:" << _pluginsPointer.last()->name();
            }
        }
    }
}

void Test::linearModel()
{
    struct LinearTest {
        QString name;
        float minError;
    };
    QList<LinearTest> testStruct {
        // Do not expect it to be correct
        {"Random", std::numeric_limits<float>::max()},
        // epsilon * 10 is out default error for any good algorithm
        {"Linear", std::numeric_limits<float>::epsilon()*10},
    };

    auto model = [](float input) -> float {
        return std::exp(1.0)*input + M_PI;
    };

    const float minError = 0.05;

    for(const auto& test : testStruct) {
        QString pluginName = test.name;
        float minError = test.minError;

        QVERIFY2(_pluginsPointer.contains(pluginName), "Cant find plugin");
        connect(_pluginsPointer[pluginName], &AlgorithmInterface::outputChanged, this, [this, pluginName, model, minError] {
            auto outputs = _pluginsPointer[pluginName]->output();
            QList<float> errors;
            errors.reserve(outputs.size());
            bool good = true;

            for(const auto output : outputs) {
                errors.append(model(output));
                if(std::abs(errors.last()) > minError) {
                    good = false;
                }
            }
            if(!good) {
                _pluginsPointer[pluginName]->input(errors);
            } else {
                qDebug() << QString("[%1] error:").arg(pluginName) << errors;
            }
        });

        QList<float> input;
        std::srand(std::time(nullptr));
        for(int total = 100; total --> 0;) {
            input.append(std::rand()/(float)RAND_MAX);
        }
        qDebug() << QString("[%1] INPUT:").arg(pluginName) << input;
        _pluginsPointer[pluginName]->input(input);
    }
}

QTEST_MAIN(Test)
