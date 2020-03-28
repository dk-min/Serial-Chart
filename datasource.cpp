#include "datasource.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)

DataSource::DataSource(QObject *parent) :
    QObject(parent),
    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();

    init();
}

void DataSource::update(QAbstractSeries *series, int index)
{
    QXYSeries *xySeries = static_cast<QXYSeries *>(series);
    (index == 0)?(xySeries->replace(xySeries1)):(xySeries->replace(xySeries2));

/*
    m_index++;
    if (m_index > m_data.count() - 1)
        m_index = 0;

    QVector<QPointF> points = m_data.at(m_index);
    // Use replace instead of clear + append, it's optimized for performance
    xySeries->replace(points);
    */
}

void DataSource::generateData(int type, int rowCount, int colCount)
{
    // Remove previous data
    m_data.clear();

    // Append the new data depending on the type
    for (int i(0); i < rowCount; i++) {
        QVector<QPointF> points;
        points.reserve(colCount);
        for (int j(0); j < colCount; j++) {
            qreal x(0);
            qreal y(0);
            switch (type) {
            case 0:
                // data with sin + random component
                y = qSin(M_PI / 50 * j) + 0.5 + QRandomGenerator::global()->generateDouble();
                x = j;
                break;
            case 1:
                // linear data
                x = j;
                y = (qreal) i / 10;
                break;
            default:
                // unknown, do nothing
                break;
            }
            points.append(QPointF(x, y));
        }
        m_data.append(points);
    }
}

void DataSource::init(void)
{
    QPointF points;
    for (int j = 0; j < 256; j++) {
        qreal x;
        qreal y;
            // data with sin + random component
        y = 0;
        x = j;
        points.setX(x);
        points.setX(y);
        xySeries1.append(points);
        xySeries2.append(points);
    }
}

void DataSource::serialData(QStringList *data)
{
    xySeries1.replace(m_index, QPointF(m_index,static_cast<qreal>(data->at(0).toFloat())));
    xySeries2.replace(m_index, QPointF(m_index,static_cast<qreal>(data->at(1).toFloat())));
    m_index++;
    if(m_index>=256)
        m_index = 0;
}
