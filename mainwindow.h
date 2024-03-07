#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client.h"
#include "loginmanager.h"
#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QDir>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString username, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onLoginSuccess(const User& user);
    void onLoginFailure(const QString& message);

private slots:
    void onSendClicked();
    void onReceivedMessage(const QString &sender, const QString &message);

private:
    Client *_client;
    QTextEdit *_chatDisplay;
    QLineEdit *_messageInput;
    QPushButton *_sendButton;
};
#endif // MAINWINDOW_H
