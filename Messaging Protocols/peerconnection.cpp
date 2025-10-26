#include "peerconnection.h"
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QEventLoop>

PeerConnection::PeerConnection(QObject *parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &PeerConnection::onReadyRead);
}

void PeerConnection::connectToPeer(const QString &user, const QString &room) {
    username = user;
    roomKey = room;
    authenticated = false;

    socket->connectToHost("127.0.0.1", 12345);
    if (socket->waitForConnected(3000)) {
        QString auth = "AUTH|" + roomKey + "\n";
        socket->write(auth.toUtf8());

        // Wait briefly for AUTH_OK to be handled in onReadyRead
        QEventLoop loop;
        QTimer::singleShot(500, &loop, &QEventLoop::quit);
        loop.exec();

        if (authenticated) {
            qDebug() << " Authenticated to room:" << roomKey;
        } else {
            socket->disconnectFromHost();
            QMessageBox::warning(nullptr, "Authentication Failed",
                                 "Room key is invalid or server rejected connection.");
        }
    } else {
        QMessageBox::warning(nullptr, "Connection Error",
                             "Unable to connect to server.");
    }
}

void PeerConnection::sendMessage(const QString &message) {
    if (!authenticated) return;
    QString msg = "MSG|" + username + "|" + roomKey + "|" + message + "\n";
    socket->write(msg.toUtf8());
    qDebug() << " Sent message:" << msg;
}

void PeerConnection::sendFile(const QString &filePath) {
    if (!authenticated) return;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();  // Read once
        QString fileName = QFileInfo(filePath).fileName();
        QByteArray encodedData = data.toBase64();  // Encode the already-read data
        QByteArray packet = "FILE|" + username.toUtf8() + "|" + roomKey.toUtf8() + "|" + fileName.toUtf8() + "|" + encodedData + "\n";
        socket->write(packet);
    }
}

void PeerConnection::onReadyRead() {
    while (socket->canReadLine()) {
        QByteArray data = socket->readLine().trimmed();
        qDebug() << " Incoming data:" << data;
        QList<QByteArray> parts = data.split('|');

        if (data.startsWith("AUTH_OK")) {
            authenticated = true;
            qDebug() << " Received AUTH_OK from server";
        } else if (parts[0] == "MSG" && parts.size() >= 4) {
            emit messageReceived(parts[1], parts[3]);
            qDebug() << "👀 Displaying message from" << parts[1] << ":" << parts[3];
        } else if (parts[0] == "FILE" && parts.size() >= 5) {
            QString sender = parts[1];
            QString fileName = parts[3];
            QByteArray fileData = QByteArray::fromBase64(parts[4]);

            QString savePath = QCoreApplication::applicationDirPath() + "/" + fileName;
            QFile outFile(savePath);
            if (outFile.open(QIODevice::WriteOnly)) {
                outFile.write(fileData);
                outFile.close();
                qDebug() << " File saved to:" << savePath;
                QMessageBox::information(nullptr, "File Received", "File saved to:\n" + savePath);
            } else {
                QMessageBox::warning(nullptr, "File Save Error", "Could not save file to:\n" + savePath);
            }
        } else if (data.startsWith("ERROR")) {
            QMessageBox::warning(nullptr, "Server Error", QString::fromUtf8(data));
        }
    }
}
