#ifndef SERVER_H
#define SERVER_H

#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QString>
#include <QList>

struct Room {
    QList<QTcpSocket*> clients;
};

class Server : public QObject {
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer *tcpServer;
    QMap<QString, Room> rooms;
    QMap<QTcpSocket*, QString> clientRoomMap;
};


#endif // SERVER_H
