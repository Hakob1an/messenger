#include "mainwindow.h"
#include "worker.h"
#include "logindialog.h"
#include "databasemanager.h"
#include <QApplication>
#include <QThread>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseManager dbManager;
    if (!dbManager.createConnection()) {
       return -1;
    }

    LoginDialog loginDialog;
    if (loginDialog.exec() != QDialog::Accepted) {
        return 0;
    }

    qDebug() << "username: " << loginDialog.getUsername() << "\n";

    MainWindow mainWindow(loginDialog.getUsername());
    mainWindow.show();

    QThread* thread = new QThread();
    Worker* worker = new Worker("127.0.0.1", 8080, "User1");
    worker->moveToThread(thread);

    QObject::connect(thread, &QThread::started, worker, &Worker::process);
    QObject::connect(worker, &Worker::finished, thread, &QThread::quit);
    QObject::connect(worker, &Worker::finished, worker, &Worker::deleteLater);
    QObject::connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();

    return app.exec();
}
