#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent), diameter(100), x(100), y(100)
{
    srand(time(0));
}
