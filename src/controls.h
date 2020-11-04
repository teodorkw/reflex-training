#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class Controls;
}

class Controls : public QWidget
{
    Q_OBJECT

    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *plotButton;

public:
    explicit Controls(QWidget *parent = 0);
    ~Controls();

private:
    Ui::Controls *ui;

signals:
    started();
    stopped();
};

#endif // CONTROLS_H
