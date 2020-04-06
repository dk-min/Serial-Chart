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

class Plot : public QMainWindow{
    Q_OBJECT

public:
    //Plot(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    Plot();
    ~Plot() override{

    }


    QLineSeries *seriesreturn(int index);


    QChart *returnchart();

    Q_INVOKABLE void setYlow(QString Ylow);
    Q_INVOKABLE void setXhigh(QString Xhigh);
    Q_INVOKABLE void setYhigh(QString Yhigh);
    Q_INVOKABLE void setChannel(QString Channel);
    Q_INVOKABLE void start(void);

    void initserial(SerialChart* mserial);

signals:

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    SerialChart *serialchart = new SerialChart;
    QQuickView viewer;

    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;

    QLineSeries *series;
    QChart *chart = new QChart();
    QFont font;
    qreal xlow = 0, ylow = 512, yhigh = 4096;
    qint32 xhigh = 1024;
    int channel;
};

#endif // PLOT_H
