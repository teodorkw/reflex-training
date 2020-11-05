#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    state(IDLE),
    model(500)
{
    ui->setupUi(this);

    canvas = findChild<Canvas*>("canvas");
    edit = findChild<QTextEdit*>("textEdit");
    controls = findChild<Controls*>("controls");

    connect(canvas, &Canvas::hit, this, &MainWindow::reportHit); // stary sposob nie dziala
    connect(this, &MainWindow::setXY, canvas, &Canvas::setXY_slot);
    connect(this, &MainWindow::operate, canvas, &Canvas::switchOperate);

    connect(controls, &Controls::started, this, &MainWindow::started);
    connect(controls, &Controls::stopped, this, &MainWindow::stopped);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reportHit()
{
    switch(state)
    {
    case IDLE:
        break;
    case PREPARE:
        model.startTimer();
        emit setXY(model.getX(), model.getY(), model.getDiameter());
        state = RUNNING;
        break;
    case RUNNING:
        model.stopTimer();
        model.startTimer();
        emit setXY(model.getX(), model.getY(), model.getDiameter());
        edit->append("Czas: " + QString::number(model.getLastTime()));
        break;
    }


}
void MainWindow::started()
{
    if(state == IDLE)
    {
        state = PREPARE;
        emit operate(true);
        emit setXY(model.getX(), model.getY(), model.getDiameter());
    }
}
void MainWindow::stopped()
{
    state = IDLE;
    emit operate(false);
}

/*void MainWindow::startStop()
{
    QMessageBox Msgbox;
    Msgbox.setText("test");
    Msgbox.exec();
}*/
