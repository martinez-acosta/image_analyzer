#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include <QWidget>
#include <QLabel>
#include <QStatusBar>
#include <QPixmap>
#include <QString>
#include "imagergb.h"


class ImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ImageLabel(QWidget *parent = 0);
    ~ImageLabel();
    void setLabelInfo(QLabel *i);
    void setStatusBarInfo(QStatusBar *q);
    void setImage(QString &n);
    imageRGB *getImageRGB() { return img; }

    void saveImageAs(QString &n);
    void grayscale();

signals:

public slots:

protected:
    void mouseMoveEvent(QMouseEvent *ev);

private:
    QLabel *info;
    QStatusBar *info_sb;
    imageRGB *img;
    QImage *qimg; //to transfer data only
    QString path;
public:
    void update();

};

#endif // IMAGELABEL_H
