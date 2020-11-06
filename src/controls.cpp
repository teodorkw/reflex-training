#include "controls.h"
#include "ui_controls.h"

Controls::Controls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Controls)
{
    ui->setupUi(this);

    startButton = findChild<QPushButton*>("startButton");
    stopButton = findChild<QPushButton*>("stopButton");
    saveButton = findChild<QPushButton*>("saveButton");
    resetButton = findChild<QPushButton*>("resetButton");
    plotButton = findChild<QPushButton*>("plotButton");

    connect(startButton, &QPushButton::clicked, this, &Controls::started);
    connect(stopButton, &QPushButton::clicked, this, &Controls::stopped);
    connect(saveButton, &QPushButton::clicked, this, &Controls::saved);
    connect(resetButton, &QPushButton::clicked, this, &Controls::reset);
    connect(plotButton, &QPushButton::clicked, this, &Controls::plotted);
}

Controls::~Controls()
{
    delete ui;
}
