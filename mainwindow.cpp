#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QPixmap>
#include <QMdiSubWindow>
#include <QInputDialog>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>
#include <string>
#include <QMessageBox>

#define I -1
#define W  0
#define Q -2
#define M -3

//#include "dlgimage.h"

using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MdiArea=ui->mdiArea;

    connect(ui->action_Open,SIGNAL(triggered()),this,SLOT(openImage()));
    connect(ui->action_Save_As,SIGNAL(triggered()),this,SLOT(saveImageAs()));
    connect(ui->action_Exit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionDuplicate,SIGNAL(triggered()),this,SLOT(duplicateWindow()));
    connect(ui->action_Grayscale,SIGNAL(triggered()),this,SLOT(grayscale()));
    connect(ui->actionNew_Histogram,SIGNAL(triggered()),this,SLOT(trans()));
    connect(ui->actionNew_Mask,SIGNAL(triggered()),this,SLOT(mascara()));
    connect(ui->actionApply_Convolution,SIGNAL(triggered()),this,SLOT(convolution()));

    connect(ui->actionFirstIm,SIGNAL(triggered()),this,SLOT(firstImage()));
    connect(ui->actionOpSum,SIGNAL(triggered()),this,SLOT(opSum()));
    connect(ui->actionOpMin,SIGNAL(triggered()),this,SLOT(opMin()));
    connect(ui->actionOpMax,SIGNAL(triggered()),this,SLOT(opMax()));
    connect(ui->actionOpDiff,SIGNAL(triggered()),this,SLOT(opDiff()));
    connect(ui->actionOpComplement,SIGNAL(triggered()),this,SLOT(opComplement()));
    connect(ui->actionOpProduct,SIGNAL(triggered()),this,SLOT(opProduct()));
    connect(ui->actionNormal,SIGNAL(triggered()),this,SLOT(ApplyThresholding()));
    connect(ui->actionValue,SIGNAL(triggered()),this,SLOT(ApplyThresholdingValue()));
    connect(ui->actionLabelingNormal,SIGNAL(triggered()),this,SLOT(labelingNormal()));
    connect(ui->actionLabelingValue,SIGNAL(triggered()),this,SLOT(labelingValue()));
    connect(ui->actionHistogram,SIGNAL(triggered()),this,SLOT(calculateHistogram()));

    // showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//Original
