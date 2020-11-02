#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    canvas = findChild<Canvas*>("canvas");
    edit = findChild<QTextEdit*>("textEdit");

    connect(canvas, &Canvas::hit, this, &MainWindow::writeHitTime); // stary sposob nie dziala
}

MainWindow::~MainWindow()
{
    delete ui;
}
