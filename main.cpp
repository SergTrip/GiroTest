#include "girotestwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GiroTestWidget w;
    w.show();

    return a.exec();
}
