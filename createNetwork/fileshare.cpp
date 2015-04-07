#include "fileshare.h"
#include <QFile>

FileShare::FileShare()
{
}

void FileShare::sync(QString filename, int ownID, int masterID, QMap<int, QTcpSocket*> senders, QMap<int, QTcpSocket*> receivers) {
    if(masterID == ownID) {

    }

    else {
        if(receivers[masterID]->waitForReadyRead()) {
            char buffer[1024] = {0};
            receivers[masterID]->read(buffer, receivers[masterID]->bytesAvailable());
            //QTextStream(stdout) << "File size is: " << buffer << "\n";
            QString si(buffer);
            int size = si.toInt();
            int s = 0;
            QFile newFile(filename);
            if(newFile.open(QIODevice::WriteOnly)) {
                while(s<size){
                    if(receivers[masterID]->waitForReadyRead()) {
                        char buffer[32768] = {0};
                        receivers[masterID]->read(buffer, receivers[masterID]->bytesAvailable());
                        s+=strlen(buffer);
                        newFile.write(buffer);
                    }
                }
                QTextStream(stdout) << "File has been read. Size is: " << s << "\n";
                newFile.close();
            }
        }
    }
}
