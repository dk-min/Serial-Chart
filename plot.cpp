#include "plot.h"
#include "SerialChart.h"
Plot::Plot(QObject *parent) : QObject(parent)
{
}

QLineSeries *Plot::series1return(void){
    return series1;
}

QLineSeries *Plot::series2return(void){
    return series2;
}

QChart *Plot::returnchart(){
    return chart;
}

void Plot::setYlow(QString Ylow){
    ylow = Ylow.toDouble();
}

void Plot::setXhigh(QString Xhigh){
    xhigh = Xhigh.toInt();
}

void Plot::setYhigh(QString Yhigh){
    yhigh = Yhigh.toDouble();
}

void Plot::initserial(SerialChart* mserial){
    serialchart = mserial;
}

void Plot::start(void){
    window.close();
    serialchart->Setcolcount(xhigh);
    serialchart->initchart();
    serialchart->initserial();

    serialchart->startUpdates(this->series1return(), this->series2return());

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    series1->setUseOpenGL(true);
    series2->setUseOpenGL(true);

    chart->addSeries(series1);
    chart->addSeries(series2);

    chart->setAxisX(axisX, series1);
    chart->setAxisY(axisY, series1);

    axisX->setRange(0, xhigh);
    axisY->setRange(ylow, yhigh);
    chart->legend()->hide();

    chart->createDefaultAxes();
    chart->setTitle("Serial Chart");

    QChartView *chartView = new QChartView(chart);
    chartView->chart()->setTheme(QChart::ChartThemeBrownSand);
    chartView->setRenderHint(QPainter::Antialiasing);

    QObject::connect(chart->scene(), &QGraphicsScene::changed,
                         serialchart, &SerialChart::handleSceneChanged);

    window.setCentralWidget(chartView);
    window.setWindowTitle("Serial Chart");
    window.resize(1600, 1000);
    window.show();

}
