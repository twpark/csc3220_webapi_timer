#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include <QObject>

class HTTPManager : public QObject
{
    Q_OBJECT
public:
    explicit HTTPManager(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HTTPMANAGER_H