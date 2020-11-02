#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include <cstdlib>

class Canvas : public QWidget
{
    Q_OBJECT

    float diameter;
    float x, y;


public:
    explicit Canvas(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e)
    {
        QPainter painter(this);
        painter.drawEllipse(x, y, diameter, diameter);
    }

    void mousePressEvent(QMouseEvent *e)
    {
        if(e->button() == Qt::LeftButton)
        {
            if(sqrt(pow(x + diameter/2 - e->x(), 2) + pow(y + diameter/2 - e->y(), 2)) <= diameter/2)
            {
                x = rand() % static_cast<int>(this->width() - diameter);
                y = rand() % static_cast<int>(this->height() - diameter);
                emit hit(123);
            }
            update();
        }
    }

signals:
    void hit(float t);
public slots:
};

#endif // CANVAS_H
