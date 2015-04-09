#ifndef BLOCKWRITER_H
#define BLOCKWRITER_H

#include <QIODevice>
#include <QDataStream>
#include <QBuffer>

class BlockWriter
{
public:
    BlockWriter(QIODevice *io)
    {
        buffer.open(QIODevice::WriteOnly);
        this->io = io;
        _stream.setVersion(QDataStream::Qt_5_2);
        _stream.setDevice(&buffer);

        // Placeholder for the size. We will get the value
        // at the end.
        _stream << quint64(0);
    }

    ~BlockWriter()
    {
        // Write the real size.
        _stream.device()->seek(0);
        _stream << (quint64) buffer.size();

        // Flush to the device.
        io->write(buffer.buffer());
    }

    QDataStream &stream()
    {
        return _stream;
    }

private:
    QBuffer buffer;
    QDataStream _stream;
    QIODevice *io;
};

#endif // BLOCKWRITER_H