void MainWindow::firstImage() {

    dlgImage *img = getActiveWindow();
    if (img) {

        unsigned char* data = img->getImageRGB()->getData();
        firstIm = data;
        widthIm = img->getImageRGB()->getWidth();
        heightIm = img->getImageRGB()->getHeight();
    }

}
void MainWindow::openImage() {
    QFileDialog selectFiles(this);
    QStringList files;
    QString file;


    selectFiles.setFileMode(QFileDialog::ExistingFile);
    selectFiles.setNameFilter(tr("Image (* jpeg *.jpg *.png *.bmp)"));
    selectFiles.setAcceptMode(QFileDialog::AcceptOpen);

    if (selectFiles.exec()) {
        files = selectFiles.selectedFiles();
        file = files.at(0);
        setStatus("Loading "+file+"...");


        dlgImage *newImg;
        newImg = new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(file);

        QMdiSubWindow *t = MdiArea->addSubWindow(newImg);
        t->widget()->adjustSize();
        newImg->show();
    }
}
void MainWindow::calculateHistogram( ) {
    dlgImage *img = getActiveWindow();
    if (img) {
        unsigned char* data = img->getImageRGB()->getData();
        int height = img->getImageRGB()->getHeight();
        int width = img->getImageRGB()->getWidth();

        if (data) {
            int i, j;
            int tmp, r, g, b, max = 1;
            int *imO;
            QVector<double> x(256),
                    yGray(256),
                    yRed(256),
                    yGreen(256),
                    yBlue(256);

            Histogram *histograma;
            histograma = new Histogram(ui->mdiArea);
            QMdiSubWindow *t = MdiArea->addSubWindow(histograma);
            t->widget()->adjustSize();
            histograma->show();
            for (i = 0; i < 256; ++i)
                x[i] = i;

            for (i = 0; i < 256; ++i)
                yGray[i] = yRed[i] = yGreen[i] = yBlue[i] = 0;

            for (i = 0, imO = (int*) data; i < height; i++) {
                for (j = 0; j < width; j++,imO++) {

                    r = ( (*imO) >> 16 ) & 0xff;
                    g = ( (*imO) >> 8  ) & 0xff;
                    b = ( (*imO) >> 0  ) & 0xff;
                    tmp = ( ( 34*b + 55*g + 11*r )/100 ) & 0xff;
                    yGray[tmp] += 1;
                    yRed[r]    += 1;
                    yGreen[g]  += 1;
                    yBlue[b]   += 1;
                    max = max > yGray[tmp] ? max:yGray[tmp];
                    max = max > yRed[r]    ? max:yRed[r];
                    max = max > yGreen[g]  ? max:yGreen[g];
                    max = max > yBlue[b]   ? max:yBlue[b];
                }
            }

            for (i = 0; i < 256; ++i) {
                yGray[i]  = (100.0 * yGray[i]) /max;
                yRed[i]   = (100.0 * yRed[i])  /max;
                yGreen[i] = (100.0 * yGreen[i])/max;
                yBlue[i]  = (100.0 * yBlue[i]) /max;
            }
            histograma->setData(x, yGray, 0);
            histograma->setData(x, yRed,  1);
            histograma->setData(x, yGreen,2);
            histograma->setData(x, yBlue, 3);
        }
    }
}
void MainWindow::transHistogram(const int xmin, const int xmax) {
    dlgImage *img=getActiveWindow();
    if (img) {

        unsigned char* data = img->getImageRGB()->getData();
        int height = img->getImageRGB()->getHeight();
        int width = img->getImageRGB()->getWidth();

        if (data) {
            int i, j;
            int tmp, r, g, b, max = 1;
            int *imO;
            QVector<double> x(256),
                    yGray(256),
                    yRed(256),
                    yGreen(256),
                    yBlue(256);

            std::vector<int> red,
                    blue,
                    green,
                    gray;

            Histogram *histograma;
            histograma = new Histogram(ui->mdiArea);
            QMdiSubWindow *t = MdiArea->addSubWindow(histograma);
            t->widget()->adjustSize();
            histograma->show();
            for (i = 0; i < 256; ++i)
                x[i] = i;

            for (i = 0; i < 256; ++i)
                yGray[i] = yRed[i] = yGreen[i] = yBlue[i] = 0;

            for (i = 0, imO = (int*) data; i < height; i++) {
                for (j = 0; j < width; j++,imO++) {

                    r = ( (*imO) >> 16 ) & 0xff;
                    g = ( (*imO) >> 8  ) & 0xff;
                    b = ( (*imO) >> 0  ) & 0xff;
                    tmp = ( ( 34*b + 55*g + 11*r )/100 ) & 0xff;
                    // *imO = ( (*imO) & (0xff000000) )| (tmp<<16) | (tmp<<8) | (tmp);
                    yGray[tmp] += 1;
                    yRed[r]    += 1;
                    yGreen[g]  += 1;
                    yBlue[b]   += 1;

                    max = max > yGray[tmp] ? max:yGray[tmp];
                    max = max > yRed[r]    ? max:yRed[r];
                    max = max > yGreen[g]  ? max:yGreen[g];
                    max = max > yBlue[b]   ? max:yBlue[b];
                }
            }
            //Necesitamos encontrar el mínimo valor y máximo valor de color en cada canal distinto a cero.
            //Para eso recorremos las frecuencias de cada intensidad en "Y"
            //Así, si su valor es distinto a cero, implica que existe al menos una vez esa intensidad
            //Y agregamos el i correspondiente
            for (i = 0; i < 256; i++)
            {
                r = yRed[i];
                g = yGreen[i];
                b = yBlue[i];
                tmp = yGray[i];

                if(r != 0)
                    red.push_back(i);
                if(g != 0)
                    green.push_back(i);
                if(b != 0)
                    blue.push_back(i);
                if(tmp != 0)
                    gray.push_back(i);
            }

            int GrayMax,RedMax,GreenMax,BlueMax;
            int GrayMin,RedMin,GreenMin,BlueMin;

            //Asignamos el MIN y MAX
            GrayMin  = *std::min_element(gray.begin(),gray.end());
            RedMin   = *std::min_element(red.begin(),red.end());
            BlueMin  = *std::min_element(blue.begin(),blue.end());
            GreenMin = *std::min_element(green.begin(),green.end());
            GrayMax  = *std::max_element(gray.begin(),gray.end());
            RedMax   = *std::max_element(red.begin(),red.end());
            BlueMax  = *std::max_element(blue.begin(),blue.end());
            GreenMax = *std::max_element(green.begin(),green.end());

            std::cout<<"cdfGrayMin: "<<GrayMin<<" RedMin: "<<RedMin<<" BlueMin:"<<BlueMin<<" GreenMin:"<<GreenMin<<std::endl;
            std::cout<<"cdfGrayMax: "<<GrayMax<<" RedMax: "<<RedMax<<" BlueMax:"<<BlueMax<<" GreenMax:"<<GreenMax<<std::endl;
            int pixels = height * width;
            for (i = 0; i < 256; ++i)
                x[i] = i;

            for (i = 0; i < 256; ++i)
                yGray[i] = yRed[i] = yGreen[i] = yBlue[i] = 0;
            //Calculamos los nuevos valores de intensidad en cada canal
            max = 1;
            for (i = 0, imO = (int*) data; i < height; i++) {
                for (j = 0; j < width; j++,imO++) {

                    r = ( (*imO) >> 16 ) & 0xff;
                    g = ( (*imO) >> 8  ) & 0xff;
                    b = ( (*imO) >> 0  ) & 0xff;

                    r = (int)((r-xmin)*((double)(255)/(xmax-xmin))) + 0;
                    g = (int)((g-xmin)*((double)(255)/(xmax-xmin))) + 0;
                    b = (int)((b-xmin)*((double)(255)/(xmax-xmin))) + 0;

                    if ( r>255 ) r = 255;
                    if ( g>255 ) g = 255;
                    if ( b>255 ) b = 255;

                    if ( r<0 ) r = 0;
                    if ( g<0 ) g = 0;
                    if ( b<0 ) b = 0;

                    tmp = ( ( 34*b + 55*g + 11*r )/100 ) & 0xff;

                    *imO = ( (*imO) & (0xff000000) )| (tmp<<16) | (tmp<<8) | (tmp);

                    yGray[tmp] += 1;
                    yRed[r]    += 1;
                    yGreen[g]  += 1;
                    yBlue[b]   += 1;

                    max = max > yGray[tmp] ? max:yGray[tmp];
                    max = max > yRed[r]    ? max:yRed[r];
                    max = max > yGreen[g]  ? max:yGreen[g];
                    max = max > yBlue[b]   ? max:yBlue[b];
                }
            }
            for (i = 0; i < 256; ++i) {
                yGray[i]  = (100.0 * yGray[i]) /max;
                yRed[i]   = (100.0 * yRed[i])  /max;
                yGreen[i] = (100.0 * yGreen[i])/max;
                yBlue[i]  = (100.0 * yBlue[i]) /max;
            }

            histograma->setData(x, yGray, 0);
            histograma->setData(x, yRed,  1);
            histograma->setData(x, yGreen,2);
            histograma->setData(x, yBlue, 3);
        }
        img->update();
    }
}
void MainWindow::saveImageAs() {
    dlgImage *img=getActiveWindow();
    if (img) {
        QFileDialog selectFiles(this);
        QStringList files;
        QString file;


        selectFiles.setFileMode(QFileDialog::AnyFile);
        selectFiles.setNameFilter(tr("Imagen (* jpeg *.jpg *.png *.bmp)"));
        selectFiles.setAcceptMode(QFileDialog::AcceptSave);

        if (selectFiles.exec()) {
            files=selectFiles.selectedFiles();
            file=files.at(0);
            setStatus("Saving "+file+"...");

            img->saveImageAs(file);

        }
    }
}
void MainWindow::duplicateWindow() {
    dlgImage *img=getActiveWindow();
    if (img) {
        dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());
        MdiArea->addSubWindow(newImg);
        newImg->show();
        setStatus("Image "+img->getName()+" duplicated..");
    }
}
void MainWindow::grayscale() {
    dlgImage *img=getActiveWindow();
    if (img) {
        img->grayscale();
        setStatus("Image "+img->getName()+" grayscaled..");
    }
}
dlgImage *MainWindow::getActiveWindow() {
    QMdiSubWindow *sub=MdiArea->activeSubWindow();
    if (sub) {
        dlgImage *img;
        img=qobject_cast<dlgImage *>(sub->widget());
        return img;
    }
    setStatus("Select an image..");
    return NULL;
}
void MainWindow::setStatus(QString str) {
    ui->statusbar->showMessage(str);
}
void MainWindow::trans() {

    bool ok;
    int x = 0, x2 = 255;

    QInputDialog* inputDialog = new QInputDialog();
    inputDialog->setOptions(QInputDialog::NoButtons);

    QString text =  inputDialog->getText(NULL ,"Rango de histograma",
                                         "x:", QLineEdit::Normal,
                                         "100", &ok);

    if (ok && !text.isEmpty())
        x = stoi(text.toStdString());

    text =  inputDialog->getText(NULL ,"Rango de histograma",
                                 "X2:", QLineEdit::Normal,
                                 "200", &ok);

    if (ok && !text.isEmpty())
        x2 = stoi(text.toStdString());
    std::cout<<x <<" "<<x2<<std::endl;
    transHistogram(x, x2);
}
void MainWindow::mascara() {

    mask = new Mask( MdiArea );


    QMdiSubWindow *t = MdiArea->addSubWindow(mask);
    t->widget()->adjustSize();
    mask->show();
}
void MainWindow::convolution() {

    dlgImage *img = getActiveWindow();

    tableWidget = mask->tableWidget;

    if (img) {
        setStatus("Image "+ img->getName() + " new convolution");
        /* dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());

        QMdiSubWindow *t = MdiArea->addSubWindow(newImg);
        t->widget()->adjustSize();
        newImg->show();
*/
        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {
            int i,j;
            int *imO,*im1;
            std::string alpha = mask->alphaLabel.toStdString();
            std::string beta = mask->betaLabel.toStdString();

            unsigned char *data2 = new unsigned char[4*width*height];

            for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ )
                    *im1 = *imO;

            /* alpha: min, max, med, sum(ya hecha) */
            /* beta: sum, resta, multiplicacion */

            Conv_t conv;

            conv.data = data;
            conv.data2 = data2;
            conv.width = width;
            conv.height = height;

            if ( alpha == "sum" && beta == "product" )    convolutionAlphaBeta_SumProduct(&conv);
            if ( alpha == "sum" && beta == "sum" )        convolutionAlphaBeta_SumSum(&conv);
            if ( alpha == "sum" && beta == "diff" )       convolutionAlphaBeta_SumDiff(&conv);

            if ( alpha == "min" && beta == "product" )    convolutionAlphaBeta_MinProduct(&conv);
            if ( alpha == "min" && beta == "sum" )        convolutionAlphaBeta_MinSum(&conv);
            if ( alpha == "min" && beta == "diff" )       convolutionAlphaBeta_MinDiff(&conv);

            if ( alpha == "max" && beta == "product" )    convolutionAlphaBeta_MaxProduct(&conv);
            if ( alpha == "max" && beta == "sum" )        convolutionAlphaBeta_MaxSum(&conv);
            if ( alpha == "max" && beta == "diff" )       convolutionAlphaBeta_MaxDiff(&conv);

            if ( alpha == "median" && beta == "product" ) convolutionAlphaBeta_MedianProduct(&conv);
            if ( alpha == "median" && beta == "sum" )     convolutionAlphaBeta_MedianSum(&conv);
            if ( alpha == "median" && beta == "diff" )    convolutionAlphaBeta_MedianDiff(&conv);
            img->update();
        }
    }
}
void MainWindow::convolutionAlphaBeta_SumProduct(Conv_t * conv) {

    int i,j;
    int r, g, b, row, column;
    int currentRow, currentColumn,rr,cc;
    double value;
    double sumRed, sumBlue, sumGreen;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */


    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            sumRed = 0;
            sumBlue = 0;
            sumGreen = 0;

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else
                        value = (tableWidget->item(row, column)->text()).toDouble();

                    currentRow = row - rowCenter;
                    currentColumn = column - columnCenter;

                    rr = i + currentColumn;
                    cc = j + currentRow;

                    if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                        r = ( im1[width * cc + rr] >> 16 )& 0xff;
                        g = ( im1[width * cc + rr] >> 8  )& 0xff;
                        b = ( im1[width * cc + rr] >> 0  )& 0xff;

                        sumRed   += r * value;
                        sumGreen += g * value;
                        sumBlue  += b * value;
                    }
                }

            if ( sumRed > 255 )
                sumRed = 255;

            if ( sumGreen > 255 )
                sumGreen = 255;

            if ( sumBlue > 255 )
                sumBlue = 255;

            if ( sumRed < 0 )
                sumRed = 0;

            if ( sumGreen < 0 )
                sumGreen = 0;

            if ( sumBlue < 0 )
                sumBlue = 0;

            imO[j * width + i] = ((int)sumRed) << 16 | ((int)sumGreen) << 8 | ((int)sumBlue);
            //imO[j + i * height] = ( ( ((int)sumRed) << 16 ) & 0xff )| ( ( ((int)sumGreen) << 8 ) & 0xff ) | ( ( ((int)sumBlue) << 0 ) & 0xff );
            //std::cout<<"i: "<<i<<" j: "<<j<<std::endl;

        }

}
void MainWindow::convolutionAlphaBeta_SumSum(Conv_t * conv) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row,column;
    double value;
    double sumRed, sumBlue, sumGreen;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            sumRed = 0;
            sumBlue = 0;
            sumGreen = 0;

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else
                        value = (tableWidget->item(row, column)->text()).toDouble();

                    currentRow = row - rowCenter;
                    currentColumn = column - columnCenter;

                    rr = i + currentColumn;
                    cc = j + currentRow;

                    if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                        r = ( im1[width * cc + rr] >> 16 )& 0xff;
                        g = ( im1[width * cc + rr] >> 8  )& 0xff;
                        b = ( im1[width * cc + rr] >> 0  )& 0xff;

                        sumRed   += r + value;
                        sumGreen += g + value;
                        sumBlue  += b + value;
                    }
                }

            if ( sumRed > 255 )
                sumRed = 255;

            if ( sumGreen > 255 )
                sumGreen = 255;

            if ( sumBlue > 255 )
                sumBlue = 255;

            if ( sumRed < 0 )
                sumRed = 0;

            if ( sumGreen < 0 )
                sumGreen = 0;

            if ( sumBlue < 0 )
                sumBlue = 0;

            imO[j * width + i] = ((int)sumRed) << 16 | ((int)sumGreen) << 8 | ((int)sumBlue);


        }
}
void MainWindow::convolutionAlphaBeta_SumDiff(Conv_t * conv) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row,column;
    double value;
    double sumRed, sumBlue, sumGreen;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            sumRed = 0;
            sumBlue = 0;
            sumGreen = 0;

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else
                        value = (tableWidget->item(row, column)->text()).toDouble();

                    currentRow = row - rowCenter;
                    currentColumn = column - columnCenter;

                    rr = i + currentColumn;
                    cc = j + currentRow;

                    if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                        r = ( im1[width * cc + rr] >> 16 )& 0xff;
                        g = ( im1[width * cc + rr] >> 8  )& 0xff;
                        b = ( im1[width * cc + rr] >> 0  )& 0xff;

                        sumRed   += r - value;
                        sumGreen += g - value;
                        sumBlue  += b - value;
                    }
                }

            if ( sumRed > 255 )
                sumRed = 255;

            if ( sumGreen > 255 )
                sumGreen = 255;

            if ( sumBlue > 255 )
                sumBlue = 255;

            if ( sumRed < 0 )
                sumRed = 0;

            if ( sumGreen < 0 )
                sumGreen = 0;

            if ( sumBlue < 0 )
                sumBlue = 0;

            imO[j * width + i] = ((int)sumRed) << 16 | ((int)sumGreen) << 8 | ((int)sumBlue);


        }
}
void MainWindow::convolutionAlphaBeta_MinProduct(Conv_t * conv ) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row,column;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMin, greenMin, blueMin;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else {
                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r * value);
                            sumGreen.push_back(g * value);
                            sumBlue.push_back(b * value);
                        }
                    }
                }

            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {

                redMin =  *std::min_element(sumRed.begin(),sumRed.end());
                greenMin = *std::min_element(sumGreen.begin(),sumGreen.end());
                blueMin = *std::min_element(sumBlue.begin(),sumBlue.end());

                if ( redMin > 255 )
                    redMin = 255;

                if ( greenMin > 255 )
                    greenMin = 255;

                if ( blueMin > 255 )
                    blueMin = 255;

                if ( redMin < 0 )
                    redMin = 0;

                if ( greenMin < 0 )
                    greenMin = 0;

                if ( blueMin < 0 )
                    blueMin = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMin) << 16 | ((int)greenMin) << 8 | ((int)blueMin);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MinSum(Conv_t * conv ) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc, row, column;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMin, greenMin, blueMin;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else {
                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r + value);
                            sumGreen.push_back(g + value);
                            sumBlue.push_back(b + value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {

                redMin =  *std::min_element(sumRed.begin(),sumRed.end());
                greenMin = *std::min_element(sumGreen.begin(),sumGreen.end());
                blueMin = *std::min_element(sumBlue.begin(),sumBlue.end());

                if ( redMin > 255 )
                    redMin = 255;

                if ( greenMin > 255 )
                    greenMin = 255;

                if ( blueMin > 255 )
                    blueMin = 255;

                if ( redMin < 0 )
                    redMin = 0;

                if ( greenMin < 0 )
                    greenMin = 0;

                if ( blueMin < 0 )
                    blueMin = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMin) << 16 | ((int)greenMin) << 8 | ((int)blueMin);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MinDiff(Conv_t * conv ) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row,column;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMin, greenMin, blueMin;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else {
                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r - value);
                            sumGreen.push_back(g - value);
                            sumBlue.push_back(b - value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {

                redMin =  *std::min_element(sumRed.begin(),sumRed.end());
                greenMin = *std::min_element(sumGreen.begin(),sumGreen.end());
                blueMin = *std::min_element(sumBlue.begin(),sumBlue.end());

                if ( redMin > 255 )
                    redMin = 255;

                if ( greenMin > 255 )
                    greenMin = 255;

                if ( blueMin > 255 )
                    blueMin = 255;

                if ( redMin < 0 )
                    redMin = 0;

                if ( greenMin < 0 )
                    greenMin = 0;

                if ( blueMin < 0 )
                    blueMin = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMin) << 16 | ((int)greenMin) << 8 | ((int)blueMin);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MaxProduct(Conv_t * conv ) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row, column;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMax, greenMax, blueMax;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else {
                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r * value);
                            sumGreen.push_back(g * value);
                            sumBlue.push_back(b * value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {
                redMax =  *std::max_element(sumRed.begin(),sumRed.end());
                greenMax = *std::max_element(sumGreen.begin(),sumGreen.end());
                blueMax = *std::max_element(sumBlue.begin(),sumBlue.end());

                if ( redMax > 255 )
                    redMax = 255;

                if ( greenMax > 255 )
                    greenMax = 255;

                if ( blueMax > 255 )
                    blueMax = 255;

                if ( redMax < 0 )
                    redMax = 0;

                if ( greenMax < 0 )
                    greenMax = 0;

                if ( blueMax < 0 )
                    blueMax = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMax) << 16 | ((int)greenMax) << 8 | ((int)blueMax);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MaxSum(Conv_t * conv ) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row, column;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMax, greenMax, blueMax;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else {
                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r + value);
                            sumGreen.push_back(g + value);
                            sumBlue.push_back(b + value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {
                redMax =  *std::max_element(sumRed.begin(),sumRed.end());
                greenMax = *std::max_element(sumGreen.begin(),sumGreen.end());
                blueMax = *std::max_element(sumBlue.begin(),sumBlue.end());

                if ( redMax > 255 )
                    redMax = 255;

                if ( greenMax > 255 )
                    greenMax = 255;

                if ( blueMax > 255 )
                    blueMax = 255;

                if ( redMax < 0 )
                    redMax = 0;

                if ( greenMax < 0 )
                    greenMax = 0;

                if ( blueMax < 0 )
                    blueMax = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMax) << 16 | ((int)greenMax) << 8 | ((int)blueMax);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MaxDiff(Conv_t * conv ) {
    int i,j;
    int r, g, b;
    int currentRow, currentColumn,rr,cc,row, column;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMax, greenMax, blueMax;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() )
                        value = 0;
                    else {
                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r - value);
                            sumGreen.push_back(g - value);
                            sumBlue.push_back(b - value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {
                redMax =  *std::max_element(sumRed.begin(),sumRed.end());
                greenMax = *std::max_element(sumGreen.begin(),sumGreen.end());
                blueMax = *std::max_element(sumBlue.begin(),sumBlue.end());

                if ( redMax > 255 )
                    redMax = 255;

                if ( greenMax > 255 )
                    greenMax = 255;

                if ( blueMax > 255 )
                    blueMax = 255;

                if ( redMax < 0 )
                    redMax = 0;

                if ( greenMax < 0 )
                    greenMax = 0;

                if ( blueMax < 0 )
                    blueMax = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMax) << 16 | ((int)greenMax) << 8 | ((int)blueMax);
            }

        }
}
void MainWindow::convolutionAlphaBeta_MedianProduct(Conv_t * conv ) {
    int i,j;
    int r, g, b, row, column;
    int currentRow, currentColumn,rr,cc;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMed, greenMed, blueMed;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for (  column = tableWidget->columnCount()-1; column >= 0 ; --column )
                for ( row = tableWidget->rowCount()-1; row >= 0; --row ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() ) {
                        value = 0;
                    } else {

                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r * value);
                            sumGreen.push_back(g * value);
                            sumBlue.push_back(b * value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {

                std::sort(sumRed.begin(), sumRed.end());
                std::sort(sumGreen.begin(), sumGreen.end());
                std::sort(sumBlue.begin(), sumBlue.end());

                if ( sumRed.size() % 2 != 0 ) {

                    redMed =  (sumRed[ sumRed.size()/2 ] + sumRed[ (sumRed.size()/2) + 1 ] )/2;
                    greenMed = (sumGreen[ sumGreen.size()/2 ] + sumGreen[ (sumGreen.size()/2) + 1] )/ 2;
                    blueMed = (sumBlue[ sumBlue.size()/2 ] + sumBlue[ (sumBlue.size()/2) + 1 ] )/ 2;

                } else {

                    redMed =  sumRed[ sumRed.size()/2 ];
                    greenMed = sumGreen[ sumGreen.size()/2 ];
                    blueMed = sumBlue[ sumBlue.size()/2 ];
                }

                if ( redMed > 255 )
                    redMed = 255;

                if ( greenMed > 255 )
                    greenMed = 255;

                if ( blueMed > 255 )
                    blueMed = 255;

                if ( redMed < 0 )
                    redMed = 0;

                if ( greenMed < 0 )
                    greenMed = 0;

                if ( blueMed < 0 )
                    blueMed = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMed) << 16 | ((int)greenMed) << 8 | ((int)blueMed);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MedianSum(Conv_t * conv ) {
    int i,j;
    int r, g, b, row, column;
    int currentRow, currentColumn,rr,cc;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMed, greenMed, blueMed;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for (  column = tableWidget->columnCount()-1; column >= 0 ; --column )
                for ( row = tableWidget->rowCount()-1; row >= 0; --row ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() ) {
                        value = 0;
                    } else {

                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r + value);
                            sumGreen.push_back(g + value);
                            sumBlue.push_back(b + value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {

                std::sort(sumRed.begin(), sumRed.end());
                std::sort(sumGreen.begin(), sumGreen.end());
                std::sort(sumBlue.begin(), sumBlue.end());

                if ( sumRed.size() % 2 != 0 ) {

                    redMed =  (sumRed[ sumRed.size()/2 ] + sumRed[ (sumRed.size()/2) + 1 ] )/2;
                    greenMed = (sumGreen[ sumGreen.size()/2 ] + sumGreen[ (sumGreen.size()/2) + 1] )/ 2;
                    blueMed = (sumBlue[ sumBlue.size()/2 ] + sumBlue[ (sumBlue.size()/2) + 1 ] )/ 2;

                } else {

                    redMed =  sumRed[ sumRed.size()/2 ];
                    greenMed = sumGreen[ sumGreen.size()/2 ];
                    blueMed = sumBlue[ sumBlue.size()/2 ];
                }

                if ( redMed > 255 )
                    redMed = 255;

                if ( greenMed > 255 )
                    greenMed = 255;

                if ( blueMed > 255 )
                    blueMed = 255;

                if ( redMed < 0 )
                    redMed = 0;

                if ( greenMed < 0 )
                    greenMed = 0;

                if ( blueMed < 0 )
                    blueMed = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMed) << 16 | ((int)greenMed) << 8 | ((int)blueMed);
            }
        }
}
void MainWindow::convolutionAlphaBeta_MedianDiff(Conv_t * conv ) {

    int i,j;
    int r, g, b, row, column;
    int currentRow, currentColumn,rr,cc;
    double value;
    std::vector<double> sumRed, sumBlue, sumGreen;
    double redMed, greenMed, blueMed;
    int *imO,*im1;
    QTableWidgetItem* item;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    unsigned char *data = conv->data;
    unsigned char *data2 = conv->data2;
    const int width  = conv->width;
    const int height = conv->height;

    /* alpha: min, max, med, sum(ya hecha) */
    /* beta: sum, resta, multiplicacion */

    for ( i = 0; i < width; i++ )
        for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

            for (  column = tableWidget->columnCount()-1; column >= 0 ; --column )
                for ( row = tableWidget->rowCount()-1; row >= 0; --row ) {

                    item = tableWidget->item(row,column);

                    if ( !item || item->text().isEmpty() ) {
                        value = 0;
                    } else {

                        value = (tableWidget->item(row, column)->text()).toDouble();

                        currentRow = row - rowCenter;
                        currentColumn = column - columnCenter;

                        rr = i + currentColumn;
                        cc = j + currentRow;

                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height) {

                            r = ( im1[width * cc + rr] >> 16 )& 0xff;
                            g = ( im1[width * cc + rr] >> 8  )& 0xff;
                            b = ( im1[width * cc + rr] >> 0  )& 0xff;

                            sumRed.push_back(r - value);
                            sumGreen.push_back(g - value);
                            sumBlue.push_back(b - value);
                        }
                    }
                }
            if ( sumRed.size() > 0 && sumBlue.size() > 0 && sumGreen.size() > 0 ) {

                std::sort(sumRed.begin(), sumRed.end());
                std::sort(sumGreen.begin(), sumGreen.end());
                std::sort(sumBlue.begin(), sumBlue.end());

                for (auto w = 0; w<sumRed.size();++w )
                    std::cout<<sumRed[w]<<" ";

                /*for (vector<int>::size_type i = 0; i != sumRed.size(); ++i)
                           cout << sumRed[i] << " ";*/

                if ( sumRed.size() % 2 != 0 ) {

                    redMed =  (sumRed[ sumRed.size()/2 ] + sumRed[ (sumRed.size()/2) + 1 ] )/2;
                    greenMed = (sumGreen[ sumGreen.size()/2 ] + sumGreen[ (sumGreen.size()/2) + 1] )/ 2;
                    blueMed = (sumBlue[ sumBlue.size()/2 ] + sumBlue[ (sumBlue.size()/2) + 1 ] )/ 2;

                } else {

                    redMed =  sumRed[ sumRed.size()/2 ];
                    greenMed = sumGreen[ sumGreen.size()/2 ];
                    blueMed = sumBlue[ sumBlue.size()/2 ];
                }

                if ( redMed > 255 )
                    redMed = 255;

                if ( greenMed > 255 )
                    greenMed = 255;

                if ( blueMed > 255 )
                    blueMed = 255;

                if ( redMed < 0 )
                    redMed = 0;

                if ( greenMed < 0 )
                    greenMed = 0;

                if ( blueMed < 0 )
                    blueMed = 0;

                sumRed.clear();
                sumBlue.clear();
                sumGreen.clear();

                imO[j * width + i] = ((int)redMed) << 16 | ((int)greenMed) << 8 | ((int)blueMed);
            }
        }
}
void MainWindow::opSum() {
    dlgImage *img = getActiveWindow();

    if (img) {

        if ( img->getHeight() != heightIm || img->getWidth() != widthIm )
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Resoluciones distintas");
            messageBox.setFixedSize(500,200);
            return;
        }

        /* dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());
        MdiArea->addSubWindow(newImg);
        newImg->show();
*/
        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {
            int i,j;
            int *imO,*im1;
            int r0, g0, b0 ,r1, g1, b1;
            double r,g,b;


            for ( i = 0, imO = (int*) firstIm, im1 = (int*) data; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ ) {

                    r0 = ( *imO >> 16 ) & 0xff;
                    g0 = ( *imO >> 8  ) & 0xff;
                    b0 = ( *imO >> 0  ) & 0xff;

                    r1 = ( *im1 >> 16 ) & 0xff;
                    g1 = ( *im1 >> 8  ) & 0xff;
                    b1 = ( *im1 >> 0  ) & 0xff;

                    r = r0 + r1;
                    g = g0 + g1;
                    b = b0 + b1;

                    if ( r > 255 )
                        r = 255;

                    if ( g > 255 )
                        g = 255;

                    if ( b > 255 )
                        b = 255;

                    if ( r < 0 )
                        r = 0;

                    if ( g < 0 )
                        g = 0;

                    if ( b < 0 )
                        b = 0;

                    *im1 = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }

        }img->update();
    }
}
void MainWindow::opDiff() {
    dlgImage *img = getActiveWindow();

    if (img) {

        if ( img->getHeight() != heightIm || img->getWidth() != widthIm )
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Resoluciones distintas");
            messageBox.setFixedSize(500,200);
            return;
        }

        /*   dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());
        MdiArea->addSubWindow(newImg);
        newImg->show();*/

        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {
            int i,j;
            int *imO,*im1;
            int r0, g0, b0 ,r1, g1, b1;
            double r,g,b;


            for ( i = 0, imO = (int*) firstIm, im1 = (int*) data; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ ) {

                    r0 = ( *imO >> 16 ) & 0xff;
                    g0 = ( *imO >> 8  ) & 0xff;
                    b0 = ( *imO >> 0  ) & 0xff;

                    r1 = ( *im1 >> 16 ) & 0xff;
                    g1 = ( *im1 >> 8  ) & 0xff;
                    b1 = ( *im1 >> 0  ) & 0xff;

                    r = r0 - r1;
                    g = g0 - g1;
                    b = b0 - b1;

                    if ( r > 255 )
                        r = 255;

                    if ( g > 255 )
                        g = 255;

                    if ( b > 255 )
                        b = 255;

                    if ( r < 0 )
                        r = 0;

                    if ( g < 0 )
                        g = 0;

                    if ( b < 0 )
                        b = 0;

                    *im1 = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }

        }img->update();
    }
}
void MainWindow::opProduct() {
    dlgImage *img = getActiveWindow();

    if (img) {
        if ( img->getHeight() != heightIm || img->getWidth() != widthIm )
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Resoluciones distintas");
            messageBox.setFixedSize(500,200);
            return;
        }
        /* dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());
        MdiArea->addSubWindow(newImg);
        newImg->show();
*/
        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {
            int i,j;
            int *imO,*im1;
            int r0, g0, b0 ,r1, g1, b1;
            double r,g,b;


            for ( i = 0, imO = (int*) firstIm, im1 = (int*) data; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ ) {

                    r0 = ( *imO >> 16 ) & 0xff;
                    g0 = ( *imO >> 8  ) & 0xff;
                    b0 = ( *imO >> 0  ) & 0xff;

                    r1 = ( *im1 >> 16 ) & 0xff;
                    g1 = ( *im1 >> 8  ) & 0xff;
                    b1 = ( *im1 >> 0  ) & 0xff;

                    r = r0 * r1;
                    g = g0 * g1;
                    b = b0 * b1;

                    if ( r > 255 )
                        r = 255;

                    if ( g > 255 )
                        g = 255;

                    if ( b > 255 )
                        b = 255;

                    if ( r < 0 )
                        r = 0;

                    if ( g < 0 )
                        g = 0;

                    if ( b < 0 )
                        b = 0;

                    *im1 = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }

        } img->update();
    }
}
void MainWindow::opMin() {

    dlgImage *img = getActiveWindow();

    if (img) {
        if ( img->getHeight() != heightIm || img->getWidth() != widthIm )
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Resoluciones distintas");
            messageBox.setFixedSize(500,200);
            return;
        }
        /*  dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());
        MdiArea->addSubWindow(newImg);
        newImg->show();
*/
        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {
            int i,j;
            std::vector<int>R,G,B;
            int *imO,*im1;
            int r0, g0, b0 ,r1, g1, b1;
            double r,g,b;


            for ( i = 0, imO = (int*) firstIm, im1 = (int*) data; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ ) {

                    r0 = ( *imO >> 16 ) & 0xff;
                    g0 = ( *imO >> 8  ) & 0xff;
                    b0 = ( *imO >> 0  ) & 0xff;

                    r1 = ( *im1 >> 16 ) & 0xff;
                    g1 = ( *im1 >> 8  ) & 0xff;
                    b1 = ( *im1 >> 0  ) & 0xff;

                    R.push_back(r0);
                    R.push_back(r1);
                    G.push_back(g0);
                    G.push_back(g1);
                    B.push_back(b0);
                    B.push_back(b1);

                    r = *std::min_element(R.begin(),R.end());
                    g = *std::min_element(G.begin(),G.end());
                    b = *std::min_element(B.begin(),B.end());

                    if ( r > 255 )
                        r = 255;

                    if ( g > 255 )
                        g = 255;

                    if ( b > 255 )
                        b = 255;

                    if ( r < 0 )
                        r = 0;

                    if ( g < 0 )
                        g = 0;

                    if ( b < 0 )
                        b = 0;

                    R.clear();
                    G.clear();
                    B.clear();

                    *im1 = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }

        }img->update();
    }

}
void MainWindow::opMax() {

    dlgImage *img = getActiveWindow();

    if (img) {
        if ( img->getHeight() != heightIm || img->getWidth() != widthIm )
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Resoluciones distintas");
            messageBox.setFixedSize(500,200);
            return;
        }
        /* dlgImage *newImg;
        newImg=new dlgImage(MdiArea);
        newImg->setStatusBarInfo(ui->statusbar);
        newImg->setName(img->getName());
        MdiArea->addSubWindow(newImg);
        newImg->show();
*/
        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {
            int i,j;
            std::vector<int>R,G,B;
            int *imO,*im1;
            int r0, g0, b0 ,r1, g1, b1;
            double r,g,b;


            for ( i = 0, imO = (int*) firstIm, im1 = (int*) data; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ ) {

                    r0 = ( *imO >> 16 ) & 0xff;
                    g0 = ( *imO >> 8  ) & 0xff;
                    b0 = ( *imO >> 0  ) & 0xff;

                    r1 = ( *im1 >> 16 ) & 0xff;
                    g1 = ( *im1 >> 8  ) & 0xff;
                    b1 = ( *im1 >> 0  ) & 0xff;

                    R.push_back(r0);
                    R.push_back(r1);
                    G.push_back(g0);
                    G.push_back(g1);
                    B.push_back(b0);
                    B.push_back(b1);

                    r = *std::max_element(R.begin(),R.end());
                    g = *std::max_element(G.begin(),G.end());
                    b = *std::max_element(B.begin(),B.end());

                    if ( r > 255 )
                        r = 255;

                    if ( g > 255 )
                        g = 255;

                    if ( b > 255 )
                        b = 255;

                    if ( r < 0 )
                        r = 0;

                    if ( g < 0 )
                        g = 0;

                    if ( b < 0 )
                        b = 0;

                    R.clear();
                    G.clear();
                    B.clear();

                    *im1 = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }

        }img->update();
    }
}
void MainWindow::opComplement() {

    dlgImage *img = getActiveWindow();

    if (img) {

        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();

        if (data) {

            int i,j;
            double r,g,b;
            int *imO;

            for ( i = 0; i < width; i++ )
                for ( j = 0, imO = (int*) data; j < height; j++ ) {

                    r = 255;
                    g = 255;
                    b = 255;

                    r -= ( imO[width * j + i] >> 16 )& 0xff;
                    g -= ( imO[width * j + i] >> 8  )& 0xff;
                    b -= ( imO[width * j + i] >> 0  )& 0xff;

                    if ( r > 255 )
                        r = 255;

                    if ( g > 255 )
                        g = 255;

                    if ( b > 255 )
                        b = 255;

                    if ( r < 0 )
                        r = 0;

                    if ( g < 0 )
                        g = 0;

                    if ( b < 0 )
                        b = 0;

                    imO[j * width + i] = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }
        }img->update();
    }
}
void MainWindow::ApplyThresholding() {
    dlgImage *img = getActiveWindow();

    if ( img ) {
        setStatus("Image "+ img->getName() + " new thresholding");

        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();
        const int pixels = height * width;

        if (data) {

            int i,j;
            int *imO;
            int r, g, b;

            std::vector<double> yRed(256), yGreen(256), yBlue(256);
            std::vector<double> p1Red(256), p1Green(256), p1Blue(256);
            std::vector<double> p2Red(256), p2Green(256), p2Blue(256);
            std::vector<double> M1Red(256), M1Green(256), M1Blue(256);
            std::vector<double> M2Red(256), M2Green(256), M2Blue(256);
            std::vector<double> vRed(256), vGreen(256), vBlue(256);
            std::vector<int> t(256);
            std::vector<double> red, blue, green;

            for ( i = 0; i < 256; ++i)
                yRed[i] = yGreen[i] = yBlue[i] = 0;

            for ( i = 0, imO = (int*) data; i < height; ++i )
                for (j = 0; j < width; j++,imO++) {

                    r = ( *imO >> 16 ) & 0xff;
                    g = ( *imO >> 8  ) & 0xff;
                    b = ( *imO >> 0  ) & 0xff;

                    yRed[r]    += 1;
                    yGreen[g]  += 1;
                    yBlue[b]   += 1;

                }

            for ( i = 0; i < 256; ++i )
                std::cout<<"yRed["<<i<<"]: "<<yRed[i]<<std::endl;

            p1Red[0]   = yRed[0]/pixels;
            p1Blue[0]  = yBlue[0]/pixels;
            p1Green[0] = yGreen[0]/pixels;

            p2Red[0]   = 1 - p1Red[0];
            p2Blue[0]  = 1 - p1Blue[0];
            p2Green[0] = 1 - p1Green[0];

            for ( i = 1; i < 256; ++i ) {

                p1Red[i]   = (yRed[i]/pixels) + p1Red[i-1];
                p1Blue[i]  = (yBlue[i]/pixels) + p1Blue[i-1];
                p1Green[i] = (yGreen[i]/pixels) + p1Green[i-1];

                p2Red[i]   = 1.0 - p1Red[i];
                p2Blue[i]  = 1.0 - p1Blue[i];
                p2Green[i] = 1.0 - p1Green[i];

                std::cout<<"p1Red["<<i<<"]: "<<p1Red[i]<<" p2Red["<<i<<"]: "<<p2Red[i]<<std::endl;

            }

            for ( i = 0; i < 256; ++i) {

                M1Red[i] = M1Green[i] = M1Blue[i] = 0;
                M2Red[i] = M2Green[i] = M2Blue[i] = 0;
            }

            int divR, divG, divB;

            for ( i = 0; i < 256; ++i ) {
                divR = divG = divB = 0;
                for ( j = 0; j < 256; j++ ) {

                    if ( j <= i )
                    {

                        M1Red[i]   += yRed[j]   * j;
                        M1Green[i] += yGreen[j] * j;
                        M1Blue[i]  += yBlue[j]  * j;

                        divR += yRed[j];
                        divG += yGreen[j];
                        divB += yBlue[j];

                        if (j == i){

                            if ( divR != 0 && divG != 0 && divB != 0) {
                                M1Red[i]   = M1Red[i]   / divR;
                                M1Green[i] = M1Green[i] / divG;
                                M1Blue[i]  = M1Blue[i]  / divB;
                            } else {
                                M1Red[i]   = 0;
                                M1Green[i] = 0;
                                M1Blue[i]  = 0;
                            }
                            divR = divG = divB = 0;
                        }

                    } else {

                        M2Red[i]   +=  yRed[j]  * j;
                        M2Green[i] += yGreen[j] * j;
                        M2Blue[i]  += yBlue[j ] * j;

                        divR += yRed[j];
                        divG += yGreen[j];
                        divB += yBlue[j];

                        if (j == 255) {

                            if ( divR != 0 && divG != 0 && divB != 0) {
                                M1Red[i]   = M1Red[i]   / divR;
                                M1Green[i] = M1Green[i] / divG;
                                M1Blue[i]  = M1Blue[i]  / divB;
                            } else {
                                M1Red[i]   = 0;
                                M1Green[i] = 0;
                                M1Blue[i]  = 0;
                            }
                            divR = divG = divB = 0;
                        }
                    }
                }
            }

            for (i = 0; i < 256; ++i)
                vRed[i] = vGreen[i] = vBlue[i] = 0;

            for ( i = 0; i < 256; ++i ) {

                std::cout<<"M1Red["<<i<<"]: "<<M1Red[i]<<" M2Red["<<i<<"]: "<<M2Red[i]<<std::endl;
                vRed[i]  = ( p1Red[i] * p2Red[i] * (M1Red[i] - M2Red[i]) * (M1Red[i] - M2Red[i]) );
                vGreen[i] = ( p1Green[i] * p2Green[i] * (M1Green[i] - M2Green[i]) * (M1Green[i] - M2Green[i]) );
                vBlue[i] = ( p1Blue[i] * p2Blue[i] * (M1Blue[i] - M2Blue[i]) * (M1Blue[i] - M2Blue[i]) );

                std::cout<<"vRed["<<i<<"]: "<<vRed[i]<<std::endl;
            }

            double vRedMax, vGreenMax, vBlueMax;

            vRedMax   = *std::max_element(vRed.begin(), vRed.end());
            vGreenMax = *std::max_element(vGreen.begin(), vGreen.end());
            vBlueMax  = *std::max_element(vBlue.begin(), vBlue.end());

            int tR,tB,tG;

            for ( i = 0; i < 256; ++i ) {

                if ( vRed[i] == vRedMax )        tR = i;
                if ( vGreen[i] == vGreenMax )    tG = i;
                if ( vBlue[i] == vBlueMax )      tB = i;
            }

            std::cout<<"vRedMax: "<<vRedMax<<" vGreenMax: "<<vGreenMax<<" vBlueMax: "<<vBlueMax<<std::endl;

            for ( i = 0, imO = (int*) data; i < height; ++i )
                for ( j = 0; j < width; j++, imO++ ) {

                    r = ( *imO >> 16 ) & 0xff;
                    g = ( *imO >> 8  ) & 0xff;
                    b = ( *imO >> 0  ) & 0xff;

                    if ( r > tR  &&  g > tG &&  b > tB ) {

                        r = 255;
                        g = 255;
                        b = 255;

                    } else {

                        r = 0;
                        g = 0;
                        b = 0;

                    }

                    //computerphile
                    *imO = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }
            img->update();
        }
    }
}
void MainWindow::ApplyThresholdingValue() {
    dlgImage *img = getActiveWindow();

    if ( img ) {
        setStatus("Image "+ img->getName() + " new thresholding");

        unsigned char* data = img->getImageRGB()->getData();

        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();
        const int pixels = height * width;
        int value;
        bool ok;

        QInputDialog* inputDialog = new QInputDialog();
        inputDialog->setOptions(QInputDialog::NoButtons);

        QString text =  inputDialog->getText(NULL ,"Value",
                                             "t:", QLineEdit::Normal,
                                             "100", &ok);

        if (ok && !text.isEmpty())
            value = stoi(text.toStdString());


        if (data) {

            int i,j;
            int *imO;
            int r, g, b;

            std::vector<double> yRed(256), yGreen(256), yBlue(256);
            std::vector<double> p1Red(256), p1Green(256), p1Blue(256);
            std::vector<double> p2Red(256), p2Green(256), p2Blue(256);
            std::vector<double> M1Red(256), M1Green(256), M1Blue(256);
            std::vector<double> M2Red(256), M2Green(256), M2Blue(256);
            std::vector<double> vRed(256), vGreen(256), vBlue(256);
            std::vector<int> t(256);
            std::vector<double> red, blue, green;

            for ( i = 0; i < 256; ++i)
                yRed[i] = yGreen[i] = yBlue[i] = 0;

            for ( i = 0, imO = (int*) data; i < height; ++i )
                for (j = 0; j < width; j++,imO++) {

                    r = ( *imO >> 16 ) & 0xff;
                    g = ( *imO >> 8  ) & 0xff;
                    b = ( *imO >> 0  ) & 0xff;

                    yRed[r]    += 1;
                    yGreen[g]  += 1;
                    yBlue[b]   += 1;

                }

            for ( i = 0; i < 256; ++i )
                std::cout<<"yRed["<<i<<"]: "<<yRed[i]<<std::endl;

            p1Red[0]   = yRed[0]/pixels;
            p1Blue[0]  = yBlue[0]/pixels;
            p1Green[0] = yGreen[0]/pixels;

            p2Red[0]   = 1 - p1Red[0];
            p2Blue[0]  = 1 - p1Blue[0];
            p2Green[0] = 1 - p1Green[0];

            for ( i = 1; i < 256; ++i ) {

                p1Red[i]   = (yRed[i]/pixels) + p1Red[i-1];
                p1Blue[i]  = (yBlue[i]/pixels) + p1Blue[i-1];
                p1Green[i] = (yGreen[i]/pixels) + p1Green[i-1];

                p2Red[i]   = 1.0 - p1Red[i];
                p2Blue[i]  = 1.0 - p1Blue[i];
                p2Green[i] = 1.0 - p1Green[i];

                std::cout<<"p1Red["<<i<<"]: "<<p1Red[i]<<" p2Red["<<i<<"]: "<<p2Red[i]<<std::endl;

            }

            for ( i = 0; i < 256; ++i) {

                M1Red[i] = M1Green[i] = M1Blue[i] = 0;
                M2Red[i] = M2Green[i] = M2Blue[i] = 0;
            }

            int divR, divG, divB;

            for ( i = 0; i < 256; ++i ) {
                divR = divG = divB = 0;
                for ( j = 0; j < 256; j++ ) {

                    if ( j <= i )
                    {

                        M1Red[i]   += yRed[j]   * j;
                        M1Green[i] += yGreen[j] * j;
                        M1Blue[i]  += yBlue[j]  * j;

                        divR += yRed[j];
                        divG += yGreen[j];
                        divB += yBlue[j];

                        if (j == i){

                            if ( divR != 0 && divG != 0 && divB != 0) {
                                M1Red[i]   = M1Red[i]   / divR;
                                M1Green[i] = M1Green[i] / divG;
                                M1Blue[i]  = M1Blue[i]  / divB;
                            } else {
                                M1Red[i]   = 0;
                                M1Green[i] = 0;
                                M1Blue[i]  = 0;
                            }
                            divR = divG = divB = 0;
                        }

                    } else {

                        M2Red[i]   +=  yRed[j]  * j;
                        M2Green[i] += yGreen[j] * j;
                        M2Blue[i]  += yBlue[j ] * j;

                        divR += yRed[j];
                        divG += yGreen[j];
                        divB += yBlue[j];

                        if (j == 255) {

                            if ( divR != 0 && divG != 0 && divB != 0) {
                                M1Red[i]   = M1Red[i]   / divR;
                                M1Green[i] = M1Green[i] / divG;
                                M1Blue[i]  = M1Blue[i]  / divB;
                            } else {
                                M1Red[i]   = 0;
                                M1Green[i] = 0;
                                M1Blue[i]  = 0;
                            }
                            divR = divG = divB = 0;
                        }
                    }
                }
            }

            for (i = 0; i < 256; ++i)
                vRed[i] = vGreen[i] = vBlue[i] = 0;

            for ( i = 0; i < 256; ++i ) {

                std::cout<<"M1Red["<<i<<"]: "<<M1Red[i]<<" M2Red["<<i<<"]: "<<M2Red[i]<<std::endl;
                vRed[i]  = ( p1Red[i] * p2Red[i] * (M1Red[i] - M2Red[i]) * (M1Red[i] - M2Red[i]) );
                vGreen[i] = ( p1Green[i] * p2Green[i] * (M1Green[i] - M2Green[i]) * (M1Green[i] - M2Green[i]) );
                vBlue[i] = ( p1Blue[i] * p2Blue[i] * (M1Blue[i] - M2Blue[i]) * (M1Blue[i] - M2Blue[i]) );

                std::cout<<"vRed["<<i<<"]: "<<vRed[i]<<std::endl;
            }

            double vRedMax, vGreenMax, vBlueMax;

            vRedMax   = *std::max_element(vRed.begin(), vRed.end());
            vGreenMax = *std::max_element(vGreen.begin(), vGreen.end());
            vBlueMax  = *std::max_element(vBlue.begin(), vBlue.end());

            int tR,tB,tG;

            for ( i = 0; i < 256; ++i ) {

                if ( vRed[i] == vRedMax )        tR = i;
                if ( vGreen[i] == vGreenMax )    tG = i;
                if ( vBlue[i] == vBlueMax )      tB = i;
            }

            std::cout<<"vRedMax: "<<vRedMax<<" vGreenMax: "<<vGreenMax<<" vBlueMax: "<<vBlueMax<<std::endl;

            for ( i = 0, imO = (int*) data; i < height; ++i )
                for ( j = 0; j < width; j++, imO++ ) {

                    r = ( *imO >> 16 ) & 0xff;
                    g = ( *imO >> 8  ) & 0xff;
                    b = ( *imO >> 0  ) & 0xff;

                    if ( r > value ) {

                        r = 255;
                        g = 255;
                        b = 255;

                    } else {

                        r = 0;
                        g = 0;
                        b = 0;

                    }
                    *imO = ((int)r) << 16 | ((int)g) << 8 | ((int)b);
                }
            img->update();
        }
    }
}
void MainWindow::labelingNormal() {
    ApplyThresholding();
    dlgImage *img = getActiveWindow();

    tableWidget = mask->tableWidget;

    if (img) {

        unsigned char* data = img->getImageRGB()->getData();
        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();
        updateIm = false;
        std::queue<std::pair<int,int>>tail;

        if (data) {

            int i,j,r,g,b,r1,g1,b1,r2,g2,b2;
            int row, column,value;
            int currentRow, currentColumn,rr,cc;
            std::pair<int,int> tmp;
            int *imO,*im1;
            Labl_t toFunction;
            std::srand(std::time(0));
            QTableWidgetItem* item;

            const int rowCenter = mask->lastCenterRow;
            const int columnCenter = mask->lastCenterColumn;

            long long label = 1;

            r2 = std::rand()%256;
            g2 = std::rand()%256;
            b2 = std::rand()%256;

            unsigned char *data2 = new unsigned char[4*width*height];

            for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ )
                    *im1 = 0;

            for ( i = 0; i < width; i++ )
                for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

                    r = ( imO[width * j + i] >> 16 )& 0xff;
                    g = ( imO[width * j + i] >> 8 ) & 0xff;
                    b = ( imO[width * j + i] >> 0 ) & 0xff;

                    r1 = ( im1[width * j + i] >> 16 )& 0xff;
                    g1 = ( im1[width * j + i] >> 8 ) & 0xff;
                    b1 = ( im1[width * j + i] >> 0 ) & 0xff;

                    if ( r == 255 && g == 255 && b == 255 && r1 == 0 && g1 == 0 && b1 == 0 ) {
                        *(im1 + width * j + i) = (r2 << 16) | (g2 << 8) | (b2 << 0);

                        tail.push(std::make_pair(j,i));
                        toFunction.cc = j;
                        toFunction.rr = i;
                        toFunction.width = width;
                        toFunction.height = height;
                        toFunction.data = data;
                        toFunction.data2 = data2;
                        toFunction.label = label;
                        toFunction.t = &tail;
                        toFunction.r = r2;
                        toFunction.g = g2;
                        toFunction.b = b2;
                        checkNeighbourhood(&toFunction);
                        r2 = std::rand()%256;
                        g2 = std::rand()%256;
                        b2 = std::rand()%256;
                        label++;
                    }
                }
            if ( updateIm == true)
                for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                    for ( j = 0; j < width; j++, imO++, im1++ )
                        *imO = *im1;
        }
        img->update();
    }
}
void MainWindow::labelingValue() {
    ApplyThresholdingValue();
    dlgImage *img = getActiveWindow();

    tableWidget = mask->tableWidget;

    if (img) {

        unsigned char* data = img->getImageRGB()->getData();
        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();
        std::queue<std::pair<int,int>>tail;

        if (data) {

            int i,j,r,g,b,r1,g1,b1,r2,g2,b2;
            int row, column,value;
            int currentRow, currentColumn,rr,cc;
            std::pair<int,int> tmp;
            int *imO,*im1;
            Labl_t toFunction;
            std::srand(std::time(0));
            QTableWidgetItem* item;

            const int rowCenter = mask->lastCenterRow;
            const int columnCenter = mask->lastCenterColumn;

            long long label = 1;

            r2 = std::rand()%256;
            g2 = std::rand()%256;
            b2 = std::rand()%256;

            unsigned char *data2 = new unsigned char[4*width*height];

            for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ )
                    *im1 = 0;

            for ( i = 0; i < width; i++ )
                for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

                    r = ( imO[width * j + i] >> 16 )& 0xff;
                    g = ( imO[width * j + i] >> 8 ) & 0xff;
                    b = ( imO[width * j + i] >> 0 ) & 0xff;

                    r1 = ( im1[width * j + i] >> 16 )& 0xff;
                    g1 = ( im1[width * j + i] >> 8 ) & 0xff;
                    b1 = ( im1[width * j + i] >> 0 ) & 0xff;

                    if ( r == 255 && g == 255 && b == 255 && r1 == 0 && g1 == 0 && b1 == 0 ) {
                        *(im1 + width * j + i) = (r2 << 16) | (g2 << 8) | (b2 << 0);

                        tail.push(std::make_pair(j,i));
                        toFunction.cc = j;
                        toFunction.rr = i;
                        toFunction.width = width;
                        toFunction.height = height;
                        toFunction.data = data;
                        toFunction.data2 = data2;
                        toFunction.label = label;
                        toFunction.t = &tail;
                        toFunction.r = r2;
                        toFunction.g = g2;
                        toFunction.b = b2;
                        checkNeighbourhood(&toFunction);
                        r2 = std::rand()%256;
                        g2 = std::rand()%256;
                        b2 = std::rand()%256;
                        label++;
                    }
                }
            if ( updateIm == true)
                for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                    for ( j = 0; j < width; j++, imO++, im1++ )
                        *imO = *im1;
        }
        img->update();
    }
}
void MainWindow::checkNeighbourhood( Labl_t * tail ) {

    int cc,rr,i,j,label,r,g,b,r1,g1,b1,r2,g2,b2,*imO,*im1,width,height,row,column,currentRow,currentColumn;
    double value;
    unsigned char *data, *data2;
    QTableWidgetItem* item;
    std::pair<int,int>tmp;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    data  = tail->data;
    data2 = tail->data2;
    imO = (int*) data;
    im1 = (int*) data2;
    width = tail->width;
    height = tail->height;
    j = tail->cc;
    i = tail->rr;
    r2 = tail->r;
    g2 = tail->g;
    b2 = tail->b;
    label = tail->label;

    while ( !tail->t->empty() ) {

        //std::cout<<tail->t->empty()<<std::endl;

        tmp = tail->t->front();
        tail->t->pop();

        j = tmp.first;
        i = tmp.second;

        //*(im1 + width * j + i) = (label << 16) & 0xff | (label << 8)  & 0xff | (label << 0) & 0xff;

        for ( row = tableWidget->rowCount()-1; row >= 0; --row )
            for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                item = tableWidget->item(row,column);

                if ( !item || item->text().isEmpty() )
                    value = 0;
                else {

                    if ( updateIm == false) updateIm = true;
                    currentRow = row - rowCenter;
                    currentColumn = column - columnCenter;

                    rr =  i + currentColumn;
                    cc =  j + currentRow;

                    if ( rr >= 0 && cc >= 0 && rr < width && cc < height ) {

                        r = ( imO[width * cc + rr] >> 16 )& 0xff;
                        g = ( imO[width * cc + rr] >> 8 ) & 0xff;
                        b = ( imO[width * cc + rr] >> 0 ) & 0xff;

                        r1 = ( im1[width * cc + rr] >> 16 )& 0xff;
                        g1 = ( im1[width * cc + rr] >> 8 ) & 0xff;
                        b1 = ( im1[width * cc + rr] >> 0 ) & 0xff;

                        if ( r == 255 && g == 255 && b == 255 && r1 == 0 && g1 == 0 && b1 == 0 ){
                            im1[width * cc + rr] = (r2 << 16) | (g2 << 8) | (b2 << 0);
                            tail->t->push( make_pair(cc,rr) );
                        }
                    }
                }
            }
    }
}
void MainWindow::watershed() {
    grayscale();
    dlgImage *img = getActiveWindow();

    tableWidget = mask->tableWidget;

    if (img) {

        unsigned char* data = img->getImageRGB()->getData();
        const int height = img->getImageRGB()->getHeight();
        const int width = img->getImageRGB()->getWidth();
        updateIm = false;
        std::queue<std::pair<int,int>>tail;
        std::queue<std::pair<int,int>>tailLabeling;

        if (data) {
            int h;
            int i,j,r,g,b,r1,g1,b1,r2,g2,b2;
            int row, column,value;
            int vecinos;
            int currentRow, currentColumn,rr,cc;
            std::pair<int,int> tmp;
            int *imO,*im1;
            Labl_t toFunction;
            std::srand(std::time(0));
            QTableWidgetItem* item;

            const int rowCenter = mask->lastCenterRow;
            const int columnCenter = mask->lastCenterColumn;

            long long label = 1;

            r2 = std::rand()%256;
            g2 = std::rand()%256;
            b2 = std::rand()%256;

            unsigned char *data2 = new unsigned char[4*width*height];

            for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                for ( j = 0; j < width; j++, imO++, im1++ )
                    *im1 = -1;

            for( h = 0; h <= 255; ++h ) {

                for ( i = 0; i < width; i++ )
                    for ( j = 0, imO = (int*) data, im1 = (int*) data2; j < height; j++ ) {

                        r = ( imO[width * j + i] >> 16 )& 0xff;
                        g = ( imO[width * j + i] >> 8 ) & 0xff;
                        b = ( imO[width * j + i] >> 0 ) & 0xff;

                        /*r1 = ( im1[width * j + i] >> 16 )& 0xff;
                        g1 = ( im1[width * j + i] >> 8 ) & 0xff;
                        b1 = ( im1[width * j + i] >> 0 ) & 0xff;
                        */
                        if ( r == h ) {
                            vecinos = 0;
                            //revisamos la máscara para los vecinos
                            for ( row = tableWidget->rowCount()-1; row >= 0; --row )
                                for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                                    item = tableWidget->item(row,column);

                                    if ( !item || item->text().isEmpty() )
                                        value = 0;
                                    else {

                                        if ( updateIm == false) updateIm = true;
                                        currentRow = row - rowCenter;
                                        currentColumn = column - columnCenter;

                                        rr =  i + currentColumn;
                                        cc =  j + currentRow;

                                        if ( rr >= 0 && cc >= 0 && rr < width && cc < height ) {

                                            r1 = ( im1[width * cc + rr] >> 16 )& 0xff;
                                            g1 = ( im1[width * cc + rr] >> 8 ) & 0xff;
                                            b1 = ( im1[width * cc + rr] >> 0 ) & 0xff;

                                            if ( r1 >= 0 ) {//Si el pixel ya está etiquetado, asignamos Q

                                                *(im1 + width * j + i) = (Q << 16) | (Q << 8) | (Q << 0);
                                                tail.push(make_pair(j,i));
                                                break;
                                            } else {//En caso contrario, asignamos M porque ese pixel podría ser un mínimo

                                                *(im1 + width * j + i) = (M << 16) | (M << 8) | (M << 0);
                                                tailLabeling.push(make_pair(j,i));
                                            }

                                        }
                                    }
                                }
                        }
                    }
                while ( !tail.empty() ) {
                    //Progagamos etiqueta
                }

            }
            if ( i + 1  == width && j + 1 == height ) {
                //labeling M
                /*****************************/
                toFunction.cc = j;
                toFunction.rr = i;
                toFunction.width = width;
                toFunction.height = height;
                toFunction.data = data;
                toFunction.data2 = data2;
                toFunction.label = label;
                toFunction.t = &tailLabeling;
                toFunction.r = r2;
                toFunction.g = g2;
                toFunction.b = b2;
                checkNeighbourhoodM(&toFunction);
                r2 = std::rand()%256;
                g2 = std::rand()%256;
                b2 = std::rand()%256;
                label++;
                /****************************/
            }
            if ( updateIm == true)
                for ( i = 0, imO = (int*) data, im1 = (int*) data2; i < height; i++ )
                    for ( j = 0; j < width; j++, imO++, im1++ )
                        *imO = *im1;
        }
        img->update();
    }
}

