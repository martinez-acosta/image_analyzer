#ifndef IMAGERGB_H
#define IMAGERGB_H
#include "image.h"
#include <QImage>



class imageRGB : public image
{
public:
    imageRGB();
    imageRGB(int w, int h);
    imageRGB(int w, int h, unsigned char *image_data);
    ~imageRGB();


    //Image transformations
    void toGrayScale();
    void toNewHistogram(int x1, int x2);

    //Use this methods only for Qt
    QImage *toImage();
    void fromImage(QImage *im);

};

#endif // IMAGERGB_H
