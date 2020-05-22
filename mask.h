#ifndef MASK_H
#define MASK_H

#include <QDialog>
#include <QTableWidget>
#include <QComboBox>
namespace Ui {
class Mask;
}

class Mask : public QDialog
{
    Q_OBJECT

public:
    explicit Mask(QWidget *parent = 0);
    ~Mask();
    QTableWidget* tableWidget;
    QComboBox *boxAlpha, *boxBeta;
    QString alphaLabel;
    QString betaLabel;
    int lastCenterRow;
    int lastCenterColumn;

private slots:
    void on_spinBox_columns_valueChanged(int arg1);
    void on_boxAlpha_Changed(QString s);
    void on_boxBeta_Changed(QString s);
    void on_spinBox_rows_valueChanged(int arg1);
    void setCenter(int, int);

private:
    Ui::Mask *ui;
    void init();
    void initAlphaBeta();
    void insertElements(int, int);
};

#endif // MASK_H
