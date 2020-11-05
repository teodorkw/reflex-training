#include "model.h"

Model::Model(int canvasSize) : canvasSize(canvasSize), diameter(50)
{
    srand(time(0));
    x  = rand() % static_cast<int>(canvasSize - diameter);
    y  = rand() % static_cast<int>(canvasSize - diameter);
    x_prev = x;
    y_prev = y;
}
