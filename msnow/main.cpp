#include "test.h"
#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Company");
    QCoreApplication::setApplicationName("snow");
    QString strKey = QCoreApplication::organizationName() + QCoreApplication::applicationName();

    QSharedMemory shamem(strKey);
    if(!shamem.create(512, QSharedMemory::ReadWrite))
    {
        exit(0);
    }

    test w;
 //   w.hide();
    w.show();

    w.hide();
    return a.exec();
}
