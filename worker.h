#ifndef WORKER_H
#define WORKER_H

#include "client.h"
#include <QObject>
#include <QThread>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(const QString& serverAddress, quint16 port, const QString& username, QObject *parent = nullptr);
    ~Worker();

public slots:
    void process();

signals:
    void finished();

private:
    Client *_client;
    QString _serverAddress;
    quint16 _port;
    QString _username;
};

#endif // WORKER_H
