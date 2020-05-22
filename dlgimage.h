#ifndef DLGIMAGE_H
#define DLGIMAGE_H

#include <QDialog>
#include <QString>
#include <QStatusBar>
#include "imagelabel.h"


namespace Ui {
    class dlgImage;
}

class dlgImage : public QDialog
{
    Q_OBJECT

public:
    explicit dlgImage(QWidget *parent = 0);
    ~dlgImage();

    int getWidth() { return Width; }
    int getHeight() { return Height; }
    QString getName() { return Name; }
    imageRGB *getImageRGB() { return img->getImageRGB(); }
    void setStatusBarInfo(QStatusBar *q);
    void setName(QString n);


    void saveImageAs(QString n);
    void grayscale();
    void update();

private:
    Ui::dlgImage *ui;
    ImageLabel *img;
    int Width,Height;
    QString Name;

    void redim();

};

#endif // DLGIMAGE_H
