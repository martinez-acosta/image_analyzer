/********************************************************************************
** Form generated from reading UI file 'dlgimage.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGIMAGE_H
#define UI_DLGIMAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>
#include <imagelabel.h>

QT_BEGIN_NAMESPACE

class Ui_dlgImage
{
public:
    QGridLayout *gridLayout_3;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    ImageLabel *img;

    void setupUi(QDialog *dlgImage)
    {
        if (dlgImage->objectName().isEmpty())
            dlgImage->setObjectName(QStringLiteral("dlgImage"));
        dlgImage->resize(359, 322);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dlgImage->sizePolicy().hasHeightForWidth());
        dlgImage->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(dlgImage);
        gridLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        scrollArea = new QScrollArea(dlgImage);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(135, 150, 82, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        scrollAreaWidgetContents->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        img = new ImageLabel(scrollAreaWidgetContents);
        img->setObjectName(QStringLiteral("img"));
        sizePolicy1.setHeightForWidth(img->sizePolicy().hasHeightForWidth());
        img->setSizePolicy(sizePolicy1);
        img->setCursor(QCursor(Qt::CrossCursor));
        img->setMouseTracking(true);
        img->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(img, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_3->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(dlgImage);

        QMetaObject::connectSlotsByName(dlgImage);
    } // setupUi

    void retranslateUi(QDialog *dlgImage)
    {
        dlgImage->setWindowTitle(QApplication::translate("dlgImage", "Dialog", 0));
        img->setText(QApplication::translate("dlgImage", "Empty Image", 0));
    } // retranslateUi

};

namespace Ui {
    class dlgImage: public Ui_dlgImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGIMAGE_H
