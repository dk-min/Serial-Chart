#include "portnumber.h"
#include "qdebug.h"
#include <QSerialPortInfo>
PortNumber::PortNumber(QObject *parent) : QObject(parent)
{
}

PortNumber::PortNumber(const QStringList &list, int count, QObject *parent) : QObject(parent), m_comboList(list), m_count(count)
{

}

QStringList PortNumber::comboList()
{
    update();
    return m_comboList;
}

void PortNumber::update(void){
    m_comboList = QStringList();
    setCount(0);
    auto infos = QSerialPortInfo::availablePorts();
    for(QSerialPortInfo &info : infos){
        this->addElement(info.portName());
    }
}
void PortNumber::setComboList(const QStringList &comboList)
{

    if (m_comboList != comboList)
    {
        m_comboList = comboList;
        emit comboListChanged();
    }

}

int PortNumber::count()
{
    return m_count;
}

void PortNumber::setCount(int cnt)
{
    if (cnt != m_count)
    {
        m_count = cnt;
        emit countChanged();
    }
}

void PortNumber::addElement(const QString &element)
{
    m_comboList.append(element);
    emit comboListChanged();
    setCount(m_comboList.count());
    emit countChanged();

    for (int i = 0; i<m_count; i++)
    {
        qDebug() << m_comboList.at(i);
    }
}

void PortNumber::removeElement(int index)
{
    if (index < m_comboList.count())
    {
        m_comboList.removeAt(index);
        emit comboListChanged();
        setCount(m_comboList.count());
        emit countChanged();
    }

    for (int i = 0; i<m_count; i++)
    {
        qDebug() << m_comboList.at(i);
    }
}
