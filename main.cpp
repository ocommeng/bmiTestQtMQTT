#include "tableaudebord.h"
#include <QLoggingCategory>
#include <QFile>


#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    TableauDeBord w;
    w.show();
    return a.exec();
}
