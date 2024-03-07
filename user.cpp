#include "user.h"

User::User(const QString &username, const QString &password)
    : m_username(username), m_password(password)
{
}

QString User::getUsername() const
{
    return m_username;
}

void User::setUsername(const QString &username)
{
    m_username = username;
}

QString User::getPassword() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}
