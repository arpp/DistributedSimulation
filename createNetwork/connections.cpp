#include "connections.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <vector>

Connections::Connections(QObject* parent=0): QObject(parent) {

}

Connections::Connections(Connections &c): QObject(0){
    this->ip_adds = c.ip_adds;
    this->ports = c.ports;
    this->m = c.m;
    this->connected = c.connected;
}

Connections::Connections(QString filename): QObject(0) {
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)) {
        std::cout << "Error reading file\n";
    }
    QTextStream fin(&file);
    while(!fin.atEnd()) {
        QString line = fin.readLine();
        QStringList fields = line.split(" ");

        ip_adds.push_back(fields[0]);
        ports.push_back(fields[1].toInt());
        connected.push_back(false);
        m[fields[0]] = fields[1].toInt();
    }
    QTextStream(stdout) << "connection details read from " << filename << "\n";
    file.close();
}

void Connections::addConnection(QString ip, int port) {
    ip_adds.push_back(ip);
    ports.push_back(port);
    connected.push_back(false);
}

int Connections::getPort(int l){
    return ports[l];
}

QString Connections::getIP(int l) {
    return ip_adds[l];
}

int Connections::getPort(QString ip) {
    return m[ip];
}

bool Connections::isConnected(int l) {
    return connected[l];
}

unsigned int Connections::length() {
    return ip_adds.size();
}

void Connections::printConnections() {
    QTextStream(stdout) << "IP_ADDR\t\tPORT\n";
    for (int i=0; i<ip_adds.size(); i++) {
        QTextStream(stdout) << ip_adds[i] << "\t" << ports[i] << "\n";
    }
}

Connections::~Connections() {

}
