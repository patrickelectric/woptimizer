#include <QtTest/QtTest>

class AlgorithmInterface;
/**
 * @brief Test class to test basic functionalities
 *
 */
class Test: public QObject
{
    Q_OBJECT
private slots:
    /**
     * @brief Initialize what is necessary
     *
     */
    void initTestCase();

    void loadPlugins();

    void linearModel();
    //void linear();

private:
    QMap<QString, AlgorithmInterface *> _pluginsPointer;
};
