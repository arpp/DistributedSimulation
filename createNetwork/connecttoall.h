#ifndef CONNECTTOALL_H
#define CONNECTTOALL_H
#include "connections.h"
#include "client.h"
#include <QObject>
#include <QThread>
#include <vector>
#include <QString>

class ConnectToAll: public QObject
{
Q_OBJECT
public:
    ConnectToAll(QObject* parent=0);
    ConnectToAll(Connections *c, QString ownIP, QObject* parent=0);
    ~ConnectToAll();
public slots:
    void startConnecting();
    void clientConnectedPeace();
signals:
    void createConnections();
private:
    Connections *c;
    QString ownIP;
    std::vector<Client*> clients;
    int count;
};

#endif // CONNECTTOALL_H
