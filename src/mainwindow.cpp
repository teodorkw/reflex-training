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

    connect(controls, &Controls::started, this, &MainWindow::prepare);
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
        emit setXY(model.getX(), model.getY());

        state = GAME;
        break;
    case GAME:
        model.stopTimer();
        model.startTimer();
        emit setXY(model.getX(), model.getY());
        edit->append("Czas: " + QString::number(model.getLastTime()));
        break;
    }


}
void MainWindow::prepare()
{
    if(state == IDLE)
    {
        state = PREPARE;
        emit operate(true);
    }
}

/*void MainWindow::startStop()
{
    QMessageBox Msgbox;
    Msgbox.setText("test");
    Msgbox.exec();
}*/
