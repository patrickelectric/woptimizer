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

    QPluginLoader pluginLoader1;
    QPluginLoader pluginLoader2;
    QList<AlgorithmInterface *> pluginsPointer;
    for (const auto &path : paths) {
        qDebug() << "Checking path: " << path;
        auto files = QDir(path).entryList(QDir::Files);
        for(auto file : files) {
            qDebug() << "Checking file: " << file;
            pluginLoader1.setFileName(QString("%1/%2").arg(path, file));
            pluginLoader2.setFileName(QString("%1/%2").arg(path, file));
            if (pluginLoader1.load()) {
                qDebug() << "GOOD!";
                pluginsPointer.append(qobject_cast<AlgorithmInterface *>(pluginLoader1.instance()));
                pluginsPointer.append(qobject_cast<AlgorithmInterface *>(pluginLoader2.instance()));
                qDebug() << "Name:" << pluginsPointer.last()->name();
            } else {
                qDebug() << "Failed!";
            }
        }
    }

    for(auto* p : pluginsPointer) {
        qDebug() << "> " << p->name() << " >< " << p->output();
    }

    return 0;
}
