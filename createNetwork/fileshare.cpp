#include "fileshare.h"
#include <QFile>
#include <QFileInfo>

FileShare::FileShare()
{
}

void FileShare::sync(QString filename, int ownID, int masterID, QMap<int, QTcpSocket*> senders, QMap<int, QTcpSocket*> receivers) {
    if(masterID == ownID) {
        QFile inputFile(filename);

        if(inputFile.open(QIODevice::ReadOnly)) {

            QFileInfo fileinfo(inputFile.fileName());
            int sizeofFile = fileinfo.size();
            QByteArray filesize;
            filesize.append(QByteArray::number((qint32)fileinfo.size()));
            QTextStream(stdout) << filesize;

            int tt = senders[0]->write(filesize);
            senders[0]->waitForBytesWritten();
            QTextStream(stdout) << "Size sent: " << tt << "\n";
            int s=0;
            while (!inputFile.atEnd())
            {
                QByteArray rawFile;
                rawFile = inputFile.read(32768);
                tt = senders[0]->write(rawFile);
                senders[0]->waitForBytesWritten();
                qDebug() << "ToSend"<<rawFile.size();
                s+=rawFile.size();
            }

            QTextStream(stdout) << "File has been sent\n";
        }

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
