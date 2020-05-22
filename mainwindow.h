#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <queue>

#include "dlgimage.h"
#include "histogram.h"
#include "mask.h"

typedef struct Conv{
    unsigned char *data;
    unsigned char *data2;
    int width;
    int height;
} Conv_t;

typedef struct Labl{
    int cc;
    int rr;
    std::queue<std::pair<int,int>> * t;
    long long label;
    int width;
    int height;
    unsigned char *data;
    unsigned char *data2;
    int r;
    int g;
    int b;
} Labl_t;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QMdiArea *MdiArea;
    QTableWidget *tableWidget;

public:
    explicit MainWindow(QWidget *parent = 0);
    unsigned char * firstIm;
    int widthIm;
    int heightIm;
    bool updateIm;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Mask  *mask;
    dlgImage *getActiveWindow();
    void setStatus(QString str);
    void transHistogram(int xmin, int xmax);
    void convolutionAlphaBeta_SumProduct(Conv_t*);
    void convolutionAlphaBeta_SumSum(Conv_t*);
    void convolutionAlphaBeta_SumDiff(Conv_t*);
    void convolutionAlphaBeta_MinProduct(Conv_t*);
    void convolutionAlphaBeta_MinSum(Conv_t*);
    void convolutionAlphaBeta_MinDiff(Conv_t*);
    void convolutionAlphaBeta_MaxProduct(Conv_t*);
    void convolutionAlphaBeta_MaxSum(Conv_t*);
    void convolutionAlphaBeta_MaxDiff(Conv_t*);
    void convolutionAlphaBeta_MedianProduct(Conv_t*);
    void convolutionAlphaBeta_MedianSum(Conv_t*);
    void convolutionAlphaBeta_MedianDiff(Conv_t*);
    void checkNeighbourhood(Labl_t *);
    void checkNeighbourhoodM(Labl_t *);


private slots:
    void openImage();
    void saveImageAs();
    void duplicateWindow();
    void grayscale();
    void trans();
    void mascara();
    void convolution();
    void opSum();
    void opDiff();
    void opProduct();
    void opMin();
    void opMax();
    void opComplement();
    void firstImage();
    void ApplyThresholding();
    void ApplyThresholdingValue();
    void calculateHistogram();
    void labelingNormal();
    void labelingValue();
    void labelingM();
    void watershed();

};

#endif // MAINWINDOW_H



















