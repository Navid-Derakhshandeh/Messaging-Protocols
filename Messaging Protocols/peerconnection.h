#ifndef PEERCONNECTION_H
#define PEERCONNECTION_H

#pragma once

#include <QObject>
#include <QTcpSocket>

class PeerConnection : public QObject {
    Q_OBJECT

public:
    explicit PeerConnection(QObject *parent = nullptr);
    void connectToPeer(const QString &username, const QString &roomKey);
    void sendMessage(const QString &message);
    void sendFile(const QString &filePath);

signals:
    void messageReceived(const QString &sender, const QString &message);

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    QString username;
    QString roomKey;
    bool authenticated = false;
};




#endif // PEERCONNECTION_H
