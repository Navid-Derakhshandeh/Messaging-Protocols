#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include "server.h"
#include "peerconnection.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_connectButton_clicked();
    void on_sendButton_clicked();
    void on_fileButton_clicked();
    void onMessageReceived(const QString &sender, const QString &message);
private:
    Ui::MainWindow *ui;
    Server *server;
    PeerConnection *peer;
};
#endif // MAINWINDOW_H
