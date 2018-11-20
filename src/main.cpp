#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QPluginLoader>

#include "AlgorithmInterface.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //return app.exec();

    QStringList paths;
    paths.prepend(QCoreApplication::applicationDirPath() + QStringLiteral("/plugins"));
    paths.prepend(QCoreApplication::applicationDirPath() + QStringLiteral("/../../../plugins"));

    QPluginLoader pluginLoader;
    for (const auto &path : paths) {
        qDebug() << "Checking path: " << path;
        auto files = QDir(path).entryList(QDir::Files);
        for(auto file : files) {
            qDebug() << "Checking file: " << file;
            pluginLoader.setFileName(QString("%1/%2").arg(path, file));
            if (pluginLoader.load()) {
                qDebug() << "GOOD!";
                qDebug() << "Name:" << qobject_cast<AlgorithmInterface *>(pluginLoader.instance())->name();
            } else {
                qDebug() << "Failed!";
            };
        }
    }

    return 0;
}
