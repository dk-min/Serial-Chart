#ifndef DRAW_H
#define DRAW_H

#include <QObject>

#include <QThread>
#include <QMutex>

#include <QTimer>

#include <QXYSeries>
#include <QLineSeries>

using namespace QtCharts;

class draw : public QThread{
    Q_OBJECT

public:
    draw(QObject *parent = nullptr);
    ~draw();

public slots :
    void processDraw(QLineSeries** series, const int channel, QList<QVector<QPointF>>* chartdata);

protected:
    void run();

private:
    bool m_abort;
    QMutex mutex;
    qint8 channel = 4;
    QLineSeries **line;
    QList<QVector<QPointF>> *chartdata;
    QTimer *m_dataUpdater = new QTimer;
};

#endif // DRAW_H
