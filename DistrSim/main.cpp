#include <QCoreApplication>
#include "mnode.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MNode *n = new MNode();
    n->beginSimulation();

    return a.exec();
}
