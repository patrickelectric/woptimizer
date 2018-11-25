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
    QStringList pluginsName {
        //"Random",
        "Linear",
    };

    auto model = [](float input) -> float {
        return std::exp(1.0)*input + M_PI;
    };

    const float minError = 0.05;

    for(const auto& pluginName : pluginsName) {
        QVERIFY2(_pluginsPointer.contains(pluginName), "Cant find plugin");
        connect(_pluginsPointer[pluginName], &AlgorithmInterface::outputChanged, this, [this, pluginName, model, minError] {
            qDebug() << pluginName;
            float output = _pluginsPointer[pluginName]->output().first();
            float error = model(output);
            qDebug() << QString("[%1] error: %2").arg(pluginName).arg(error);
            if(std::abs(error) > minError) {
                _pluginsPointer[pluginName]->input({error});
            }
        });
        _pluginsPointer[pluginName]->input({0.5});
    }
}
/*
void Test::linear()
{
    QString pluginName = "Linear";
    QVERIFY2(_pluginsPointer.contains(pluginName), "Cant find plugin");
    connect(_pluginsPointer[pluginName], &AlgorithmInterface::outputChanged, this, [this, &pluginName] {
        float output = _pluginsPointer[pluginName]->output().first();
        float error = output - 0.5;
        if(std::abs(error) < 0.1) {
            qDebug() << "Done";
        } else {
            qDebug() << "Waiting 0.5, got:" << output;
            _pluginsPointer[pluginName]->input({error});
        }
    });
    _pluginsPointer[pluginName]->input({0.5});
}*/

QTEST_MAIN(Test)
