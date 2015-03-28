#include <QCoreApplication>
#include "eventA.h"
#include "mnode.h"

int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);
    MNode mn;
    EventA e;
    mn.insertEvent(&e);
//    return a.exec();
}
