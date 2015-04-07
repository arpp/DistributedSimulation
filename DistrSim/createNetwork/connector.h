#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "connections.h"
#include <QString>
#include <QTcpSocket>
#include <QMap>
#include <vector>

class connector
{
public:
    connector(QString filename);
    void begin();
    QMap<int, QTcpSocket*> getReceivers();
    QMap<int, QTcpSocket*> getSenders();
    int getOwnID();
private:
    Connections *c;
    QMap<int, QTcpSocket*> receivers;
    QMap<int, QTcpSocket*> senders;
//    std::vector<QPair<int, QTcpSocket*> > receivers;
//    std::vector<QPair<int, QTcpSocket*> > senders;

};

#endif // CONNECTOR_H
