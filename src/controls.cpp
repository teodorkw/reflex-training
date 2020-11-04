#include "controls.h"
#include "ui_controls.h"

Controls::Controls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Controls)
{
    ui->setupUi(this);

    startButton = findChild<QPushButton*>("startButton");
    stopButton = findChild<QPushButton*>("stopButton");
    plotButton = findChild<QPushButton*>("plotButton");

    connect(startButton, &QPushButton::clicked, this, &Controls::started);
    connect(stopButton, &QPushButton::clicked, this, &Controls::stopped);
}

Controls::~Controls()
{
    delete ui;
}
