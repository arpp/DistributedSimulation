#ifndef CONNECTIONS_H
#define CONNECTIONS_H
#include <vector>
#include <string>
#include <QString>
#include <map>
#include <QObject>

class Connections: public QObject {
public:
    Connections(QObject*);
    Connections(QString filename);
    Connections(Connections &c);
    void addConnection(QString ip, int port);
    QString getIP(int l);
    int getPort(int l);
    int getPort(QString ip);
    bool isConnected(int l);
    unsigned int length();
    void printConnections();
    ~Connections();
private:
    std::vector<QString> ip_adds;
    std::vector<int> ports;
    std::vector<bool> connected;
    std::map<QString, int> m;

};

#endif // CONNECTIONS_H
