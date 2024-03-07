#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "databasemanager.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QMessageBox>


class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    QString getUsername() const;
    QString getPassword() const;

private slots:
    void onLoginClicked();
    void onCancelClicked();

signals:
    void loginSuccessful(const QString& username);

private:
    QLineEdit *_usernameLineEdit;
    QLineEdit *_passwordLineEdit;
    QPushButton *_loginButton;
    QPushButton *_cancelButton;
};

#endif // LOGINDIALOG_H
