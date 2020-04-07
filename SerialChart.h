#ifndef SERIAL_H
#define SERIAL_H

#include "draw.h"

#include <QObject>
#include <QStringList>
#include <QtSerialPort>
#include <QTime>


#include <QXYSeries>
#include <QLineSeries>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE


#define BUFFER 128
#define CHNUM 10

class SerialChart : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ReadBaudrate READ ReadBaudrate WRITE WriteBaudrate NOTIFY isBaudRatechanged)
    Q_PROPERTY(QString Comport READ ReadComport WRITE WriteComport NOTIFY isComportchanged)
    Q_PROPERTY(int count  READ Readcounter WRITE Writecounter NOTIFY isCounterchanged)

public:
    explicit SerialChart(QObject *parent = nullptr);
    explicit SerialChart(int count, QObject *parent);

    void startUpdates(QLineSeries* series, int index);
    void WriteBaudrate(QString buadrate);
    QString ReadBaudrate(void);

    void WriteComport(QString comport);
    QString ReadComport(void);

    void Writecounter(int counter);
    int Readcounter(void);
    float Readdata(void);
    Q_INVOKABLE void initserial(void);
    Q_INVOKABLE void update(QLineSeries* series, int index);

    void ReadSerialData(void);
    void initchart(int channel);
    void TimerStart(void);


    bool isopen(void);
    void close(void);

    void Setcolcount(int x);

signals:
    void isBaudRatechanged(void);
    void isComportchanged(void);
    void isCounterchanged(void);
    void datarecieved(void);

public slots:
    void Receivedata(void);
    void txtfileadd(void);
    void handleSceneChanged(void);
    void updateAllSeries(void);

private:
    bool mbaudchange;
    QString m_baudrate;
    QElapsedTimer time;
    qint64 buf[2] = {0,};

    bool mcomchange;
    QString m_comport;
    int     m_count;
    int     data_count;
    int     m_chart_count;
    QStringList data;
    int     m_datatotal = 0;
    float     m_data;
    QSerialPort *Device = new QSerialPort(this);
    QFile *file = new QFile;
    QString filename = "data.txt";
    QString textdata;
    QByteArray textarray;

    int rowCount =2, colCount = 1000;
    int m_index = 0;

    int debug_count = 0;
    QAbstractSeries *series;
    QList<QVector<QPointF>> *m_chartdata = new QList<QVector<QPointF>>;

    QVector<QPointF> *ch_points = new QVector<QPointF>[CHNUM];
    int buf_point = 0;
    qreal x = 0;
    qreal y = 0;
    QLineSeries* chart_series[CHNUM];

    QElapsedTimer m_fpsTimer;
    QTimer *m_dataUpdater = new QTimer;
    int channel;

    draw *thread;

};

#endif // PORTNUMBER_H
