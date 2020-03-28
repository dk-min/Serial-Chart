#include "plot.h"
#include "SerialChart.h"
#include <QtWidgets>

/*
Plot::Plot(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent){

}
*/
Plot::Plot(){

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
    serialchart->Setcolcount(xhigh);
    serialchart->initchart();
    qDebug()<< "init chart completed!";
    serialchart->initserial();
    qDebug() << "serial init completed!";

    for(int i = 0; i < CHNUM; i++){
        serialchart->startUpdates(this->seriesreturn(i), i);
    }
    qDebug() << "serial chat update completed!";
    serialchart->TimerStart();
    qDebug() << "Timer start!";



    chart->addAxis(axisX, Qt::AlignBottom);
    qDebug() << "add Axis";
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->removeAllSeries();
    qDebug() << "remove all charts";
    for(int i = 0; i < CHNUM; i++){
        series[i].setUseOpenGL(true);
        chart->addSeries(&series[i]);
    }
    qDebug() << "chart series init completed!";



    chart->setAxisX(axisX, &series[0]);
    chart->setAxisY(axisY, &series[0]);

    axisX->setRange(0, xhigh);
    axisY->setRange(ylow, yhigh);

    chart->createDefaultAxes();
    chart->setTitle("Serial Chart");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->setRenderHint(QPainter::Antialiasing);

    QObject::connect(chart->scene(), &QGraphicsScene::changed,
                         serialchart, &SerialChart::handleSceneChanged);

    setCentralWidget(chartView);
    setWindowTitle("Serial Chart");
    resize(1600, 1000);
    show();

}

void Plot::closeEvent(QCloseEvent *event){
    qDebug() << "close event";
    if(serialchart->isopen()){
        close();
        qDebug() << "port is opened";
        chart->close();
        qDebug() << "chart closed";
        serialchart->close();
        event->accept();
    }
    else {
        qDebug() << "port is closed";
        event->ignore();
    }
}
