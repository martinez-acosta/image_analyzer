/********************************************************************************
** Form generated from reading UI file 'histogram.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAM_H
#define UI_HISTOGRAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Histogram
{
public:
    QWidget *widget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkGS;
    QCheckBox *checkRed;
    QCheckBox *checkGreen;
    QCheckBox *checkBlue;
    QCustomPlot *customPlot;

    void setupUi(QDialog *Histogram)
    {
        if (Histogram->objectName().isEmpty())
            Histogram->setObjectName(QStringLiteral("Histogram"));
        Histogram->resize(630, 360);
        Histogram->setMinimumSize(QSize(630, 360));
        widget = new QWidget(Histogram);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 621, 361));
        horizontalLayoutWidget = new QWidget(widget);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 10, 561, 41));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        checkGS = new QCheckBox(horizontalLayoutWidget);
        checkGS->setObjectName(QStringLiteral("checkGS"));
        checkGS->setChecked(true);

        horizontalLayout_4->addWidget(checkGS);

        checkRed = new QCheckBox(horizontalLayoutWidget);
        checkRed->setObjectName(QStringLiteral("checkRed"));
        checkRed->setChecked(true);

        horizontalLayout_4->addWidget(checkRed);

        checkGreen = new QCheckBox(horizontalLayoutWidget);
        checkGreen->setObjectName(QStringLiteral("checkGreen"));
        checkGreen->setChecked(true);

        horizontalLayout_4->addWidget(checkGreen);

        checkBlue = new QCheckBox(horizontalLayoutWidget);
        checkBlue->setObjectName(QStringLiteral("checkBlue"));
        checkBlue->setChecked(true);

        horizontalLayout_4->addWidget(checkBlue);

        customPlot = new QCustomPlot(widget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(10, 60, 601, 261));

        retranslateUi(Histogram);

        QMetaObject::connectSlotsByName(Histogram);
    } // setupUi

    void retranslateUi(QDialog *Histogram)
    {
        Histogram->setWindowTitle(QApplication::translate("Histogram", "Dialog", 0));
        checkGS->setText(QApplication::translate("Histogram", "GS", 0));
        checkRed->setText(QApplication::translate("Histogram", "Red", 0));
        checkGreen->setText(QApplication::translate("Histogram", "Green", 0));
        checkBlue->setText(QApplication::translate("Histogram", "Blue", 0));
    } // retranslateUi

};

namespace Ui {
    class Histogram: public Ui_Histogram {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAM_H
