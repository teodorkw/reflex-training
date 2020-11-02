#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>


class Canvas : public QWidget
{
    Q_OBJECT

    float radius;
    float x, y;
public:
    explicit Canvas(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *e)
    {
        QPainter painter(this);
        painter.drawEllipse(x, y, radius, radius);

    }

signals:

public slots:
};

#endif // CANVAS_H
