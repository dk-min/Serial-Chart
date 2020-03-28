#ifndef PLOT_H
#define PLOT_H

#include <QObject>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QtWidgets/QMainWindow>

#include <QtWidgets/QLabel>
#include <QtQuick/QQuickView>
#include "SerialChart.h"


QT_CHARTS_USE_NAMESPACE

class Plot : public QObject{
    Q_OBJECT

public:
    Plot(QObject *parent = nullptr);


    QLineSeries *seriesreturn(int index);


    QChart *returnchart();

    Q_INVOKABLE void setYlow(QString Ylow);
    Q_INVOKABLE void setXhigh(QString Xhigh);
    Q_INVOKABLE void setYhigh(QString Yhigh);
    Q_INVOKABLE void start(void);

    void initserial(SerialChart* mserial);

signals:


private:
    SerialChart *serialchart;
    QQuickView viewer;

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    QLineSeries *series = new QLineSeries[CHNUM]();
    QChart *chart = new QChart();
    QFont font;
    QMainWindow window;
    qreal xlow, ylow, yhigh;
    qint32 xhigh;
};

#endif // PLOT_H
