#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    if (ui->serverCheckBox->isChecked()) {
        server = new Server(this);
    } else {
        server = nullptr;
    }
    server = new Server(this);
    peer = new PeerConnection(this);
    connect(peer, &PeerConnection::messageReceived, this, &MainWindow::onMessageReceived);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString roomKey = ui->roomKeyEdit->text();
    peer->connectToPeer(username, roomKey);  //  Pass both arguments

}


void MainWindow::on_sendButton_clicked()
{
    QString message = ui->messageEdit->text();
    peer->sendMessage(message);
    ui->chatLog->append("Me: " + message);
}


void MainWindow::on_fileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select File");
    if (!filePath.isEmpty()) {
        peer->sendFile(filePath);
    }
}
void MainWindow::onMessageReceived(const QString &sender, const QString &message) {
    ui->chatLog->append(sender + ": " + message);
}

