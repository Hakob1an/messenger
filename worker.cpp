#include "worker.h"

Worker::Worker(const QString& serverAddress, quint16 port, const QString& username, QObject *parent)
    : QObject(parent)
    , _serverAddress(serverAddress)
    , _port(port)
    , _username(username)
{
    _client = new Client(_username, this);
}

Worker::~Worker()
{
    _client->disconnect();
}

void Worker::process()
{
    connect(_client, &Client::receivedMessage, this, [](const QString &sender, const QString &message) {
        qDebug() << sender << ": " << message;
    });

    _client->connectToServer(_serverAddress, _port);
    QThread::sleep(1);

    _client->sendUsername(_username);

    emit finished();
}
