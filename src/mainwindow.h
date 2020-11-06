#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWindow>
#include <QPainter>
#include <QTextEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>

#include "canvas.h"
#include "controls.h"
#include "model.h"

QT_CHARTS_USE_NAMESPACE

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
    void reset();
    void plotted();
};

#endif // MAINWINDOW_H
