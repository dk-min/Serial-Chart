#include "SerialChart.h"
#include "qdebug.h"
#include <QSerialPort>

#include <QAbstractSeries> 

SerialChart::SerialChart(QObject *parent) : QObject(parent), thread(new draw(this))
{
    connect(Device, SIGNAL(readyRead()),this, SLOT(Receivedata()));
    connect(this, SIGNAL(datarecieved()),this, SLOT(txtfileadd()));
    connect(this, SIGNAL(isComportchanged()), this, SLOT(handleSceneChanged()));
    connect(m_dataUpdater, SIGNAL(timeout()), this, SLOT(updateAllSeries()));
}

SerialChart::SerialChart(int count, QObject *parent) :
    QObject(parent), m_count(count)
{

}


void SerialChart::WriteBaudrate(QString buadrate){
    m_baudrate = buadrate;
    emit isBaudRatechanged();
}

QString SerialChart::ReadBaudrate(void){
    return m_baudrate;
}

void SerialChart::WriteComport(QString comport){
    m_comport = comport;
    emit isComportchanged();
}

QString SerialChart::ReadComport(void){
    return m_comport;
}

void SerialChart::Writecounter(int counter){
    m_chart_count = counter;
    emit isCounterchanged();
}

int SerialChart::Readcounter(void){
    return m_chart_count;
}


void SerialChart::initserial(void){
    bool ok;
    Device->close();
    Device->setBaudRate(m_baudrate.toInt(&ok));
    Device->setPortName(m_comport);
    Device->open(QIODevice::ReadOnly);
    file->setFileName(filename);
}

bool SerialChart::isopen(void){
    return Device->isOpen();
}

void SerialChart::close(void){
    Device->close();
    m_dataUpdater->stop();

}

void SerialChart::Receivedata(void){
    //qDebug() << time.elapsed();
    //time.restart();
    QString received, buffer;
    while (Device->canReadLine()){
        buffer = Device-> readLine(); // reads in data line by line, separated by \n or \r characters
        //qDebug() << buffer;
        if(buffer.contains("\n")){
            textdata.append(buffer);
            received = buffer.trimmed();  // remove separated flag \n or \r
        }
    }
    data = received.split(",", QString::SkipEmptyParts);
    data_count = data.size();

    //qDebug() << buffer;
    //qDebug() << "data count is" << data_count;
    if(data_count)
        emit datarecieved();
    else
        textdata.clear();
}

void SerialChart::txtfileadd(void){
    textarray.append(textdata);
    textdata.clear();
    file->open(QIODevice::WriteOnly);
    file->write(textarray);
    file->close();
    ReadSerialData();
}

float SerialChart::Readdata(void){
    return m_data;
}

void SerialChart::update(QLineSeries* series, int index){

    QVector<QPointF> points = m_chartdata->at(index);
    series->replace(points);

}

void SerialChart::ReadSerialData(void)
{
    for(int i = 0; i < data_count; i++){
        ch_points[i].replace(buf_point, QPointF(buf_point, data.at(i).toDouble()));
        m_chartdata->replace(i, ch_points[i]);
    }
    if(++buf_point >= colCount){
        buf_point = 0;
    }

}


void SerialChart::handleSceneChanged(void)
{
    m_dataUpdater->start();
    //thread->processDraw(chart_series,channel, m_chartdata);
}


void SerialChart::initchart(int channel){
    buf_point = 0;
    this->channel = channel;
    for(int i = 0; i < channel; i++){
        ch_points[i].clear();
        ch_points[i].reserve(colCount);
        for(int j = 0; j < colCount; j++){
            ch_points[i].append(QPointF(j, 0));
        }
    }

    m_chartdata->clear();
    for(int i = 0; i < channel; i++){
        m_chartdata->append(ch_points[i]);
    }
    //time.start();
}

void SerialChart::Setcolcount(int x){
    colCount = x;
}

void SerialChart::startUpdates(QLineSeries* series, int index)
{
    chart_series[index] = series;
}

void SerialChart::TimerStart(void)
{
    //m_dataUpdater->start();
    m_dataUpdater->setInterval(30); // 60Hz
    m_dataUpdater->setSingleShot(false);

    //thread->processDraw(chart_series,channel, m_chartdata);
}

void SerialChart::updateAllSeries()
{
    for(int i = 0; i < channel; i++){
        QVector<QPointF> points = m_chartdata->at(i);
        chart_series[i]->replace(points);
    }
}

