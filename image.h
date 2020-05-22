#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>

class image
{
protected:
    int width,height;
    int oX,oY;
    unsigned char *data;
public:
    image();
    image(int w,int h,int s);
    image(int w,int h,unsigned char *image_data);
    ~image();

    void redim(int w,int h, int s); //Set new size for the image. Original data is erased.

    int getHeight();
    int getWidth();
    unsigned char *getData();

};

#endif // IMAGE_H
