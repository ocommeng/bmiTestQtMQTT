#include "testwidget1.h"
#include <QLoggingCategory>
#include <QFile>


#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    TestWidget1 w;
    w.show();
    return a.exec();
}
