/********************************************************************************
** Form generated from reading UI file 'mask.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASK_H
#define UI_MASK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mask
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelAlpha;
    QComboBox *comboBox_alpha;
    QLabel *labelBeta;
    QComboBox *comboBox_beta;
    QLabel *label_columns;
    QSpinBox *spinBox_columns;
    QLabel *label_rows;
    QSpinBox *spinBox_rows;

    void setupUi(QDialog *Mask)
    {
        if (Mask->objectName().isEmpty())
            Mask->setObjectName(QStringLiteral("Mask"));
        Mask->resize(634, 500);
        Mask->setMinimumSize(QSize(630, 500));
        verticalLayoutWidget = new QWidget(Mask);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 581, 461));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(verticalLayoutWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 0, -1, -1);
        labelAlpha = new QLabel(verticalLayoutWidget);
        labelAlpha->setObjectName(QStringLiteral("labelAlpha"));

        horizontalLayout_6->addWidget(labelAlpha);

        comboBox_alpha = new QComboBox(verticalLayoutWidget);
        comboBox_alpha->setObjectName(QStringLiteral("comboBox_alpha"));

        horizontalLayout_6->addWidget(comboBox_alpha);

        labelBeta = new QLabel(verticalLayoutWidget);
        labelBeta->setObjectName(QStringLiteral("labelBeta"));

        horizontalLayout_6->addWidget(labelBeta);

        comboBox_beta = new QComboBox(verticalLayoutWidget);
        comboBox_beta->setObjectName(QStringLiteral("comboBox_beta"));

        horizontalLayout_6->addWidget(comboBox_beta);


        horizontalLayout->addLayout(horizontalLayout_6);

        label_columns = new QLabel(verticalLayoutWidget);
        label_columns->setObjectName(QStringLiteral("label_columns"));

        horizontalLayout->addWidget(label_columns);

        spinBox_columns = new QSpinBox(verticalLayoutWidget);
        spinBox_columns->setObjectName(QStringLiteral("spinBox_columns"));

        horizontalLayout->addWidget(spinBox_columns);

        label_rows = new QLabel(verticalLayoutWidget);
        label_rows->setObjectName(QStringLiteral("label_rows"));

        horizontalLayout->addWidget(label_rows);

        spinBox_rows = new QSpinBox(verticalLayoutWidget);
        spinBox_rows->setObjectName(QStringLiteral("spinBox_rows"));

        horizontalLayout->addWidget(spinBox_rows);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Mask);

        QMetaObject::connectSlotsByName(Mask);
    } // setupUi

    void retranslateUi(QDialog *Mask)
    {
        Mask->setWindowTitle(QApplication::translate("Mask", "Dialog", 0));
        labelAlpha->setText(QApplication::translate("Mask", "Alpha:", 0));
        labelBeta->setText(QApplication::translate("Mask", "Beta:", 0));
        label_columns->setText(QApplication::translate("Mask", "Columns:", 0));
        label_rows->setText(QApplication::translate("Mask", "Rows:", 0));
    } // retranslateUi

};

namespace Ui {
    class Mask: public Ui_Mask {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASK_H
