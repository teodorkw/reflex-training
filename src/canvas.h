#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>



class Canvas : public QWidget
{
    Q_OBJECT

    float diameter;
    float x, y;
    bool operate;

public:
    explicit Canvas(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e)
    {
        if(operate)
        {
            QPainter painter(this);
            painter.drawEllipse(x, y, diameter, diameter);
        }
    }

    void mousePressEvent(QMouseEvent *e)
    {
        if(operate && e->button() == Qt::LeftButton)
        {

            if(sqrt(pow(x + diameter/2 - e->x(), 2) + pow(y + diameter/2 - e->y(), 2)) <= diameter/2)
            {

                emit hit();
            }
            update();
        }
    }

signals:
    void hit();      // propagates distance
public slots:
    void setXY_slot(float xx, float yy)
    {
        x = xx;
        y = yy;
    }
    void switchOperate(bool o)
    {
        operate = o;
        update();
    }
};

#endif // CANVAS_H
