/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Save_As;
    QAction *action_Exit;
    QAction *actionDuplicate;
    QAction *action_Grayscale;
    QAction *actionNew_Histogram;
    QAction *actionNew_Mask;
    QAction *actionApply_Convolution;
    QAction *actionOperations;
    QAction *actionMin;
    QAction *actionMax;
    QAction *actionSum;
    QAction *actionDiff;
    QAction *actionComplement;
    QAction *actionProduct;
    QAction *actionOpSum;
    QAction *actionOpDiff;
    QAction *actionOpMin;
    QAction *actionOpMax;
    QAction *actionOpComplement;
    QAction *actionOpProduct;
    QAction *actionFirstIm;
    QAction *actionHistogram;
    QAction *actionNormal;
    QAction *actionValue;
    QAction *actionLabelingNormal;
    QAction *actionLabelingValue;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Edit;
    QMenu *menu_Transforms;
    QMenu *menuConvolution;
    QMenu *menuOperations;
    QMenu *menuOt_su;
    QMenu *menuLabeling;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(590, 429);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Open->setShortcutContext(Qt::WindowShortcut);
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        action_Save_As = new QAction(MainWindow);
        action_Save_As->setObjectName(QStringLiteral("action_Save_As"));
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        actionDuplicate = new QAction(MainWindow);
        actionDuplicate->setObjectName(QStringLiteral("actionDuplicate"));
        action_Grayscale = new QAction(MainWindow);
        action_Grayscale->setObjectName(QStringLiteral("action_Grayscale"));
        actionNew_Histogram = new QAction(MainWindow);
        actionNew_Histogram->setObjectName(QStringLiteral("actionNew_Histogram"));
        actionNew_Mask = new QAction(MainWindow);
        actionNew_Mask->setObjectName(QStringLiteral("actionNew_Mask"));
        actionApply_Convolution = new QAction(MainWindow);
        actionApply_Convolution->setObjectName(QStringLiteral("actionApply_Convolution"));
        actionOperations = new QAction(MainWindow);
        actionOperations->setObjectName(QStringLiteral("actionOperations"));
        actionMin = new QAction(MainWindow);
        actionMin->setObjectName(QStringLiteral("actionMin"));
        actionMax = new QAction(MainWindow);
        actionMax->setObjectName(QStringLiteral("actionMax"));
        actionSum = new QAction(MainWindow);
        actionSum->setObjectName(QStringLiteral("actionSum"));
        actionDiff = new QAction(MainWindow);
        actionDiff->setObjectName(QStringLiteral("actionDiff"));
        actionComplement = new QAction(MainWindow);
        actionComplement->setObjectName(QStringLiteral("actionComplement"));
        actionProduct = new QAction(MainWindow);
        actionProduct->setObjectName(QStringLiteral("actionProduct"));
        actionOpSum = new QAction(MainWindow);
        actionOpSum->setObjectName(QStringLiteral("actionOpSum"));
        actionOpDiff = new QAction(MainWindow);
        actionOpDiff->setObjectName(QStringLiteral("actionOpDiff"));
        actionOpMin = new QAction(MainWindow);
        actionOpMin->setObjectName(QStringLiteral("actionOpMin"));
        actionOpMax = new QAction(MainWindow);
        actionOpMax->setObjectName(QStringLiteral("actionOpMax"));
        actionOpComplement = new QAction(MainWindow);
        actionOpComplement->setObjectName(QStringLiteral("actionOpComplement"));
        actionOpProduct = new QAction(MainWindow);
        actionOpProduct->setObjectName(QStringLiteral("actionOpProduct"));
        actionFirstIm = new QAction(MainWindow);
        actionFirstIm->setObjectName(QStringLiteral("actionFirstIm"));
        actionHistogram = new QAction(MainWindow);
        actionHistogram->setObjectName(QStringLiteral("actionHistogram"));
        actionNormal = new QAction(MainWindow);
        actionNormal->setObjectName(QStringLiteral("actionNormal"));
        actionValue = new QAction(MainWindow);
        actionValue->setObjectName(QStringLiteral("actionValue"));
        actionLabelingNormal = new QAction(MainWindow);
        actionLabelingNormal->setObjectName(QStringLiteral("actionLabelingNormal"));
        actionLabelingValue = new QAction(MainWindow);
        actionLabelingValue->setObjectName(QStringLiteral("actionLabelingValue"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        verticalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 590, 23));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QStringLiteral("menu_Edit"));
        menu_Transforms = new QMenu(menubar);
        menu_Transforms->setObjectName(QStringLiteral("menu_Transforms"));
        menuConvolution = new QMenu(menu_Transforms);
        menuConvolution->setObjectName(QStringLiteral("menuConvolution"));
        menuOperations = new QMenu(menu_Transforms);
        menuOperations->setObjectName(QStringLiteral("menuOperations"));
        menuOt_su = new QMenu(menu_Transforms);
        menuOt_su->setObjectName(QStringLiteral("menuOt_su"));
        menuLabeling = new QMenu(menu_Transforms);
        menuLabeling->setObjectName(QStringLiteral("menuLabeling"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menubar->addAction(menu_Transforms->menuAction());
        menu_File->addAction(action_Open);
        menu_File->addAction(action_Save);
        menu_File->addAction(action_Save_As);
        menu_File->addSeparator();
        menu_File->addAction(action_Exit);
        menu_Edit->addAction(actionDuplicate);
        menu_Transforms->addAction(action_Grayscale);
        menu_Transforms->addAction(actionNew_Histogram);
        menu_Transforms->addAction(menuConvolution->menuAction());
        menu_Transforms->addAction(menuOperations->menuAction());
        menu_Transforms->addAction(menuOt_su->menuAction());
        menu_Transforms->addSeparator();
        menu_Transforms->addAction(actionHistogram);
        menu_Transforms->addAction(menuLabeling->menuAction());
        menuConvolution->addSeparator();
        menuConvolution->addSeparator();
        menuConvolution->addAction(actionNew_Mask);
        menuConvolution->addAction(actionApply_Convolution);
        menuOperations->addSeparator();
        menuOperations->addAction(actionFirstIm);
        menuOperations->addAction(actionOpSum);
        menuOperations->addAction(actionOpDiff);
        menuOperations->addAction(actionOpMin);
        menuOperations->addAction(actionOpMax);
        menuOperations->addAction(actionOpComplement);
        menuOperations->addAction(actionOpProduct);
        menuOt_su->addSeparator();
        menuOt_su->addSeparator();
        menuOt_su->addSeparator();
        menuOt_su->addAction(actionNormal);
        menuOt_su->addAction(actionValue);
        menuLabeling->addSeparator();
        menuLabeling->addAction(actionLabelingNormal);
        menuLabeling->addAction(actionLabelingValue);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Image Analysis", 0));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0));
        action_Save_As->setText(QApplication::translate("MainWindow", "S&ave As..", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "&Exit", 0));
        actionDuplicate->setText(QApplication::translate("MainWindow", "&Duplicate", 0));
        action_Grayscale->setText(QApplication::translate("MainWindow", "&Grayscale", 0));
        actionNew_Histogram->setText(QApplication::translate("MainWindow", "&New Histogram", 0));
        actionNew_Mask->setText(QApplication::translate("MainWindow", "&New Mask", 0));
        actionApply_Convolution->setText(QApplication::translate("MainWindow", "&Apply Convolution", 0));
        actionOperations->setText(QApplication::translate("MainWindow", "Operations", 0));
        actionMin->setText(QApplication::translate("MainWindow", "&firstMin", 0));
        actionMax->setText(QApplication::translate("MainWindow", "f&irstMax", 0));
        actionSum->setText(QApplication::translate("MainWindow", "&Sum", 0));
        actionDiff->setText(QApplication::translate("MainWindow", "&Diff", 0));
        actionComplement->setText(QApplication::translate("MainWindow", "&Complement", 0));
        actionProduct->setText(QApplication::translate("MainWindow", "&Product", 0));
        actionOpSum->setText(QApplication::translate("MainWindow", "&opSum", 0));
        actionOpDiff->setText(QApplication::translate("MainWindow", "o&pDiff", 0));
        actionOpMin->setText(QApplication::translate("MainWindow", "op&Min", 0));
        actionOpMax->setText(QApplication::translate("MainWindow", "opMa&x", 0));
        actionOpComplement->setText(QApplication::translate("MainWindow", "opComp&lement", 0));
        actionOpProduct->setText(QApplication::translate("MainWindow", "opP&roduct", 0));
        actionFirstIm->setText(QApplication::translate("MainWindow", "&firstIm", 0));
        actionHistogram->setText(QApplication::translate("MainWindow", "&Histogram", 0));
        actionNormal->setText(QApplication::translate("MainWindow", "Normal", 0));
        actionValue->setText(QApplication::translate("MainWindow", "Value", 0));
        actionLabelingNormal->setText(QApplication::translate("MainWindow", "Normal", 0));
        actionLabelingValue->setText(QApplication::translate("MainWindow", "Value", 0));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "&Edit", 0));
        menu_Transforms->setTitle(QApplication::translate("MainWindow", "&Transforms", 0));
        menuConvolution->setTitle(QApplication::translate("MainWindow", "&Convolution", 0));
        menuOperations->setTitle(QApplication::translate("MainWindow", "&Operations", 0));
        menuOt_su->setTitle(QApplication::translate("MainWindow", "Ot&su", 0));
        menuLabeling->setTitle(QApplication::translate("MainWindow", "Labeling", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
