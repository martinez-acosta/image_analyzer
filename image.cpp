#include "image.h"

image::image()
{
    width=0;
    height=0;
    oX=0;
    oY=0;
    data=NULL;
}

image::image(int w, int h, int s) {
    data=NULL;
    redim(w,h,s);
}

image::image(int w, int h, unsigned char *image_data) {
    data=image_data;
    width=w;
    height=h;
    oX=0;
    oY=0;
}

image::~image() {
    if (data)
        delete []data;
}

void image::redim(int w, int h, int s) {
    if (data)
        delete []data;
    width=w;
    height=h;
    oX=0;
    oY=0;
    data=new unsigned char[s];
}

int image::getHeight() {
    return height;
}

int image::getWidth() {
    return width;
}

unsigned char *image::getData() {
    return data;
}
