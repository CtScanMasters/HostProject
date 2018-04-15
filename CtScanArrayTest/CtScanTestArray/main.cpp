#include <QCoreApplication>
#include "Kernel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Kernel kernel;

    return a.exec();
}
