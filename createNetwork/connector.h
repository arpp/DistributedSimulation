#ifndef CONNECTOR_H
#define CONNECTOR_H
#include "connections.h"
#include <QString>
#include <QTcpSocket>
#include <vector>

class connector
{
public:
    connector(QString filename);
    void begin();
    std::vector<QPair<int, QTcpSocket*> > getReceivers();
    std::vector<QPair<int, QTcpSocket*> > getSenders();
private:
    Connections *c;
    std::vector<QPair<int, QTcpSocket*> > receivers;
    std::vector<QPair<int, QTcpSocket*> > senders;

};

#endif // CONNECTOR_H
