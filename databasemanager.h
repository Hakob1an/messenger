#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <openssl/evp.h>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();
    bool createConnection();
    bool checkOrRegisterUser(const QString& username, const QString& password);

private:
    QSqlDatabase _db;
    static int _instanceCount;
    QString _connectionName;

    QString hashPassword(const QString& password);
    bool registerUser(const QString& username, const QString& password);
};

#endif // DATABASEMANAGER_H
