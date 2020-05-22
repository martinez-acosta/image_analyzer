#include "dlgimage.h"
#include "ui_dlgimage.h"

#include <iostream>

using namespace std;

dlgImage::dlgImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgImage)
{
    ui->setupUi(this);

    img=ui->img;

    Width=0;
    Height=0;

    cout<<"Window created.."<<endl;
}

dlgImage::~dlgImage()
{
    delete ui;
    cout<<"Window Closed.."<<endl;
}

void dlgImage::redim() {
    Width=0;
    Height=0;
    Width=img->pixmap()->width();
    Height=img->pixmap()->height();
    img->setGeometry(0,0,Width,Height);
    this->adjustSize();
}

void dlgImage::setName(QString n) {
    img->setImage(n);
    Name=n;
    this->setWindowTitle(Name);
    redim();
}

void dlgImage::saveImageAs(QString n) {
    img->saveImageAs(n);
    setName(n);
}

void dlgImage::setStatusBarInfo(QStatusBar *q) {
    img->setStatusBarInfo(q);
}

void dlgImage::grayscale() {
    img->grayscale();
}
void dlgImage::update() {
    img->update();
}