void MainWindow::labelingM() {

    int cc,rr,i,j,label,r,g,b,r1,g1,b1,r2,g2,b2,*imO,*im1,width,height,row,column,currentRow,currentColumn;
    double value;
    unsigned char *data, *data2;
    QTableWidgetItem* item;
    std::pair<int,int>tmp;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    data  = tail->data;
    data2 = tail->data2;
    imO = (int*) data;
    im1 = (int*) data2;
    width = tail->width;
    height = tail->height;
    j = tail->cc;
    i = tail->rr;
    r2 = tail->r;
    g2 = tail->g;
    b2 = tail->b;
    label = tail->label;

    while ( !tail->t->empty() ) {

        //std::cout<<tail->t->empty()<<std::endl;

        tmp = tail->t->front();
        tail->t->pop();

        j = tmp.first;
        i = tmp.second;

        //*(im1 + width * j + i) = (label << 16) & 0xff | (label << 8)  & 0xff | (label << 0) & 0xff;

        for ( row = tableWidget->rowCount()-1; row >= 0; --row )
            for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                item = tableWidget->item(row,column);

                if ( !item || item->text().isEmpty() )
                    value = 0;
                else {

                    if ( updateIm == false) updateIm = true;
                    currentRow = row - rowCenter;
                    currentColumn = column - columnCenter;

                    rr =  i + currentColumn;
                    cc =  j + currentRow;

                    if ( rr >= 0 && cc >= 0 && rr < width && cc < height ) {

                        r = ( imO[width * cc + rr] >> 16 )& 0xff;
                        g = ( imO[width * cc + rr] >> 8 ) & 0xff;
                        b = ( imO[width * cc + rr] >> 0 ) & 0xff;

                        r1 = ( im1[width * cc + rr] >> 16 )& 0xff;
                        g1 = ( im1[width * cc + rr] >> 8 ) & 0xff;
                        b1 = ( im1[width * cc + rr] >> 0 ) & 0xff;

                        if ( r == 255 && g == 255 && b == 255 && r1 == 0 && g1 == 0 && b1 == 0 ){
                            im1[width * cc + rr] = (r2 << 16) | (g2 << 8) | (b2 << 0);
                            tail->t->push( make_pair(cc,rr) );
                        }
                    }
                }
            }
    }

}
void MainWindow::checkNeighbourhoodM( Labl_t * tail ) {

    int cc,rr,i,j,label,r,g,b,r1,g1,b1,r2,g2,b2,*imO,*im1,width,height,row,column,currentRow,currentColumn;
    double value;
    unsigned char *data, *data2;
    QTableWidgetItem* item;
    std::pair<int,int>tmp;

    const int rowCenter = mask->lastCenterRow;
    const int columnCenter = mask->lastCenterColumn;

    data  = tail->data;
    data2 = tail->data2;
    imO = (int*) data;
    im1 = (int*) data2;
    width = tail->width;
    height = tail->height;
    j = tail->cc;
    i = tail->rr;
    r2 = tail->r;
    g2 = tail->g;
    b2 = tail->b;
    label = tail->label;

    while ( !tail->t->empty() ) {

        //std::cout<<tail->t->empty()<<std::endl;

        tmp = tail->t->front();
        tail->t->pop();

        j = tmp.first;
        i = tmp.second;

        //*(im1 + width * j + i) = (label << 16) & 0xff | (label << 8)  & 0xff | (label << 0) & 0xff;

        for ( row = tableWidget->rowCount()-1; row >= 0; --row )
            for (  column = tableWidget->columnCount()-1; column >= 0 ; --column ) {

                item = tableWidget->item(row,column);

                if ( !item || item->text().isEmpty() )
                    value = 0;
                else {

                    if ( updateIm == false) updateIm = true;
                    currentRow = row - rowCenter;
                    currentColumn = column - columnCenter;

                    rr =  i + currentColumn;
                    cc =  j + currentRow;

                    if ( rr >= 0 && cc >= 0 && rr < width && cc < height ) {

                        r = ( imO[width * cc + rr] >> 16 )& 0xff;
                        g = ( imO[width * cc + rr] >> 8 ) & 0xff;
                        b = ( imO[width * cc + rr] >> 0 ) & 0xff;

                        r1 = ( im1[width * cc + rr] >> 16 )& 0xff;
                        g1 = ( im1[width * cc + rr] >> 8 ) & 0xff;
                        b1 = ( im1[width * cc + rr] >> 0 ) & 0xff;

                        if ( /* r == 255 && g == 255 && b == 255 && */ r1 == M && g1 == M && b1 == M ){
                            im1[width * cc + rr] = (label << 16) | (label << 8) | (label << 0);
                            tail->t->push( make_pair(cc,rr) );
                        }
                    }
                }
            }
    }
}
