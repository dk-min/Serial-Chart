#ifndef PORTNUMBER_H
#define PORTNUMBER_H
#include <QObject>
#include <QStringList>

class PortNumber : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList comboList READ comboList WRITE setComboList NOTIFY comboListChanged)
    Q_PROPERTY(int count READ count WRITE setCount NOTIFY countChanged)

public:
    PortNumber(QObject *parent = nullptr);
    PortNumber(const QStringList &list,int count, QObject *parent);

    QStringList comboList();
    void setComboList(const QStringList &comboList);

    int count();
    void setCount(int cnt);
    void update(void);


    Q_INVOKABLE void addElement(const QString &element);
    Q_INVOKABLE void removeElement(int index);

signals:
    void comboListChanged();
    void countChanged();

public slots:


private:

    QStringList m_comboList;
    int         m_count;
};

#endif // PORTNUMBER_H
