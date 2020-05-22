#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QDialog>

namespace Ui {
class Histogram;
}

class Histogram : public QDialog
{
    Q_OBJECT

public:
    explicit Histogram(QWidget *parent = 0);
    void setData(const QVector<double> &x1, const QVector<double> &y1, int index);
    ~Histogram();

private slots:

    void on_checkBlue_clicked(bool);

    void on_checkGreen_clicked(bool);

    void on_checkRed_clicked(bool );

    void on_checkGS_clicked(bool );

private:
    Ui::Histogram *ui;

    void init();
    void calculate();
};

#endif // HISTOGRAM_H
