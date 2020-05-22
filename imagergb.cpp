#include "imagergb.h"
#include <stdio.h>
#include <QPixmap>
#include <QImage>
#include <iostream>


using namespace std;

imageRGB::imageRGB()
    :image()
{
}

imageRGB::imageRGB(int w, int h)
    :image(w,h,4*w*h+4)
{

}

imageRGB::imageRGB(int w, int h, unsigned char *data)
    :image(w,h,data)
{

}

imageRGB::~imageRGB() {

}

//This method is for Qt use only.
void imageRGB::fromImage(QImage *im) {
    if (!im->isNull()) {
        int i;
        QRgb *imD,*imO;
        redim(im->width(),im->height(),4*im->width()*im->height()+4);
        for (i=0,imD=(QRgb*)data;i<height;i++,imD+=width) {
            imO=(QRgb*)im->scanLine(i);
            memcpy(imD,imO,4*width);
        }
    }
}

//This method is for Qt use only.
QImage *imageRGB::toImage() {
    if (!data)
        return NULL;

    QImage *im;
    im=new QImage(data,width,height,QImage::Format_RGB32);

    return im;
}

void imageRGB::toGrayScale() {
    if (data) {
        int i,j;
        int tmp,r,g,b;
        int *imO;
        for (i=0,imO=(int*)data;i<height;i++) {
            for (j=0;j<width;j++,imO++) {
                r=((*imO)>>16)&0x000000ff;
                g=((*imO)>>8)&0x000000ff;
                b=((*imO)>>0)&0x000000ff;
                tmp=((34*b+55*g+11*r)/100)&0x000000ff;
                *imO=((*imO)&(0xff000000))|(tmp<<16)|(tmp<<8)|(tmp);

            }
        }
    }
}


void imageRGB::toNewHistogram(int x1, int x2) {
    if (data) {
        double escala = 255.0/(x2-x1);
        int i,j;
        int r,g,b;
        int *imO;
        for (i=0,imO=(int*)data;i<height;i++) {
            for (j=0;j<width;j++,imO++) {
                r=((*imO)>>16)&0x000000ff;
                g=((*imO)>>8)&0x000000ff;
                b=((*imO)>>0)&0x000000ff;
                if(r<x1 || r>x2) r=x1;
                if(g<x1 || g>x2) g=x1;
                if(b<x1 || b>x2) b=x1;
                r=(int)((r-x1)*escala);
                g=(int)((g-x1)*escala);
                b=(int)((b-x1)*escala);
                *imO=((*imO)&(0xff000000))|(r<<16)|(g<<8)|(b);
            }
        }
    }
}
