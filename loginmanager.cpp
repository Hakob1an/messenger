#include "loginmanager.h"

LoginManager::LoginManager(QObject *parent) : QObject(parent), _user("admin", "password")
{}

bool LoginManager::login(const QString &username, const QString &password)
{
    if(username == _user.getUsername() && password == _user.getPassword()) {
        emit loginSuccess(_user);
        return true;
    } else {
        emit loginFailure("Invalid username or password.");
        return false;
    }
}
