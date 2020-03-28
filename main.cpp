#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QList>

#include <QApplication>

#include <QQmlContext>

#include <QObject>

#include <QtQuick/QQuickView>


#include "portnumber.h"
#include "SerialChart.h"
#include "plot.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QtWidgets/QMainWindow>

#include <QtWidgets/QLabel>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Material");
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    SerialChart *mSerial = new SerialChart;
    PortNumber *portnum = new PortNumber;
    Plot *mplot = new Plot;
    mplot->initserial(mSerial);

    engine.rootContext()->setContextProperty("portnum", portnum);  // set portnum variable in qml file
    engine.rootContext()->setContextProperty("serialC", mSerial);  // set Serial variable in qml file
    engine.rootContext()->setContextProperty("windowC", mplot);    // set plot variable in qml file

    qDebug()<< "qml variable setting is completed!";

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}

