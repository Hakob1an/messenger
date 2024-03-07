#include "logindialog.h"
#include "databasemanager.h"
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent)
{
    _usernameLineEdit = new QLineEdit(this);
    _passwordLineEdit = new QLineEdit(this);
    _passwordLineEdit->setEchoMode(QLineEdit::Password);

    _loginButton = new QPushButton(tr("Login"), this);
    _cancelButton = new QPushButton(tr("Cancel"), this);

    connect(_loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(_cancelButton, &QPushButton::clicked, this, &LoginDialog::onCancelClicked);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(new QLabel(tr("Username:")), 0, 0);
    layout->addWidget(_usernameLineEdit, 0, 1);
    layout->addWidget(new QLabel(tr("Password:")), 1, 0);
    layout->addWidget(_passwordLineEdit, 1, 1);
    layout->addWidget(_loginButton, 2, 0, 1, 2);
    layout->addWidget(_cancelButton, 3, 0, 1, 2);

    setLayout(layout);
    setWindowTitle(tr("Login"));
}

QString LoginDialog::getUsername() const
{
    return _usernameLineEdit->text();
}

QString LoginDialog::getPassword() const
{
    return _passwordLineEdit->text();
}

void LoginDialog::onLoginClicked()
{
    DatabaseManager dbManager;
    if (dbManager.checkOrRegisterUser(getUsername(), getPassword())) {
        emit loginSuccessful(getUsername());
        accept();
    } else {
        QMessageBox::warning(this, tr("Login Failed"), tr("Invalid username or password."));
    }
}

void LoginDialog::onCancelClicked()
{
    reject();
}
