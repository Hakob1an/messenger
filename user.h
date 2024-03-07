#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(const QString &username, const QString &password);

    QString getUsername() const;
    void setUsername(const QString &username);

    QString getPassword() const;
    void setPassword(const QString &password);

private:
    QString m_username;
    QString m_password;
};

#endif // USER_H
