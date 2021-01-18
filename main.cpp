#include "drawable_graphui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    drawable_graphUI w;
    w.show();
    return a.exec();
}
