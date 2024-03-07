#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QString username, QObject *parent = nullptr);
    void connectToServer(const QString &host, quint16 port);
    void sendUsername(const QString &username);
    void sendMessage(const QString &message);
    QString getUsername() const { return _username; }
    void setUsername(QString username) { _username = username; }
    void onConnected();

signals:
    void receivedMessage(const QString &sender, const QString &message);

private slots:
    void onReadyRead();

private:
    QString _username;
    QTcpSocket *_socket;

public:
    bool _usernameSent;
};

#endif //CLIENT_H
