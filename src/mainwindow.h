#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>

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
        IDLE, PREPARE, RUNNING
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
    void setXY(float x, float y, float d);
    void operate(bool o);
public slots:
    void reportHit();
    void started();     // after clicking Start button
    void stopped();
    void saved();
};

#endif // MAINWINDOW_H
