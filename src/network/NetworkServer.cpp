#include "NetworkServer.h"
#include "NetworkTypes.h"

NetworkServer::NetworkServer()
{
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(broadcastAd()));
    m_timer->start(BROADCAST_FREQ);

}

NetworkServer::~NetworkServer()
{
    delete m_timer;
}

void NetworkServer::treatObject(const NetworkMessageAskFor &object)
{

}

void NetworkServer::broadcastAd()
{
    qDebug() << "test";
    NetworkMessageAd msg(QString("Flute a qui lira !"));
    QVariant v;
    v.setValue(msg);
    for (int i = 0; i<4; i++) {
        sendObject(v, m_udpSendingSocket, QHostAddress::Broadcast);
    }
}

void NetworkServer::newClient()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    m_clients.insert(/* TODO */ 1, client);

    connect(client, SIGNAL(readyRead()), this, SLOT(receivingTcpData()));
    connect(client, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
}
