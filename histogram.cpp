#include "histogram.h"
#include "ui_histogram.h"

Histogram::Histogram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Histogram)
{
    ui->setupUi(this);
    init();
}

Histogram::~Histogram()
{
    delete ui;
}

void Histogram::setData(const QVector<double> &x, const QVector<double> &y,int index)
{
    ui->customPlot->graph(index)->setData(x, y);
    ui->customPlot->replot();
}

void Histogram::init() {
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();
    ui->customPlot->addGraph();

    ui->customPlot->graph(0)->setPen(QPen(QColor(100, 100, 100)));
    ui->customPlot->graph(1)->setPen(QPen(QColor(255, 100, 0)));
    ui->customPlot->graph(2)->setPen(QPen(QColor(0, 255, 100)));
    ui->customPlot->graph(3)->setPen(QPen(QColor(0, 100, 255)));

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->xAxis->setRange(0, 255);
    ui->customPlot->yAxis->setRange(0, 255);
    ui->customPlot->replot();
}

void Histogram::calculate() {
    for (int i = 0; i < 4; ++i) {
        if(ui->customPlot->graph(i)->visible()) {
            ui->customPlot->graph(i)->rescaleValueAxis();
        }
    }
}

void Histogram::on_checkBlue_clicked(bool checked)
{
    ui->customPlot->graph(3)->setVisible(checked);
    calculate();
    ui->customPlot->replot();
}

void Histogram::on_checkGreen_clicked(bool checked)
{
    ui->customPlot->graph(2)->setVisible(checked);
    calculate();
    ui->customPlot->replot();
}

void Histogram::on_checkRed_clicked(bool checked)
{
    ui->customPlot->graph(1)->setVisible(checked);
    calculate();
    ui->customPlot->replot();
}

void Histogram::on_checkGS_clicked(bool checked)
{
    ui->customPlot->graph(0)->setVisible(checked);
    calculate();
    ui->customPlot->replot();
}
