#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent) {
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);

    if (tcpServer->listen(QHostAddress::Any, 12345)) {
        qDebug() << " Server is listening on port 12345";
    } else {
        qDebug() << "Server failed to start:" << tcpServer->errorString();
    }
}

void Server::onNewConnection() {
    QTcpSocket *client = tcpServer->nextPendingConnection();
    connect(client, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, [this, client]() {
        QString roomKey = clientRoomMap.value(client);
        if (rooms.contains(roomKey)) {
            rooms[roomKey].clients.removeAll(client);
            qDebug() << " Client disconnected from room:" << roomKey;
        }
        clientRoomMap.remove(client);
        client->deleteLater();
    });
}

void Server::onReadyRead() {
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    while (client->canReadLine()) {
        QByteArray data = client->readLine().trimmed();
        QList<QByteArray> parts = data.split('|');
        if (parts.isEmpty()) continue;

        QString command = parts[0];

        if (command == "AUTH" && parts.size() >= 2) {
            QString roomKey = parts[1];

            if (!rooms.contains(roomKey)) {
                rooms[roomKey] = Room();
                qDebug() << " Created new room:" << roomKey;
            }

            if (!rooms[roomKey].clients.contains(client)) {
                rooms[roomKey].clients.append(client);
            }

            clientRoomMap[client] = roomKey;
            client->write("AUTH_OK\n");
            qDebug() << " Client joined room:" << roomKey;

        } else if (command == "MSG" && parts.size() >= 4) {
            QString sender = parts[1];
            QString roomKey = parts[2];
            QString message = parts[3];

            if (!rooms.contains(roomKey)) {
                client->write("ERROR|Room not found\n");
                return;
            }

            qDebug() << "📨 Received message from" << sender << "in room" << roomKey << ":" << message;

            for (QTcpSocket *c : rooms[roomKey].clients) {
                if (c != client && c->state() == QAbstractSocket::ConnectedState) {
                    c->write("MSG|" + sender.toUtf8() + "|" + roomKey.toUtf8() + "|" + message.toUtf8() + "\n");
                }
            }

        } else if (command == "FILE" && parts.size() >= 5) {
            QString sender = parts[1];
            QString roomKey = parts[2];
            QString fileName = parts[3];
            QByteArray fileData = parts[4];

            if (!rooms.contains(roomKey)) {
                client->write("ERROR|Room not found\n");
                return;
            }

            for (QTcpSocket *c : rooms[roomKey].clients) {
                if (c != client && c->state() == QAbstractSocket::ConnectedState) {
                    QByteArray packet = "FILE|" + sender.toUtf8() + "|" + roomKey.toUtf8() + "|" + fileName.toUtf8() + "|" + fileData + "\n";
                    c->write(packet);
                }
            }

        } else {
            client->write("ERROR|Invalid command\n");
        }
    }
}
