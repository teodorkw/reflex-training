#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MSGBOX(title, text) \
    QMessageBox Msgbox; \
    Msgbox.setWindowTitle(title); \
    Msgbox.setText(text); \
    Msgbox.exec(); \

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
    connect(controls, &Controls::saved, this, &MainWindow::saved);
    connect(controls, &Controls::reset, this, &MainWindow::reset);
    connect(controls, &Controls::plotted, this, &MainWindow::plotted);
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
        edit->append("Time: " + QString::number(model.getLastTime()) + ", distance: " + QString::number(model.getLastDistance()));
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
void MainWindow::saved()
{
    state = IDLE;
    QString fName = QFileDialog::getSaveFileName(nullptr, "Save", ".", "CSV file (*.csv);;All files (*.*)");
    model.saveFile(fName.toStdString());
}
void MainWindow::reset()
{
    state = IDLE;
    emit operate(false);
    model.clearMeasures();
    edit->clear();

}
void MainWindow::plotted()
{
    state = IDLE;
    emit operate(false);

    QLineSeries *times = new QLineSeries();
    QLineSeries *distances = new QLineSeries();
    QScatterSeries *s3 = new QScatterSeries();

    auto t = model.getTimes();
    auto d = model.getDistances();
    int idx = 0;
    for(int i = 0; i < t.size(); ++i)
    {
        times->append(i + 1, t[i]);
        distances->append(i + 1, d[i]);
        s3->append(d[i], t[i]);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Stats");
    QValueAxis *axisX = new QValueAxis;
    axisX->setTitleText("hit number");
    chart->addAxis(axisX, Qt::AlignBottom);

    chart->addSeries(times);
    chart->addSeries(distances);
    //chart->addSeries(s3);

    QValueAxis *axisT = new QValueAxis;
    axisT->setTitleText("time [s]");
    axisT->setLinePenColor(times->pen().color());
    axisT->setTitleBrush(QBrush(times->pen().color()));
    chart->addAxis(axisT, Qt::AlignLeft);
    times->attachAxis(axisX);
    times->attachAxis(axisT);

    QValueAxis *axisD = new QValueAxis;
    axisD->setTitleText("distance from previous target [px]");
    axisD->setLinePenColor(distances->pen().color());
    axisD->setTitleBrush(QBrush(distances->pen().color()));
    chart->addAxis(axisD, Qt::AlignRight);
    distances->attachAxis(axisX);
    distances->attachAxis(axisD);

    /*QValueAxis *axisS3 = new QValueAxis;
    axisS3->setLinePenColor(s3->pen().color());
    chart->addAxis(axisS3, Qt::AlignRight);
    s3->attachAxis(axisX);
    s3->attachAxis(axisS3);*/


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow(this);    // on stack closes immediately
    window->setCentralWidget(chartView);
    window->resize(800, 600);
    window->show();
}

