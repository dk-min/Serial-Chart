#include "plot.h"
#include "SerialChart.h"
Plot::Plot(QObject *parent) : QObject(parent)
{
}

QLineSeries *Plot::seriesreturn(int index){
    return &series[index];
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

    for(int i = 0; i < CHNUM; i++){
        serialchart->startUpdates(this->seriesreturn(i), i);
    }
    serialchart->TimerStart();



    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    for(int i = 0; i < CHNUM; i++){
        series[i].setUseOpenGL(true);
        chart->addSeries(&series[i]);
    }




    chart->setAxisX(axisX, &series[0]);
    chart->setAxisY(axisY, &series[0]);

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
