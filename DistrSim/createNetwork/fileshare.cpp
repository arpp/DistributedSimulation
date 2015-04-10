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

        QTextStream(stderr) << "beginning transfer" << "";
        QMap<int, QTcpSocket*>::iterator siter;
        for(siter = senders.begin(); siter != senders.end(); siter++) {
            QFile inputFile(filename + QString::number(siter.key()));
            qDebug() << "Sending " << filename + QString::number(siter.key()) << "";
            if(inputFile.open(QIODevice::ReadOnly)) {

                    QByteArray rawFile = inputFile.readAll();
                    QString buffer(rawFile);
                    qDebug() << buffer;


                    BlockWriter(siter.value()).stream() << buffer;
                    bool sent = (siter.value())->waitForBytesWritten();
                    QTextStream(stderr) << "Size sent: " << rawFile.size() << "";
//                }

                QTextStream(stderr) << "File has been sent";
                inputFile.close();
            }
        }

    }

    else {
        QString filedata;
        BlockReader(receivers[masterID]).stream() >> filedata;

        QFile file(filename);
        if(file.open(QIODevice::WriteOnly)) {
            QByteArray *bytes = new QByteArray;
            bytes->append(filedata);
            file.write(*bytes);
            file.close();
        }
        else {
            qDebug() << "ERROR: could not open "+filename+" to write" ;
            exit(-1);
        }
    }
}
