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
    QPushButton *saveButton;
    QPushButton *plotButton;

public:
    explicit Controls(QWidget *parent = 0);
    ~Controls();

private:
    Ui::Controls *ui;

signals:
    started();
    stopped();
    saved();
};

#endif // CONTROLS_H
