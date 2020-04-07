#include "draw.h"

draw::draw(QObject *parent) : QThread(parent){
    m_abort = false;
}

draw::~draw(){
    mutex.lock();
    m_abort = true;
    mutex.unlock();

    wait();
}

void draw::processDraw(QLineSeries** series, const int channel, QList<QVector<QPointF>>* chartdata){
    line = series;
    this->channel = channel;
    this->chartdata = chartdata;
    start();
}

void draw::run(){
    for(int i = 0; i < channel; i++){
        if (m_abort)
            return;
        QVector<QPointF> points = chartdata->at(i);
        line[i]->replace(points);
    }
    msleep(10);
}
