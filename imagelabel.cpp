#include "imagelabel.h"
#include "imagergb.h"
#include <iostream>
#include <QMouseEvent>
#include <QRgb>



using namespace std;

ImageLabel::ImageLabel(QWidget *parent) :
    QLabel(parent)
{
    info=NULL;
    info_sb=NULL;
    img=NULL;
    qimg=new QImage;
    cout<<"create label.."<<endl;
}

ImageLabel::~ImageLabel() {
    if (img)
        delete img;
    if (qimg)
        delete qimg;
    cout<<"erase label.."<<endl;
}

void ImageLabel::setLabelInfo(QLabel *i) {
    info=i;
}

void ImageLabel::setStatusBarInfo(QStatusBar *q) {
    info_sb=q;
}

void ImageLabel::setImage(QString &n) {
    if (qimg->load(n)) {
        cout<<"Image loaded..."<<endl;
        if (img)
            delete img;

        img=new imageRGB();
        img->fromImage(qimg);
        this->setPixmap(QPixmap::fromImage(*qimg));

        path=n;

    }
    else
        cout<<"Image couldn't be loaded.."<<endl;
}

void ImageLabel::saveImageAs(QString &n) {

    if (qimg->save(n))
        cout<<"Image loaded..."<<endl;
    else
        cout<<"Image couldn't be saved.."<<endl;
}

void ImageLabel::mouseMoveEvent(QMouseEvent *ev) {

    if (this->pixmap()) {
       QString texto;
       unsigned int x=0,y=0,r=0,g=0,b=0;
       x=ev->x();
       y=ev->y();
       const QRgb p=this->pixmap()->toImage().pixel(x,y);
       r=(p>>16)&0x000000ff;
       g=(p>>8)&0x000000ff;
       b=(p>>0)&0x000000ff;

       texto.sprintf("[%dx%d] X=%d, Y=%d, R=%d, G=%d, B=%d",img->getWidth(),img->getHeight(),x,y,r,g,b);
       texto="["+path+"]"+texto;
       if (info)
           info->setText(texto);
       if (info_sb)
           info_sb->showMessage(texto);
    }
}

void ImageLabel::update() {
    if (qimg)
        delete qimg;
    qimg=img->toImage();
    this->setPixmap(QPixmap::fromImage(*qimg));
}

void ImageLabel::grayscale() {

    img->toGrayScale();
    update();
}

