#include <QtGui/QApplication>
#include "tester.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tester w;
    w.show();

    return a.exec();
}
