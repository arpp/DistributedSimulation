#include "fileshare.h"
#include "blockreader.h"
#include "blockwriter.h"
#include <QFile>
#include <QFileInfo>

FileShare::FileShare()
{
}

void FileShare::sync(QString filename, int ownID, int masterID, QMap<int, QTcpSocket*> senders, QMap<int, QTcpSocket*> receivers) {
    if(masterID == ownID) {
        QMap<int, QTcpSocket*>::iterator siter;
        for(siter = senders.begin(); siter != senders.end(); siter++) {
            QFile inputFile(filename);
            if(inputFile.open(QIODevice::ReadOnly)) {

                QFileInfo fileinfo(inputFile.fileName() + QString::number(siter.key()));
//                QByteArray filesize;
//                filesize.append(QByteArray::number((qint32)fileinfo.size()));
//                QTextStream(stdout) << filesize;
                int filesize = fileinfo.size();
                BlockWriter(siter.value()).stream() << filesize;

//                int tt = (siter.value())->write(filesize);
//                (siter.value())->waitForBytesWritten();
                QTextStream(stdout) << "Size sent: " << filesize << "\n";
                int s=0;
                while (!inputFile.atEnd())
                {
                    QByteArray rawFile;
                    rawFile = inputFile.read(32768);
//                    tt = (siter.value())->write(rawFile);
//                    (siter.value())->waitForBytesWritten();
                    BlockWriter(siter.value()).stream() << rawFile;
                    qDebug() << "ToSend"<<rawFile.size();
                    s+=rawFile.size();
                }

                QTextStream(stdout) << "File has been sent\n";
            }
        }

    }

    else {
        if(true) {
//            receivers[masterID]->waitForReadyRead();
//            char buffer[1024] = {0};
            int size;
            BlockReader(receivers[masterID]).stream() >> size;
//            receivers[masterID]->read(buffer, receivers[masterID]->bytesAvailable());
            QTextStream(stdout) << "File size is: " << size << "\n";
//            QString si(buffer);
//            int size = si.toInt();
            int s = 0;
            QFile newFile(filename);
            if(newFile.open(QIODevice::WriteOnly)) {
                while(s<size){
//                    if(receivers[masterID]->waitForReadyRead()) {
//                        char buffer[32768] = {0};
//                        receivers[masterID]->read(buffer, size-s);
                        QByteArray buffer;
                        BlockReader(receivers[masterID]).stream() >> buffer;
                        s+=buffer.size();
                        newFile.write(buffer);
//                    }
                }
                QTextStream(stdout) << "File has been received. Size is: " << s << "\n";
                newFile.close();
            }
        }
        QTextStream(stdout) << "Waiting1\n";
    }
}
