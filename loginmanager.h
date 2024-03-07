#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "user.h"
#include <QObject>

class LoginManager : public QObject
{
    Q_OBJECT
public:
    explicit LoginManager(QObject *parent = nullptr);

    bool login(const QString &username, const QString &password);

signals:
    void loginSuccess(const User& user);
    void loginFailure(const QString& message);

private:
    User _user;
};

#endif // LOGINMANAGER_H
