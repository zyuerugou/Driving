#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>

class control : public QObject
{
    Q_OBJECT
public:
    explicit control(QObject *parent = 0);

signals:

public slots:
};

#endif // CONTROL_H