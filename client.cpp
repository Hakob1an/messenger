#include "client.h"


Client::Client(QString username, QObject *parent)
    : QObject(parent)
    , _username(username)
    , _socket(new QTcpSocket(this))
    , _usernameSent(false)
{
    connect(_socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QString &host, quint16 port)
{
    _socket->connectToHost(host, port);
    connect(_socket, &QTcpSocket::connected, this, &Client::onConnected);
}

void Client::onConnected()
{
    sendUsername(_username);
}

void Client::sendUsername(const QString &username)
{
    if (_socket->state() == QTcpSocket::ConnectedState && !_usernameSent) {
        QString initMessage = QString("%1").arg(username);
        _socket->write(initMessage.toUtf8());
        _usernameSent = true;
    }
}

void Client::sendMessage(const QString &message)
{
    if (_socket->state() == QTcpSocket::ConnectedState && _usernameSent) {
        QString chatMessage = QString("%1").arg(message);
        _socket->write(chatMessage.toUtf8());
    }
}

void Client::onReadyRead()
{
    QByteArray data = _socket->readAll();
    QString sender;
    QString message(data);
    emit receivedMessage(sender, message);
}
