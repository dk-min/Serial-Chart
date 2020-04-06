#include "plot.h"
#include "SerialChart.h"
#include <QtWidgets>

/*
Plot::Plot(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent){

}
*/
Plot::Plot(){
    series = new QLineSeries[channel]();
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

void Plot::setChannel(QString Channel){
    channel = Channel.toInt();
}

void Plot::initserial(SerialChart* mserial){
    serialchart = mserial;
}

void Plot::start(void){
    if(serialchart->isopen()){
        serialchart->close();
    }
    serialchart->Setcolcount(xhigh);
    serialchart->initchart(channel);
    qDebug()<< "init chart completed!";
    serialchart->initserial();
    qDebug() << "serial init completed!";

    if(series != nullptr)
        delete[] series;
    series = new QLineSeries[channel]();

    for(int i = 0; i < channel; i++){
        series[i].setUseOpenGL(true);
        chart->addSeries(&series[i]);
        qDebug() << "i count is " << i;
    }

    qDebug() << "chart series init completed!";
    axisX = new QValueAxis;
    axisY = new QValueAxis;
    //chart->addAxis(axisX, Qt::AlignBottom);
    //chart->addAxis(axisY, Qt::AlignLeft);



    //series->attachAxis(axisX);
    //series->attachAxis(axisY);
    //chart->setAxisX(axisX, &series[0]);
    //chart->setAxisY(axisY, &series[0]);

    qDebug() << "attach completed";

    for(int i = 0; i < channel; i++){
        serialchart->startUpdates(this->seriesreturn(i), i);
    }
    qDebug() << "serial chat update completed!";
    serialchart->TimerStart();
    qDebug() << "Timer start!";

    chart->createDefaultAxes();
    for(int i = 0; i < channel; i++){
        chart->setAxisX(axisX, &series[i]);
        chart->setAxisY(axisY, &series[i]);
    }

    axisX->setMax(xhigh);
    axisY->setRange(ylow, yhigh);

    chart->setTitle("Serial Chart");
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    qDebug() << "Axes and title, legend setting is completed";

    QChartView *chartView = new QChartView(chart);
    chartView->chart()->setTheme(QChart::ChartThemeLight);
    chartView->setRenderHint(QPainter::Antialiasing);
    setCentralWidget(chartView);


    QObject::connect(chart->scene(), &QGraphicsScene::changed,
                         serialchart, &SerialChart::handleSceneChanged);

    setWindowTitle("Serial Chart");
    resize(1600, 1000);
    show();

}

void Plot::closeEvent(QCloseEvent *event){
    qDebug() << "close event";
    if(serialchart->isopen()){
        serialchart->close();
        event->accept();
    }
    else {
        qDebug() << "port is closed";
        event->ignore();
    }
}
/*
Plot::~Plot(){
    delete serialchart;
    delete axisX;
    delete axisY;
    delete[] series;
    delete chart;
}
*/
