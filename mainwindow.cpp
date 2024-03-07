#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString username, QWidget *parent)
    : QMainWindow(parent)
    , _client(new Client(username, this))
{
    _chatDisplay = new QTextEdit;
    _chatDisplay->setReadOnly(true);
    _chatDisplay->setStyleSheet("QTextEdit {"
                                "background-color: #C47899;"
                                "border: 2px solid #BD4F7F;"
                                "border-radius: 10px;"
                                "padding: 5px;"
                                "color: white;"
                                "font-weight: bold;"
                                "}");

    _messageInput = new QLineEdit;
    _messageInput->setStyleSheet("QLineEdit {"
                                 "background-color: #C47899;"
                                 "border: 2px solid #BD4F7F;"
                                 "border-radius: 10px;"
                                 "padding: 5px;"
                                 "color: white;"
                                 "font-weight: bold;"
                                 "}");

    QFont font("Arial", 11, QFont::TypeWriter);
    _chatDisplay->setFont(font);

    _sendButton = new QPushButton(tr("Send"));
    //_sendButton->setStyleSheet("background-color: #C47899");
    _sendButton->setStyleSheet("QPushButton {"
                               "    background-color: #C47899;"
                               "    border: 2px solid #BD4F7F;"
                               "    border-radius: 10px;"
                               "    padding: 5px;"
                               "    color: white;"
                               "    font-weight: bold;"
                               "}"
                               "QPushButton:hover {"
                               "    background-color: #BF5E88;"
    "}");

    connect(_sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);

    auto* layout = new QVBoxLayout;
    layout->addWidget(_chatDisplay);
    layout->addWidget(_messageInput);
    layout->addWidget(_sendButton);

    layout->setSpacing(10);
    layout->setMargin(10);

    this->setStyleSheet("background-color: #ffffff;");

    auto* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(_client, &Client::receivedMessage, this, &MainWindow::onReceivedMessage);

    _client->connectToServer("localhost", 8080);
    _client->sendUsername(username);
}

MainWindow::~MainWindow()
{}

void MainWindow::onReceivedMessage(const QString &sender, const QString &message)
{
    _chatDisplay->append(sender + message);
}

void MainWindow::onSendClicked()
{
    QString message = _messageInput->text();

    if (!message.isEmpty()) {
        _chatDisplay->append("Me: " + message);

        _client->sendMessage(message);

        _messageInput->clear();
    }
}

void MainWindow::onLoginSuccess(const User& user)
{
    qDebug() << "Login successful for user:" << user.getUsername();
}

void MainWindow::onLoginFailure(const QString& message)
{
    qDebug() << "Login failed:" << message;
}
