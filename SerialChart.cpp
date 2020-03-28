#include "SerialChart.h"
#include "qdebug.h"
#include <QSerialPort>

#include <QAbstractSeries> 


//Q_DECLARE_METATYPE(QAbstractSeries *)
//Q_DECLARE_METATYPE(QAbstractAxis *)
//Q_DECLARE_METATYPE(QLineSeries *)

SerialChart::SerialChart(QObject *parent) : QObject(parent)
{
    connect(Device, SIGNAL(readyRead()),this, SLOT(Receivedata()));
    connect(this, SIGNAL(datarecieved()),this, SLOT(txtfileadd()));
    connect(this, SIGNAL(isComportchanged()), this, SLOT(handleSceneChanged()));
    //qRegisterMetaType<QAbstractSeries*>();
    //qRegisterMetaType<QLineSeries*>();
    //qRegisterMetaType<QAbstractAxis*>();
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

void SerialChart::Receivedata(void){
    QString received, buffer;
    while (Device->canReadLine()){
        buffer = Device-> readLine(); // reads in data line by line, separated by \n or \r characters
        if(buffer.contains("\n")){
            received = buffer.trimmed();  // remove separated flag \n or \r
        }
        //qDebug() << received;
    }
    if(received.contains(",", Qt::CaseInsensitive)){
        //qDebug() << "it contains ','";
        data = received.split(",", QString::SkipEmptyParts); // remove blank parts
    }
    else {
        //qDebug() << "it dosen't contain ','";
        data = received.split("", QString::SkipEmptyParts);
    }
    data_count = data.size();
    //qDebug() << data;
    qDebug() << "data count is" << data_count;
    if(data_count)
        emit datarecieved();
}

float SerialChart::Readdata(void){
    return m_data;
}

void SerialChart::update(QAbstractSeries* series, int index){
    QLineSeries *xySeries = static_cast<QLineSeries *>(series);
    QVector<QPointF> points = m_chartdata.at(index);
    xySeries->replace(points);
}

void SerialChart::ReadSerialData(void)
{
    for(int i = 0; i < data_count; i++){
        ch_points[i].replace(buf_point, QPointF(buf_point, data.at(i).toDouble()));
        m_chartdata.replace(i, ch_points[i]);
    }
    if(++buf_point >= colCount){
        buf_point = 0;
    }
}


void SerialChart::txtfileadd(void){
    file->open(QIODevice::WriteOnly);
    for(int i = 0; i < data_count - 1; i++){
        textdata.append(data.at(i));
        textdata.append(',');
    }
    textdata.append(data.at(data_count - 1));
    textdata.append('\n');

    qDebug() << textdata;
    textarray.append(textdata);
    textdata.clear();
    file->write(textarray);
    ReadSerialData();
    file->close();
}

void SerialChart::handleSceneChanged(void)
{
    m_dataUpdater.start();
}


void SerialChart::initchart(void){
    for(int i = 0; i < CHNUM; i++){
        ch_points[i].clear();
        ch_points[i].reserve(colCount);
        for(int j = 0; j < colCount; j++){
            ch_points[i].append(QPointF(j, 0));
        }
    }

    m_chartdata.clear();
    for(int i = 0; i < CHNUM; i++){
        m_chartdata.append(ch_points[i]);
    }
    qDebug()<< "init completed!";
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
    m_dataUpdater.setInterval(1/60*1000); // 60Hz
    m_dataUpdater.setSingleShot(true);

    connect(&m_dataUpdater, SIGNAL(timeout()), this, SLOT(updateAllSeries()));
}

void SerialChart::updateAllSeries()
{
    for(int i = 0; i < CHNUM; i++){
        update(chart_series[i], i);
    }
}

