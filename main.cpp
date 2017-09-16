#include "josephcircle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JosephCircle w;
    w.show();

    return a.exec();
}
