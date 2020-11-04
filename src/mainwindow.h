#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTextEdit>
#include <QMessageBox>

#include "canvas.h"
#include "controls.h"
#include "model.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum State
    {
        IDLE, PREPARE, GAME
    }state;

    Canvas *canvas;
    QTextEdit *edit;
    Controls *controls;

    Model model;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
signals:
    void setXY(float x, float y);
    void operate(bool o);
public slots:
    void reportHit();
    void prepare();     // after clicking Start button

};

#endif // MAINWINDOW_H
