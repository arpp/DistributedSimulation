#ifndef FILESHARE_H
#define FILESHARE_H
#include <QString>
#include <QMap>
#include <QTcpSocket>

class FileShare
{
public:
    FileShare();
    void sync(QString filename, int ownID, int masterID, QMap<int, QTcpSocket*> receivers, QMap<int, QTcpSocket*> senders);
};

#endif // FILESHARE_H
