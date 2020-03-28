#ifndef SERIAL_H
#define SERIAL_H
#include <QObject>
#include <QStringList>
#include <QtSerialPort>


#include <QXYSeries>
#include <QLineSeries>

using namespace QtCharts;

QT_BEGIN_NAMESPACE
class QQuickView;
QT_END_NAMESPACE


#define BUFFER 128

class SerialChart : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ReadBaudrate READ ReadBaudrate WRITE WriteBaudrate NOTIFY isBaudRatechanged)
    Q_PROPERTY(QString Comport READ ReadComport WRITE WriteComport NOTIFY isComportchanged)
    Q_PROPERTY(int count  READ Readcounter WRITE Writecounter NOTIFY isCounterchanged)

public:
    explicit SerialChart(QObject *parent = nullptr);
    explicit SerialChart(int count, QObject *parent);

    void startUpdates(QLineSeries* series1, QLineSeries* series2);
    void WriteBaudrate(QString buadrate);
    QString ReadBaudrate(void);

    void WriteComport(QString comport);
    QString ReadComport(void);

    void Writecounter(int counter);
    int Readcounter(void);
    float Readdata(void);
    Q_INVOKABLE void initserial(void);
    Q_INVOKABLE void update(QAbstractSeries* series, int index);

    void ReadSerialData(void);
    void initchart(void);

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
    QList<QVector<QPointF> > m_chartdata;

    QVector<QPointF> ch1_points;
    QVector<QPointF> ch2_points;
    int buf_point = 0;
    qreal x = 0;
    qreal y = 0;
    QLineSeries* chart_series1;
    QLineSeries* chart_series2;

    QElapsedTimer m_fpsTimer;
    QTimer m_dataUpdater;

};

#endif // PORTNUMBER_H
