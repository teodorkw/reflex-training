#include "canvas.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent), diameter(100), operate(false), firstHit(true)
{


    setFixedSize(500, 500);


}
